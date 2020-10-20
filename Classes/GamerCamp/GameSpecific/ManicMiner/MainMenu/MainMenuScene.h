#ifndef _MAINMENUSCENE_H_
#define _MAINMENUSCENE_H_

#include "cocos2d.h"

class CMainMenuSceneLayer : public cocos2d::CCLayer
{
//private:


public:

	CREATE_FUNC( CMainMenuSceneLayer );


	virtual bool init();


	void CB_OnGameStartButton( Ref* pSender );


	static cocos2d::Scene* scene();
};


#endif // _MAINMENUSCENE_H_
