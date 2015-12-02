#include "CocoCamera.h"
using namespace cocos2d;
namespace cocogame {
	void CocoCamera::open()
	{
		if (_enterFrameListener == nullptr)
		{
			_enterFrameListener = EventListenerCustom::create(Director::EVENT_AFTER_UPDATE, CC_CALLBACK_1(CocoCamera::onUpdate, this));
			auto dispatcher = Director::getInstance()->getEventDispatcher();
			dispatcher->addEventListenerWithFixedPriority(_enterFrameListener, -1);
		}
	}
	void CocoCamera::close()
	{
		if (_enterFrameListener != nullptr)
		{
			auto dispatcher = Director::getInstance()->getEventDispatcher();
			dispatcher->removeEventListener(_enterFrameListener);
			_enterFrameListener = nullptr;
		}
	}
	void CocoCamera::see(cocos2d::Node * node)
	{
	}
	void CocoCamera::onUpdate(cocos2d::Event * evt)
	{
		auto bgpos = _backgroundNode->convertToWorldSpace(Vec2(0, 0));
		auto tpos = _targetNode->convertToWorldSpace(Vec2(0, 0));
		auto offset = _center - tpos;
		auto bgSize = _backgroundNode->getContentSize() * 1.2;
		bgpos += offset;
		if (bgpos.x > 0)
		{
			offset.x -= bgpos.x;
		}
		else if (bgpos.x + bgSize.width < _viewSize.width)
		{
			offset.x += _viewSize.width - bgpos.x - bgSize.width;
		}
		if (bgpos.y > 0)
		{
			offset.y -= bgpos.y;
		}
		else if (bgpos.y + bgSize.height < _viewSize.height)
		{
			offset.y += _viewSize.height - bgpos.y - bgSize.height;
		}
		_backgroundNode->setPosition(_backgroundNode->getPosition() + offset);
	}
}