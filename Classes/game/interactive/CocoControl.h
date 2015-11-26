#ifndef __COCO_CONTROL_H__
#define __COCO_CONTROL_H__
namespace cocogame {
	class CocoControl
	{
	public:
		static CocoControl *getInstance();
		CocoControl();
		~CocoControl();
		inline void setPhysicsWorld(cocos2d::PhysicsWorld *pw) { _physicsWorld = pw; }
	private:
		static CocoControl *_shared_instance;
		cocos2d::PhysicsWorld *_physicsWorld;
		/*class AccelerationCtrl
		{
		public:
			AccelerationCtrl():_enabled(false){};
			void setEnabled(bool value);
		private:
			bool _enabled;
			cocos2d::PhysicsWorld *_physicsWorld;
		} *_accCtrl;*/
	};
}
#endif

