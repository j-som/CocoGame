#ifndef __COCO_WORLD_H__
#define __COCO_WORLD_H__
#include "cocos2d.h"
#include "game\scene\map\CocoMapData.h"
namespace cocogame {
	class CocoWorld :
		public cocos2d::Layer
	{
	public:
		static cocos2d::Scene* createScene(const cocos2d::Value &worldInfo);
		CREATE_FUNC(CocoWorld);
		virtual bool init();
		inline void setPhysicsWorld(cocos2d::PhysicsWorld *w) { _physicsWorld = w; }
	protected:
		virtual bool createWorldByInfo(const cocos2d::Value &info);
	private:
		cocos2d::PhysicsWorld *_physicsWorld;
		CocoMapData *_mapData;
	};
}
#endif