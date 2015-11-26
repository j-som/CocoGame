#include "MapInfo.h"
using namespace cocos2d;
namespace cocogame
{
	MapInfo::MapInfo()
	{
	}


	MapInfo::~MapInfo()
	{
	}
	bool MapInfo::parseByTMXMapInfo(const cocos2d::TMXMapInfo & mapInfo)
	{
		Size ms = mapInfo.getMapSize();
		Size gs = mapInfo.getTileSize();

		_size = Size(ms.width * gs.width, ms.height * gs.height);
		_gridSize = gs;

		auto groups = mapInfo.getObjectGroups();
		if (groups.size() > 0)
		{
			auto g = getGroupNamedInGroups(CocoLayerName[EARTH_SURFACE], groups);
			auto data = g->getProperty("x");
			return true;
		}
		//auto 
		return false;
	}
	cocos2d::TMXObjectGroup * MapInfo::getGroupNamedInGroups(const std::string & groupName, Vector<TMXObjectGroup *> groups)
	{
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
}
