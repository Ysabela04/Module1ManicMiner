#ifndef _MAINMENUSCENE_H_
#define _MAINMENUSCENE_H_

#include "cocos2d.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

class CMainMenuSceneLayer : public IGCGameLayer
{
private:


public:
	CMainMenuSceneLayer();
	~CMainMenuSceneLayer();

	// -----

	void Callback_OnGameStartButton( Ref* pSender );
	void Callback_OnQuitButton( Ref* pSender );

	virtual void onEnter();

	virtual	void VOnCreate( void );

};


#endif // _MAINMENUSCENE_H_
