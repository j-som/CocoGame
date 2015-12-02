#ifndef __MAP_PARSER_H__
#define __MAP_PARSER_H__

#include <string>
#include "cocos2d.h"

namespace cocogame {
	class StaticBlockObject
	{
	public:
		StaticBlockObject();
		~StaticBlockObject();
		enum class BlockShapeType
		{
			NONE,
			POLYGON,//多边形
			//ELLIPSE,//椭圆形
			CIRCLE,//圆形
			RECTANGLE,//矩形
			EAGE//边
		};

		BlockShapeType shape;
		cocos2d::PhysicsMaterial material;
		inline void setDensity(const float value) { material.density = value; }
		inline void setFriction(const float value) { material.friction = value; }
		inline void setRestitution(const float value) { material.restitution = value; }
		const inline float getDesity() const { return material.density; }
		const inline float getFriction() const { return material.friction; }
		const inline float getRestitution()const { return material.restitution; }
		cocos2d::Vector<cocos2d::PhysicsShape*> *createPhysicsShapes();
		bool initWithObject(const cocos2d::ValueMap obj);
		inline cocos2d::Value getOtherAttribute(const std::string &key) 
		{ 
			if (_originObj.find(key) != _originObj.end()) 
				return _originObj.at(key); 
			return cocos2d::Value();
		}
		int x;
		int y;
		float width;
		float height;
	private:
		union BlockData
		{
			float radius;
			std::vector<cocos2d::Point> *edgePoints;
			std::vector<cocos2d::Point> *polygonPoints;
		} _data;
		cocos2d::ValueMap _originObj;
		void initEdgePoints(cocos2d::Value v);
		void initPolygonPoints(cocos2d::Value v);
		void ellipse2PolygonPoints();

	};
	typedef std::vector<StaticBlockObject *> StaticBlockList;

	class CocoMapData
	{
	public:
		CocoMapData();
		//CocoMapData(const CocoMapData &copied);
		bool initWithTMXFile(const std::string &fileName);
		cocos2d::TMXObjectGroup *getGroupNamed(const std::string &groupName) const;
		inline const StaticBlockList *getStaticBlockList() { return _staticBlocks; }
		inline const cocos2d::Size getMapSize() const { return _mapSize; }
		~CocoMapData();

	private:
		cocos2d::TMXMapInfo *_mapInfo = nullptr;
		StaticBlockList *_staticBlocks = nullptr;
		cocos2d::Size _mapSize;
	};
}
#endif
