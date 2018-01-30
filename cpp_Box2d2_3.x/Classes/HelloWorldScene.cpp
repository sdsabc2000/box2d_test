#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "VisibleRect.h"




USING_NS_CC;

using namespace cocostudio::timeline;

//#define PTM_RATIO 32
#define PTM_RATIO 0.05


HelloWorld::HelloWorld()
{


}
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
    //
    //// 'layer' is an autorelease object
    //auto layer = HelloWorld::create();

    //// add layer as a child to scene
    //scene->addChild(layer);



    // return the scene
    //return scene;
	{
		//创建有物理空间的场景  
		Scene* scene = Scene::createWithPhysics();
		//设置Debug模式，你会看到物体的表面被线条包围，主要为了在调试中更容易地观察  
		scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		HelloWorld* layer = HelloWorld::create();
		//把空间保持我们创建的层中，就是上面所说m_world的作用，方便后面设置空间的参数  
		layer->m_world = scene->getPhysicsWorld();
		scene->addChild(layer);
		return scene;
	}
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /**  you can create scene with following comment code instead of using csb file.
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
    **/
	
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Card.plist", "Card.png");


	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		ballOne = Sprite::createWithSpriteFrameName("img_card_00.png");
		ballOne->setPosition(visibleSize.width / 2+100, visibleSize.height / 2);
		//创建物体，并且物体的形状为圆形，第一参数为半径，第二个参数为物体材质  
		//第三个参数为边的厚度,就是在Debug模式下看到的物体外面线条的厚度，默认为0  
		PhysicsBody* ballBodyOne = PhysicsBody::createBox(ballOne->getContentSize() , PHYSICSBODY_MATERIAL_DEFAULT);
		//是否设置物体为静态  
		//ballBody->setDynamic(false);  
		//设置物体的恢复力  
		ballBodyOne->getShape(0)->setRestitution(1.0f);
		//设置物体的摩擦力  
		ballBodyOne->getShape(0)->setFriction(0.0f);
		//设置物体密度  
		ballBodyOne->getShape(0)->setDensity(1.0f);
		//设置质量  
		//ballBodyOne->getShape(0)->setMass(5000);  
		//设置物体是否受重力系数影响  
		ballBodyOne->setGravityEnable(false);

		//设置物体的冲力  
		//Vect force = Vect(5000000.0f, 500000.0f);
		Vect force = Vect(0, 5000000.0f);
		ballBodyOne->applyImpulse(force);
		//把物体添加到精灵中  
		ballOne->setPhysicsBody(ballBodyOne);
		//设置标志  
		ballOne->setTag(1);
		this->addChild(ballOne);
		//ballOne->runAction(MoveTo::create(2, Vec2(visibleSize.width / 2 + 100, 600)));
		

		//设置第二个球  
		ballTwo = Sprite::createWithSpriteFrameName("img_card_00.png");
		ballTwo->setPosition(visibleSize.width / 3, visibleSize.height / 3);
		PhysicsBody* ballBodyTwo = PhysicsBody::createBox(ballOne->getContentSize() , PHYSICSBODY_MATERIAL_DEFAULT);
		//是否设置物体为静态  
		//ballBodyTwo->setDynamic(false);  
		ballBodyTwo->getShape(0)->setRestitution(1.0f);
		ballBodyTwo->getShape(0)->setFriction(0.0f);
		ballBodyTwo->getShape(0)->setDensity(1.0f);

		ballBodyTwo->setGravityEnable(false);

		//ballTwo->runAction(MoveTo::create(2, Vec2(visibleSize.width / 3, 600)));


		force = Vect(-0, -5000000.0f);
		ballBodyTwo->applyImpulse(force);
		ballTwo->setPhysicsBody(ballBodyTwo);
		ballTwo->setTag(2);
		this->addChild(ballTwo);

		//创建一个盒子，用来碰撞  
		Sprite* edgeSpace = Sprite::create();
		PhysicsBody* boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
		boundBody->getShape(0)->setFriction(0.0f);
		boundBody->getShape(0)->setRestitution(1.0f);

		edgeSpace->setPhysicsBody(boundBody);
		edgeSpace->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(edgeSpace);
		edgeSpace->setTag(0);
		
		boundBody->setCategoryBitmask(0x0001);
		boundBody->setCollisionBitmask(0x0001);
		boundBody->setContactTestBitmask(0x0001);

		ballBodyOne->setCategoryBitmask(0x0001);
		ballBodyOne->setCollisionBitmask(0x0001);
		ballBodyOne->setContactTestBitmask(0x0001);

		ballBodyTwo->setCategoryBitmask(0x0001);
		ballBodyTwo->setCollisionBitmask(0x0001);
		ballBodyTwo->setContactTestBitmask(0x0001);
		/*
		categoryBitmask：
		分类掩码，定义了物体属于哪个分类。场景中的每个物理刚体可以被赋值一个多达32位的值(因为categoryBitmask为int型),每个对应32位掩码中的每一位，你在你的游戏中定义掩码值。
		结合collisionBitMask和contactTestBitMask属性， 你可以定义哪些物理刚体相互作用并且你的游戏何时接受这些相互作用的通知。默认值为0xFFFFFFFF(所有位都被设置)。
		contactTestBitmask：
		接触测试掩码，定义哪些刚体分类可以与本刚体产生相互作用的通知。当两个刚体在同一个空间，即物理世界中，每个刚体的分类掩码会和其他刚体的接触测试掩码进行逻辑与的运算。
		如果任意一个比较结果为非零值，产生一个PhysicsContact对象并且传递到物理世界协议中，这里协议指我们的监听器对应的回调函数。 
		为了最好的性能，仅设置你感兴趣的接触测试掩码中的位，也就是说通过设置接触测试掩码，你可以决定发生碰撞后，回调函数是否有响应。默认值为0x00000000(所有位都被清除)。
		collisionBitmask：
		碰撞掩码，定义了哪些物理刚体分类可以和这个物理刚体发生碰撞。当两个物理刚体相互接触时，可能发生碰撞。这个刚体的碰撞掩码和另一个刚体的分类掩码进行逻辑与运算比较。
		如果结果是一个非零值，这个刚体会发生碰撞。每个刚体独立选择接受与哪个刚体发生碰撞。
		例如，你可以使用此掩码来忽略那些对于本刚体的速度有影响的刚体碰撞，也就是说你可以使用此掩码使得本刚体与某些刚体碰撞不会对本刚体产生影响。
		默认值为0xFFFFFFFF(所有位都被设置)。
		*/
	}
	
    return true;
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	//添加监听器  
	auto contactListener = EventListenerPhysicsContact::create();
	//设置监听器的碰撞开始函数  
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	//添加到事件分发器中  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}


//步中两个形状刚开始第一次接触。回调返回true则会处理正常碰撞，返回false，Chipmunk会完全忽略碰撞。
//如果返回false，则preSolve()和postSolve()回调将永远不会被执行，但你仍然会在形状停止重叠的时候接收到一个单独的事件。

bool HelloWorld::onContactBegin(const PhysicsContact& contact)
{
	Sprite* spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	Sprite* spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();
	if (tagA == 1 && tagB == 2 || tagA == 2 && tagB == 1)
	{
		//spriteA->removeFromParent();
		//spriteB->removeFromParent();
		
	}
	return true;
}


