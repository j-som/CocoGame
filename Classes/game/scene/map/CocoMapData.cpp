#include "CocoMapData.h"
#include "cocos2d.h"

using namespace cocos2d;
namespace cocogame {
	CocoMapData::CocoMapData()
	{
	}

	//CocoMapData::CocoMapData(const CocoMapData &copied):_mapInfo(copied._mapInfo)
	//{

	//}

	bool CocoMapData::initWithTMXFile(const std::string & fileName)
	{
		CC_SAFE_RELEASE(_mapInfo);
		_mapInfo = TMXMapInfo::create(fileName);
		if (_mapInfo)
		{
			_mapInfo->retain();
		}
		CCASSERT(_mapInfo != nullptr, "Invalid tmx file");
		auto groups = this->getGroupNamed("earth_surface")->getObjects();
		CC_SAFE_DELETE(_staticBlocks);
		this->_staticBlocks = new StaticBlockList();
		for (auto it = groups.cbegin(); it != groups.cend(); ++it)
		{
			ValueMap map = it->asValueMap();
			StaticBlockObject *obj = new StaticBlockObject();
			if (obj->initWithObject(map))
			{
				_staticBlocks->push_back(obj);
			}
			else
			{
				delete obj;
			}

		}
		return true;
	}

	cocos2d::TMXObjectGroup * CocoMapData::getGroupNamed(const std::string & groupName) const
	{
		auto groups = _mapInfo->getObjectGroups();
		CCASSERT(groupName.size() > 0, "Invalid group name!");
		if (groups.size() > 0)
		{
			TMXObjectGroup* objectGroup = nullptr;
			for (auto iter = groups.cbegin(); iter != groups.cend(); ++iter)
			{
				objectGroup = *iter;
				if (objectGroup && objectGroup->getGroupName() == groupName)
				{
					return objectGroup;
				}
			}
		}
		return nullptr;
	}




	CocoMapData::~CocoMapData()
	{
		CC_SAFE_FREE(_mapInfo);
		CC_SAFE_FREE(_staticBlocks);
	}

	StaticBlockObject::StaticBlockObject():shape(BlockShapeType::NONE), material(0, 0.5f, 0.5f)
	{
	}
	StaticBlockObject::~StaticBlockObject()
	{
		switch (shape)
		{
		case BlockShapeType::POLYGON:
			CC_SAFE_DELETE(_data.polygonPoints);
			break;
		case BlockShapeType::CIRCLE:
			_data.radius = 0.0f;
			break;
		case BlockShapeType::EAGE:
			CC_SAFE_DELETE(_data.edgePoints);
			break;
		default:
			break;
		}
	}
	Vector<PhysicsShape*> *StaticBlockObject::createPhysicsShapes()
	{
		CCASSERT(shape != BlockShapeType::NONE, "Invalid shape!");
		Vector<PhysicsShape *> *shapes = nullptr;
		PhysicsShape *ret = nullptr;
		switch (shape)
		{
		case BlockShapeType::POLYGON:
			ret = PhysicsShapePolygon::create(_data.polygonPoints->data(), _data.polygonPoints->size(), material, Vec2(this->x, this->y));
			shapes = new Vector<PhysicsShape *>(1);
			shapes->pushBack(ret);
			break;
		case BlockShapeType::CIRCLE:
			ret = PhysicsShapeCircle::create(_data.radius, material, Vec2(this->x, this->y));
			shapes = new Vector<PhysicsShape *>(1);
			shapes->pushBack(ret);
			break;
		case BlockShapeType::EAGE:
			CCASSERT(_data.edgePoints->size() > 1, "Edge segment points must be more than 1!");
			shapes = new Vector<PhysicsShape *>(_data.edgePoints->size());
			for (auto it = _data.edgePoints->begin(); (it+1) != _data.edgePoints->end(); ++it)
			{
				ret = PhysicsShapeEdgeSegment::create(*it, *(it + 1), material);
				shapes->pushBack(ret);
			}
			break;
		case BlockShapeType::RECTANGLE:
			shapes = new Vector<PhysicsShape *>(1);
			ret = PhysicsShapeBox::create(Size(this->width, this->height), material, Vec2(this->x, this->y));
			shapes->pushBack(ret);
		default:
			break;
		}
		return shapes;
	}
	bool StaticBlockObject::initWithObject(const cocos2d::ValueMap obj)
	{
		_originObj = obj;
		this->x = obj.at("x").asInt();
		this->y = obj.at("y").asInt();
		this->width = obj.at("width").asFloat();
		this->height = obj.at("height").asFloat();
		auto polygon = obj.find("polylinePoints");
		if (polygon != obj.end())
		{
			initEdgePoints(polygon->second);
			return true;
		}
		polygon = obj.find("points");
		if (polygon != obj.end())
		{
			initPolygonPoints(polygon->second);
			return true;
		}
		//CCASSERT(this->width > 0.0f && this->height > 0.0f, "");
		if (this->width > 0.0f && this->height > 0.0f)
		{
			bool isEllipse = obj.find("ellipse") != obj.end() && obj.at("ellipse").asBool();
			if (isEllipse)
			{
				if (this->width == this->height)
				{
					_data.radius = this->width / 2;
					shape = BlockShapeType::CIRCLE;
					this->x += _data.radius;
					this->y += _data.radius;
				}
				else
				{
					ellipse2PolygonPoints();
				}
			}
			else
			{
				shape = BlockShapeType::RECTANGLE;
				this->x += this->width / 2;
				this->y += this->height / 2;
			}
			return true;
		}

		return false;
	}
	void StaticBlockObject::initEdgePoints(cocos2d::Value v)
	{
		shape = BlockShapeType::EAGE;
		_data.edgePoints = new std::vector<Point>();
		auto points = v.asValueVector();
		_data.edgePoints->reserve(points.size());
		for (auto p = points.begin(); p != points.end(); ++p)
		{
			auto map = p->asValueMap();
			Point point = Point(map.at("x").asFloat(), map.at("y").asFloat());
			point = CC_POINT_PIXELS_TO_POINTS(point);
			point.x += this->x;
			point.y = this->y - point.y;
			_data.edgePoints->push_back(point);
		}
	}
	void StaticBlockObject::initPolygonPoints(cocos2d::Value v)
	{
		shape = BlockShapeType::POLYGON;
		_data.polygonPoints = new std::vector<Point>();
		auto points = v.asValueVector();
		_data.polygonPoints->reserve(points.size());
		for (auto p = points.begin(); p != points.end(); ++p)
		{
			auto map = p->asValueMap();
			Point point = Point(map.at("x").asFloat(), -map.at("y").asFloat());
			point = CC_POINT_PIXELS_TO_POINTS(point);
			_data.polygonPoints->push_back(point);
		}
	}
	void StaticBlockObject::ellipse2PolygonPoints()
	{
		shape = BlockShapeType::POLYGON;
		_data.polygonPoints = new std::vector<Point>();
		float a = this->width / 2;
		float b = this->height / 2;

		_data.polygonPoints->reserve(10);
		float angle = 0.0f;
		while (angle > -360.0f)
		{
			_data.polygonPoints->push_back(Point(std::cosf(angle/180*std::_Pi) * a, std::sin(angle / 180 * std::_Pi) * b));
			angle -= 22.5f;
		} 
		this->x += a;
	}
}