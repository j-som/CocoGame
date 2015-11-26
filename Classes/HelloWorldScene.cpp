#include "HelloWorldScene.h"
#include "Roco.h"
#include "game/cocogame.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

	Vect g(0.0f, -50.0f);
	scene->getPhysicsWorld()->setGravity(g);
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	auto body = PhysicsBody::createEdgeBox(visibleSize);
	this->setPhysicsBody(body);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	auto roco = Roco::createRoco();
	roco->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(roco, 2);
	auto node = Node::create();
	//auto line = PhysicsBody::createEdgeSegment(Vec2(origin.x, origin.y + 100), Vec2(origin.x + visibleSize.width, origin.y));
	//node->setPhysicsBody(line);
	this->addChild(node);
	cocogame::MapParser parser;
	parser.initWithTMXFile("res/map/00.tmx");
	auto list = parser.getStaticBlockList();
	auto sbody = PhysicsBody::create();
	for (auto it = list->begin(); it != list->end(); ++it)
	{
		auto obj = *it;
		auto shapes = obj->createPhysicsShapes();
		for (auto s = shapes->begin(); s != shapes->end(); ++s)
		{
			sbody->addShape(*s);
		}
	}
	sbody->setDynamic(false);
	node->setPhysicsBody(sbody);
	//auto info = new cocogame::MapInfo();
	//info->parseByTMXMapInfo(*mapInfo);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
