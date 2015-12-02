#include "CocoWorld.h"

using namespace cocos2d;

namespace cocogame {
	Scene * CocoWorld::createScene(const cocos2d::Value &worldInfo)
	{
		auto scene = Scene::createWithPhysics();

		// 'layer' is an autorelease object
		auto layer = CocoWorld::create();

		layer->setPhysicsWorld(scene->getPhysicsWorld());
		layer->createWorldByInfo(worldInfo);
		// add layer as a child to scene
		scene->addChild(layer);
		// return the scene
		return scene;
	}

	bool CocoWorld::init()
	{
		if (!Layer::init())
		{
			return false;
		}

		return true;
	}
	bool CocoWorld::createWorldByInfo(const cocos2d::Value & info)
	{
		return false;
	}
}
