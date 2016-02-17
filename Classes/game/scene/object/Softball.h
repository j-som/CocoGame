#ifndef __SOFT_BALL_H__
#define __SOFT_BALL_H__
#include "cocos2d.h"
namespace cocogame{
	class Softball:public cocos2d::DrawNode
	{
	public:
		CREATE_FUNC(Softball);
		virtual bool init();
		virtual void onEnter();
		virtual void onExit();
		virtual void update(float delta);
		void initWithRadius(float radius, int jointCount);
		
	private:
		cocos2d::Node *_mainNode;
		cocos2d::Vector<cocos2d::Node *> _subNodeList;
		std::vector<cocos2d::PhysicsJoint *> _insideJoints;
		std::vector<cocos2d::PhysicsJoint *> _surfaceJoints;

		void buildJoints();
		void fillColor(cocos2d::Color4F &color);
	};
}
#endif