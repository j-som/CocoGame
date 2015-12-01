#ifndef __COCO_CONTROL_H__
#define __COCO_CONTROL_H__
#include "cocos2d.h"
namespace cocogame {
	typedef void (*AccelerationHandler)(cocos2d::Acceleration*, cocos2d::Event*);
	class CocoControl
	{
	public:
		static CocoControl *getInstance();
		CocoControl();
		~CocoControl();
		inline void setPhysicsWorld(cocos2d::PhysicsWorld *pw) { _physicsWorld = pw; }
		inline bool addAccelerationHandler(AccelerationHandler func)
		{
			for (auto it = _accelerationCallbacks.cbegin(); it != _accelerationCallbacks.cend(); ++it)
			{
				if (*it == func)
				{
					return false;
				}
			}
			_accelerationCallbacks.push_back(func);
			return true;
		}
		inline bool removeAccelerationHandler(AccelerationHandler func)
		{
			for (auto it = _accelerationCallbacks.cbegin(); it != _accelerationCallbacks.cend(); ++it)
			{
				if (*it == func)
				{
					_accelerationCallbacks.erase(std::remove(_accelerationCallbacks.begin(), _accelerationCallbacks.end(), func), _accelerationCallbacks.end());
					return true;
				}
			}
			return false;
		}
		inline bool isAccelerometerEnabled() const { return _accelerometerEnabled; }
		void setAccelerometerEnabled(const bool value);
		void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);
	private:
		std::vector<AccelerationHandler> _accelerationCallbacks;
		cocos2d::PhysicsWorld *_physicsWorld;
		bool _accelerometerEnabled;
		cocos2d::EventListener*  _accelerometerListener;
	};
}
#endif

