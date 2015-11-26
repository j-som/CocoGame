#include "CocoControl.h"
#include <new>
#include "cocos2d.h"
namespace cocogame {
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
	/*void CocoControl::AccelerationCtrl::setEnabled(bool value)
	{
	}*/
}