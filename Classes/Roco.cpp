#include "Roco.h"

Roco * Roco::createRoco()
{
	auto roco = Roco::create();
	roco->initByFName("locoroco.png");
	return roco;
}

Roco * Roco::createRoco(const std::string &fname)
{
	auto roco = Roco::create();
	roco->initByFName(fname);
	return roco;
}

bool Roco::init()
{
	if (cocos2d::Sprite::init() == false)
	{
		return false;
	}
	auto body = cocos2d::PhysicsBody::createCircle(40, cocos2d::PhysicsMaterial(1.0f, 0.0f, 0.5f));
	//dy->setMass(1200);
	body->setMoment(10);
	//body->setPositionOffset(cocos2d::Vec2(-100.0f, -100.0f));
	//auto body = cocos2d::PhysicsBody::createBox(cocos2d::Size(40, 40));
	this->setPhysicsBody(body);
	return true;
}

void Roco::initByFName(const std::string &fname)
{
	if (_face == nullptr)
	{
		_face = cocos2d::Sprite::create(fname);
		this->addChild(_face, 0);
	}
}
