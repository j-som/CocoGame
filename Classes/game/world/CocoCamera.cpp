#include "CocoCamera.h"
using namespace cocos2d;
namespace cocogame {
	void CocoCamera::followBegin()
	{
		if (_enterFrameListener == nullptr)
		{
			_enterFrameListener = EventListenerCustom::create(Director::EVENT_AFTER_UPDATE, CC_CALLBACK_1(CocoCamera::onUpdate, this));
			auto dispatcher = Director::getInstance()->getEventDispatcher();
			dispatcher->addEventListenerWithFixedPriority(_enterFrameListener, -1);
		}
	}
	void CocoCamera::followEnd()
	{
		if (_enterFrameListener != nullptr)
		{
			auto dispatcher = Director::getInstance()->getEventDispatcher();
			dispatcher->removeEventListener(_enterFrameListener);
			_enterFrameListener = nullptr;
		}
	}
	inline void CocoCamera::see(cocos2d::Node * node)
	{
		auto bgpos = _backgroundNode->convertToWorldSpace(Vec2(0, 0));
		auto tpos = node->convertToWorldSpace(Vec2(0, 0));
		auto offset = _center - tpos;
		bgpos += offset;
		if (bgpos.x > 0)
		{
			offset.x -= bgpos.x;
		}
		else if (bgpos.x + _sceneSize.width < _viewPortSize.width)
		{
			offset.x += _viewPortSize.width - bgpos.x - _sceneSize.width;
		}
		if (bgpos.y > 0)
		{
			offset.y -= bgpos.y;
		}
		else if (bgpos.y + _sceneSize.height < _viewPortSize.height)
		{
			offset.y += _viewPortSize.height - bgpos.y - _sceneSize.height;
		}
		_backgroundNode->setPosition(_backgroundNode->getPosition() + offset);
	}
	void CocoCamera::onUpdate(cocos2d::Event * evt)
	{
		see(_targetNode);
	}
}