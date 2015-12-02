#ifndef __COCO_CAMERA_H__
#define __COCO_CAMERA_H__
#include "cocos2d.h"
namespace cocogame {
	class CocoCamera
	{
	public:
		inline void setBackgroundNode(cocos2d::Node *node)
		{
			_backgroundNode = node;
		}
		inline void setTargetNode(cocos2d::Node *node) {
			_targetNode = node;
		}
		inline void setViewCenter(const cocos2d::Vec2 &center) { _center = center; }
		inline void setViewPortSize(const cocos2d::Size &size) { _viewPortSize = size; }
		inline void setSceneSize(const cocos2d::Size &size) { _sceneSize = size; }
		virtual void followBegin();
		virtual void followEnd();
		inline void see(cocos2d::Node *node);
	private:
		cocos2d::Node *_backgroundNode;
		cocos2d::Node *_targetNode;
		cocos2d::EventListener *_enterFrameListener;
		cocos2d::Vec2 _center;
		cocos2d::Size _viewPortSize;
		cocos2d::Size _sceneSize;
		void onUpdate(cocos2d::Event *evt);
	};
}
#endif
