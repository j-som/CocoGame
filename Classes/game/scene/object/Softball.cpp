#include "Softball.h"
#include "cocos2d.h"
using namespace cocos2d;

namespace cocogame {
	bool Softball::init()
	{
		if (!DrawNode::init())
		{
			return false;
		}
		scheduleUpdate();
		return true;
	}

	void Softball::onEnter()
	{
		DrawNode::onEnter();
		auto world = getScene()->getPhysicsWorld();
		if (!_insideJoints.empty())
		{
			for each(auto spring in _insideJoints)
			{
				world->addJoint(spring);
			}
		}
		if (!_surfaceJoints.empty())
		{
			for each(auto spring in _surfaceJoints)
			{
				world->addJoint(spring);
			}
		}
	}

	void Softball::onExit()
	{
		if (!_insideJoints.empty())
		{
			for each(auto spring in _insideJoints)
			{
				spring->setEnable(false);
			}
		}

		if (!_surfaceJoints.empty())
		{
			for each(auto spring in _surfaceJoints)
			{
				spring->setEnable(false);
			}
		}
		DrawNode::onExit();
	}

	void Softball::update(float delta)
	{
		//this->drawCatmullRom
		fillColor(Color4F(1.0f, 1.0f, 0.0f, 1.0f));
	}

	void Softball::initWithRadius(float radius, int jointCount)
	{
		_mainNode = Node::create();
		auto mbody = PhysicsBody::createBox(Size(1, 1));
		mbody->addMass(0.1);
		_mainNode->setPhysicsBody(mbody);
		addChild(_mainNode);
		float twoPi = 2 * std::_Pi;
		int nodeCount = jointCount * 2;
		_subNodeList.reserve(nodeCount);
		for (int i = 0; i < nodeCount; ++i)
		{
			auto node = Node::create();
			float x = std::cos(twoPi * i / nodeCount) * radius;
			float y = std::sin(twoPi * i / nodeCount) * radius;
			node->setPosition(x, y);
			auto body = PhysicsBody::createBox(Size(1, 1));
			body->addMass(0.01);
			node->setPhysicsBody(body);
			_subNodeList.pushBack(node);
			addChild(node);
		}
		buildJoints();
	}
	
	void Softball::buildJoints()
	{
		//内部支撑节点
		int jointCount = _subNodeList.size();
		if (false == _insideJoints.empty())
		{
			for each (auto spring in _insideJoints)
			{
				spring->removeFormWorld();
			}
			_insideJoints.clear();
		}
		_insideJoints.reserve(jointCount);
		
		for each (auto node in _subNodeList)
		{
			auto spring = PhysicsJointSpring::construct(_mainNode->getPhysicsBody(), node->getPhysicsBody(), Vec2(0, 0), Vec2(0, 0), 20.0f, 2.0f);
			//spring->setRestLength(length);
			_insideJoints.push_back(spring);
		}
		
		Node *nodeA, *nodeB;
		/*
		for (int i = 0; i < jointCount; ++i)
		{
			nodeA = _subNodeList.at(i);
			nodeB = _subNodeList.at(i + jointCount);
			auto spring = PhysicsJointSpring::construct(nodeA->getPhysicsBody(), nodeB->getPhysicsBody(), Vec2(0, 0), Vec2(0, 0), 20.0f, 2.0f);
			_insideJoints.push_back(spring);
		}
		*/
		//外表包围节点
		if (false == _surfaceJoints.empty())
		{
			for each (auto spring in _surfaceJoints)
			{
				spring->removeFormWorld();
			}
			_surfaceJoints.clear();
		}
		_surfaceJoints.reserve(_subNodeList.size());
		nodeA = _subNodeList.at(_subNodeList.size() - 1);
		nodeB = _subNodeList.at(0);
		auto dJoint = PhysicsJointDistance::construct(nodeA->getPhysicsBody(), nodeB->getPhysicsBody(), Vec2(0, 0), Vec2(0, 0));
		_surfaceJoints.push_back(dJoint);
		for (int i = 0; i < _subNodeList.size() - 1; ++i)
		{
			nodeA = _subNodeList.at(i);
			nodeB = _subNodeList.at(i+1);
			dJoint = PhysicsJointDistance::construct(nodeA->getPhysicsBody(), nodeB->getPhysicsBody(), Vec2(0, 0), Vec2(0, 0));
			_surfaceJoints.push_back(dJoint);
		}
	}
	void Softball::fillColor(cocos2d::Color4F & color)
	{
		clear();
		if (!_subNodeList.empty())
		{
			ssize_t size = _subNodeList.size();
			PointArray *ps = PointArray::create(size);
			if (ps != nullptr)
			{
				for each (auto node in _subNodeList)
				{
					ps->addControlPoint(node->getPosition());
				}
				
				ssize_t p;
				float lt;
				float deltaT = 1.0f / ps->count();
				Vec2 *vertices = new (std::nothrow) Vec2[size];
				if (!vertices)
					return;

				for (unsigned int i = 0; i < size; i++) {

					float dt = (float)i / size;

					// border
					if (dt == 1) {
						p = ps->count() - 1;
						lt = 1;
					}
					else {
						p = dt / deltaT;
						lt = (dt - deltaT * (float)p) / deltaT;
					}

					// Interpolate
					Vec2 pp0 = ps->getControlPointAtIndex(p - 1);
					Vec2 pp1 = ps->getControlPointAtIndex(p + 0);
					Vec2 pp2 = ps->getControlPointAtIndex(p + 1);
					Vec2 pp3 = ps->getControlPointAtIndex(p + 2);

					Vec2 newPos = ccCardinalSplineAt(pp0, pp1, pp2, pp3, 0.05f, lt);
					vertices[i].x = newPos.x;
					vertices[i].y = newPos.y;
				}
				drawPolygon(vertices, size, color, 0.00001, color);
				log("run fill color");
				CC_SAFE_DELETE_ARRAY(vertices);
				
			}
		}

	}
}