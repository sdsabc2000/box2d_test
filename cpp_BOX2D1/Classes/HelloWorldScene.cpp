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
		gravity.Set(0.0f, -10.0f); //һ������10��λ����������Ϊ�������ٶȣ�Box2D��Ĭ�ϵĵ�λ�������  
		mWorld = new b2World(gravity); // ����һ�����������ٶȵ�����  
	

		b2BodyDef bodyDef;   //һ������Ķ���  
		bodyDef.type = b2_staticBody; //��������ͣ������ģ���Ӳ��~ ���԰����������嵱�ɵ���  
		b2PolygonShape borderShape; // һ�����ε���״  
		b2FixtureDef borderFixture; // һ��������  

		//����ذ�  
		bodyDef.position.Set(0, 0); // �ذ���0��0λ��  
		borderShape.SetAsBox(VisibleRect::right().x * PTM_RATIO, 0); //���ó��Ⱥ͸߶ȣ����������ĵذ������X�ᣬ��һ����  
		borderFixture.shape = &borderShape;
		b2Body * bottomBorder = mWorld->CreateBody(&bodyDef); //�������д���һ�����壨���棩  
		bottomBorder->CreateFixture(&borderFixture);          //���Ƶ������״ 

	
	}


		{
			//CCSprite * ball = CCSprite::create("CloseNormal.png"); //С���Ӧ�ľ���  
			CCSprite * ball = CCSprite::createWithSpriteFrameName("img_card_01.png");

			

			ball->setAnchorPoint(ccp(0.5, 0.5));
			ball->setPosition(VisibleRect::center());
			this->addChild(ball);

			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody; //С���ǿ��Զ���  
			bodyDef.userData = ball;    //��ֻ��Ϊ�˱������ݣ�����ͨ�������ҵ���Ӧ�ľ���  
			bodyDef.linearDamping = 0.0f; //���ٶ�Ϊ0  
			bodyDef.position.Set(ball->getPositionX() * PTM_RATIO, ball->getPositionY()* PTM_RATIO); //��ʼλ��  
			mBallBody = mWorld->CreateBody(&bodyDef); // ��Box2D�����д���һ������  

			b2PolygonShape bodyShape;
			//С��Ĵ�С����״~ ���εģ�����Բ�ε�Ӧ����b2CircleShape  ;һ��Ŀ�Ⱥ͸߶�
			bodyShape.SetAsBox(ball->getContentSize().width /2* PTM_RATIO, ball->getContentSize().height/2 * PTM_RATIO); //С��Ĵ�С����״~ ���εģ�����Բ�ε�Ӧ����b2CircleShape  

			b2FixtureDef bodyFixture; //С��Ķ�����  
			bodyFixture.density = 1;  // �ܶ�  
			bodyFixture.shape = &bodyShape; //��״  
			bodyFixture.friction = 0.1f; //Ħ��������Ϊ���������û��������Ħ��������û��  
			bodyFixture.restitution = 1.0f; //������100%����~~~  
			mBallBody->CreateFixture(&bodyFixture);

		}





	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto myListener = EventListenerTouchOneByOne::create();

	//���������˾���Ϣ���ɻ����´���  
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
	//�ٶȵ�������
	int32 velocityIterations = 8;// 10;
	//λ�õ�������
	int32 positionIterations = 8;// 10;

	mWorld->Step(dt, velocityIterations, positionIterations);
	mWorld->ClearForces();

	{
		CCSprite * ball = (CCSprite *)(mBallBody->GetUserData());
		b2Vec2 ballPosition = mBallBody->GetPosition();
		ball->setPosition(ccp(ballPosition.x / PTM_RATIO, ballPosition.y / PTM_RATIO));
	}



}

