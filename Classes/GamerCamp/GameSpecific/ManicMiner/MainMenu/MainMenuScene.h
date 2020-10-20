#ifndef _MAINMENUSCENE_H_
#define _MAINMENUSCENE_H_

#include "cocos2d.h"

class CMainMenuSceneLayer : public cocos2d::CCLayer
{
private:


public:
	// cocos2d-x classes all have a static create() function
	// This macro implements the default behaviour of create()
	// i.e. news an instance, calls init, and calls autorelease 
	CREATE_FUNC( CMainMenuSceneLayer );

	// Explicit constructor - called from the CREATE_FUNC() macro
	// n.b. this must back-chain calls to the base class versions of init()
	// or the behaviour of your code will be 'unexpected'
	virtual bool init();

	// callback passed to the CCMenu system to be called when
	// the Game Start button is pushed
	void CB_OnGameStartButton( Ref* pSender );

	// The cocos2d convention is to have the root layer of a scene
	// be able to create and return a CCScene* (set to autorelease)
	// which has an instance of itself as a child
	static cocos2d::Scene* scene();
};


#endif // _MAINMENUSCENE_H_
