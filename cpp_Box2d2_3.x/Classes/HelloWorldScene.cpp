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
		//����������ռ�ĳ���  
		Scene* scene = Scene::createWithPhysics();
		//����Debugģʽ����ῴ������ı��汻������Χ����ҪΪ���ڵ����и����׵ع۲�  
		scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		HelloWorld* layer = HelloWorld::create();
		//�ѿռ䱣�����Ǵ����Ĳ��У�����������˵m_world�����ã�����������ÿռ�Ĳ���  
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
		//�������壬�����������״ΪԲ�Σ���һ����Ϊ�뾶���ڶ�������Ϊ�������  
		//����������Ϊ�ߵĺ��,������Debugģʽ�¿������������������ĺ�ȣ�Ĭ��Ϊ0  
		PhysicsBody* ballBodyOne = PhysicsBody::createBox(ballOne->getContentSize() , PHYSICSBODY_MATERIAL_DEFAULT);
		//�Ƿ���������Ϊ��̬  
		//ballBody->setDynamic(false);  
		//��������Ļָ���  
		ballBodyOne->getShape(0)->setRestitution(1.0f);
		//���������Ħ����  
		ballBodyOne->getShape(0)->setFriction(0.0f);
		//���������ܶ�  
		ballBodyOne->getShape(0)->setDensity(1.0f);
		//��������  
		//ballBodyOne->getShape(0)->setMass(5000);  
		//���������Ƿ�������ϵ��Ӱ��  
		ballBodyOne->setGravityEnable(false);

		//��������ĳ���  
		//Vect force = Vect(5000000.0f, 500000.0f);
		Vect force = Vect(0, 5000000.0f);
		ballBodyOne->applyImpulse(force);
		//��������ӵ�������  
		ballOne->setPhysicsBody(ballBodyOne);
		//���ñ�־  
		ballOne->setTag(1);
		this->addChild(ballOne);
		//ballOne->runAction(MoveTo::create(2, Vec2(visibleSize.width / 2 + 100, 600)));
		

		//���õڶ�����  
		ballTwo = Sprite::createWithSpriteFrameName("img_card_00.png");
		ballTwo->setPosition(visibleSize.width / 3, visibleSize.height / 3);
		PhysicsBody* ballBodyTwo = PhysicsBody::createBox(ballOne->getContentSize() , PHYSICSBODY_MATERIAL_DEFAULT);
		//�Ƿ���������Ϊ��̬  
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

		//����һ�����ӣ�������ײ  
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
		categoryBitmask��
		�������룬���������������ĸ����ࡣ�����е�ÿ�����������Ա���ֵһ�����32λ��ֵ(��ΪcategoryBitmaskΪint��),ÿ����Ӧ32λ�����е�ÿһλ�����������Ϸ�ж�������ֵ��
		���collisionBitMask��contactTestBitMask���ԣ� ����Զ�����Щ��������໥���ò��������Ϸ��ʱ������Щ�໥���õ�֪ͨ��Ĭ��ֵΪ0xFFFFFFFF(����λ��������)��
		contactTestBitmask��
		�Ӵ��������룬������Щ�����������뱾��������໥���õ�֪ͨ��������������ͬһ���ռ䣬�����������У�ÿ������ķ�����������������ĽӴ�������������߼�������㡣
		�������һ���ȽϽ��Ϊ����ֵ������һ��PhysicsContact�����Ҵ��ݵ���������Э���У�����Э��ָ���ǵļ�������Ӧ�Ļص������� 
		Ϊ����õ����ܣ������������Ȥ�ĽӴ����������е�λ��Ҳ����˵ͨ�����ýӴ��������룬����Ծ���������ײ�󣬻ص������Ƿ�����Ӧ��Ĭ��ֵΪ0x00000000(����λ�������)��
		collisionBitmask��
		��ײ���룬��������Щ������������Ժ����������巢����ײ����������������໥�Ӵ�ʱ�����ܷ�����ײ������������ײ�������һ������ķ�����������߼�������Ƚϡ�
		��������һ������ֵ���������ᷢ����ײ��ÿ���������ѡ��������ĸ����巢����ײ��
		���磬�����ʹ�ô�������������Щ���ڱ�������ٶ���Ӱ��ĸ�����ײ��Ҳ����˵�����ʹ�ô�����ʹ�ñ�������ĳЩ������ײ����Ա��������Ӱ�졣
		Ĭ��ֵΪ0xFFFFFFFF(����λ��������)��
		*/
	}
	
    return true;
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	//��Ӽ�����  
	auto contactListener = EventListenerPhysicsContact::create();
	//���ü���������ײ��ʼ����  
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	//��ӵ��¼��ַ�����  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}


//����������״�տ�ʼ��һ�νӴ����ص�����true��ᴦ��������ײ������false��Chipmunk����ȫ������ײ��
//�������false����preSolve()��postSolve()�ص�����Զ���ᱻִ�У�������Ȼ������״ֹͣ�ص���ʱ����յ�һ���������¼���

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


