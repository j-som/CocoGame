#include "CocoControl.h"
#include <new>
#include "cocos2d.h"
using namespace cocos2d;

namespace cocogame {
	static CocoControl *_shared_instance = nullptr;
	CocoControl * CocoControl::getInstance()
	{
		if (nullptr == _shared_instance)
		{
			_shared_instance = new (std::nothrow) CocoControl();
			CCASSERT(_shared_instance, "FATAL: Not enough memory");
		}
		return _shared_instance;
	}

	CocoControl::CocoControl()
	{
	}


	CocoControl::~CocoControl()
	{
	}
	void CocoControl::setAccelerometerEnabled(const bool enabled)
	{
		if (enabled != _accelerometerEnabled)
		{
			_accelerometerEnabled = enabled;

			auto dispatcher = Director::getInstance()->getEventDispatcher();
			dispatcher->removeEventListener(_accelerometerListener);
			_accelerometerListener = nullptr;

			Device::setAccelerometerEnabled(enabled);

			if (enabled)
			{
				auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(CocoControl::onAcceleration, this));
				dispatcher->addEventListenerWithFixedPriority(listener, -1);
				_accelerometerListener = listener;
			}
		}
	}
	void CocoControl::onAcceleration(cocos2d::Acceleration * acc, cocos2d::Event * event)
	{
		for (auto it = _accelerationCallbacks.begin(); it != _accelerationCallbacks.end(); ++it)
		{
			(*it)(acc, event);
		}
	}
	/*void CocoControl::AccelerationCtrl::setEnabled(bool value)
	{
	}*/
}