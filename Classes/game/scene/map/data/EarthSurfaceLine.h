#ifndef __COCO_EARTH_SURFACE_LINE_H__
#define __COCO_EARTH_SURFACE_LINE_H__

#include "cocos2d.h"
namespace cocogame
{
	class EarthSurfaceLine
	{
	public:
		EarthSurfaceLine();
		~EarthSurfaceLine();
		inline std::vector<cocos2d::Point> getPoints() const { return _points; };
		inline void setPoints(const std::vector<cocos2d::Point>& points) { _points = points; };
		void initWithString(std::string &str);
	private:
		std::vector<cocos2d::Point> _points;
	};
}

#endif

