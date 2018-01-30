#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"





using namespace cocos2d;
class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();


    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void onEnter();
	bool onContactBegin(const PhysicsContact& contact);
protected:
	Sprite*  ballOne;
	Sprite*  ballTwo;
	PhysicsWorld* m_world;
};

#endif // __HELLOWORLD_SCENE_H__
