#ifndef __COCO_MAP_INFO_H__
#define __COCO_MAP_INFO_H__
#include "cocos2d.h"
#include "EarthSurfaceLine.h"

namespace cocogame
{
	enum CocoLayerIndex
	{
		EARTH_SURFACE
	};

	static const char *CocoLayerName[] = {
		"earth_surface"
	};

	class MapInfo
	{
	public:
		MapInfo();
		~MapInfo();
		bool parseByTMXMapInfo(const cocos2d::TMXMapInfo &mapInfo);
		inline const std::vector<EarthSurfaceLine> &getSurfaceLines() const { return _surfaceLines; };
		inline void setSurfaceLines(const std::vector<EarthSurfaceLine> &lines) { _surfaceLines = lines; }
		inline const cocos2d::Size getMapSize() { return _size; }
		inline const cocos2d::Size getGridSize() { return _gridSize; }
	private:
		std::vector<EarthSurfaceLine> _surfaceLines;
		cocos2d::TMXObjectGroup *getGroupNamedInGroups(const std::string &groupName, cocos2d::Vector<cocos2d::TMXObjectGroup *> groups);
		cocos2d::Size _size;
		cocos2d::Size _gridSize;
	};
}
#endif

