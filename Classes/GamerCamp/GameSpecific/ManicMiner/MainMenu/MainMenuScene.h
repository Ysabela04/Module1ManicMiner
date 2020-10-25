#ifndef _MAINMENUSCENE_H_
#define _MAINMENUSCENE_H_

#include "cocos2d.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"

// -----

//////////////////////////////////////////////////////////////////////////
// Class: CMainMenuSceneLayer
//
// This is a class that handles the Main Menu of the game.
//
// It currently has only a simple play button and a quit button.
//
//////////////////////////////////////////////////////////////////////////
class CMainMenuSceneLayer : public IGCGameLayer
{
public:
	CMainMenuSceneLayer();
	~CMainMenuSceneLayer();

	// -----

	//////////////////////////////////////////////////////////////////////////
	// Functions
	//////////////////////////////////////////////////////////////////////////
	void Callback_OnGameStartButton( Ref* pSender );
	void Callback_OnQuitButton( Ref* pSender );

	//////////////////////////////////////////////////////////////////////////
    // Virtual Functions
    //
	virtual void onEnter();
	virtual	void VOnCreate( void );
};

#endif // _MAINMENUSCENE_H_
