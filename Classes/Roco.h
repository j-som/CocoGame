#pragma once
#include "cocos2d.h"
class Roco :
	public cocos2d::Sprite
{
public:
	static Roco *createRoco();
	static Roco *createRoco(const std::string &fname);
	virtual bool init();
	CREATE_FUNC(Roco);

private:
	cocos2d::Sprite *_face;
	void initByFName(const std::string &fname);
};

