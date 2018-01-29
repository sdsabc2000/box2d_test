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
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
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
		b2Vec2 gravity;
		gravity.Set(0.0f, -10.0f); //一个向下10单位的向量，作为重力减速度，Box2D中默认的单位是秒和米  
		mWorld = new b2World(gravity); // 创建一个有重力加速度的世界  
	

		b2BodyDef bodyDef;   //一个物体的定义  
		bodyDef.type = b2_staticBody; //物体的类型，不动的，坚硬的~ 可以把这样的物体当成地面  
		b2PolygonShape borderShape; // 一个方形的形状  
		b2FixtureDef borderFixture; // 一个定制器  

		//定义地板  
		bodyDef.position.Set(0, 0); // 地板在0，0位置  
		borderShape.SetAsBox(VisibleRect::right().x * PTM_RATIO, 0); //设置长度和高度，这里描述的地板就像是X轴，是一条线  
		borderFixture.shape = &borderShape;
		b2Body * bottomBorder = mWorld->CreateBody(&bodyDef); //在世界中创建一个物体（地面）  
		bottomBorder->CreateFixture(&borderFixture);          //定制地面的形状 

	
	}


		{
			//CCSprite * ball = CCSprite::create("CloseNormal.png"); //小球对应的精灵  
			CCSprite * ball = CCSprite::createWithSpriteFrameName("img_card_01.png");

			

			ball->setAnchorPoint(ccp(0.5, 0.5));
			ball->setPosition(VisibleRect::center());
			this->addChild(ball);

			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody; //小球是可以动的  
			bodyDef.userData = ball;    //这只是为了保存数据，可以通过物体找到对应的精灵  
			bodyDef.linearDamping = 0.0f; //初速度为0  
			bodyDef.position.Set(ball->getPositionX() * PTM_RATIO, ball->getPositionY()* PTM_RATIO); //初始位置  
			mBallBody = mWorld->CreateBody(&bodyDef); // 在Box2D世界中创建一个物体  

			b2PolygonShape bodyShape;
			//小球的大小和形状~ 方形的？？？圆形的应该是b2CircleShape  ;一半的宽度和高度
			bodyShape.SetAsBox(ball->getContentSize().width /2* PTM_RATIO, ball->getContentSize().height/2 * PTM_RATIO); //小球的大小和形状~ 方形的？？？圆形的应该是b2CircleShape  

			b2FixtureDef bodyFixture; //小球的定制器  
			bodyFixture.density = 1;  // 密度  
			bodyFixture.shape = &bodyShape; //形状  
			bodyFixture.friction = 0.1f; //摩擦力，因为掉落过程中没有物体间的摩擦，所以没用  
			bodyFixture.restitution = 1.0f; //弹力，100%反弹~~~  
			mBallBody->CreateFixture(&bodyFixture);

		}





	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto myListener = EventListenerTouchOneByOne::create();

	//如果不加入此句消息依旧会向下传递  
	myListener->setSwallowTouches(true);
	


 
	
	// HelloWorld *p = m_pMainScene;
	 myListener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		 

		 Vec2 pt = touch->getLocation();
		 {
			 return true;
		 }
	
		
		return false;
	};

	myListener->onTouchMoved = [&](Touch* touch, Event* event)
	{

	};

	myListener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		
	};

	//dispatcher->addEventListenerWithSceneGraphPriority(myListener, m_pCardNode);

	scheduleUpdate();

    return true;
}


void HelloWorld::update(float dt)
{
	//速度迭代次数
	int32 velocityIterations = 8;// 10;
	//位置迭代次数
	int32 positionIterations = 8;// 10;

	mWorld->Step(dt, velocityIterations, positionIterations);
	mWorld->ClearForces();

	{
		CCSprite * ball = (CCSprite *)(mBallBody->GetUserData());
		b2Vec2 ballPosition = mBallBody->GetPosition();
		ball->setPosition(ccp(ballPosition.x / PTM_RATIO, ballPosition.y / PTM_RATIO));
	}



}

