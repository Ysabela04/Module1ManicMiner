#include "MainMenuScene.h"

#include <algorithm>
#include <stdlib.h> 

#include "AppDelegate.h"
#include "GamerCamp/GameSpecific/ManicMiner/Base Level/CLevel.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

// -----

CMainMenuSceneLayer::CMainMenuSceneLayer()
	: IGCGameLayer( GetGCTypeIDOf( CMainMenuSceneLayer ) )
{

}

CMainMenuSceneLayer::~CMainMenuSceneLayer()
{

}

// -----

void CMainMenuSceneLayer::onEnter()
{
	IGCGameLayer::onEnter();
}

void CMainMenuSceneLayer::VOnCreate()
{
	//////////////////////////////////////////////////////////////////////////
	// cache some useful values 
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	// Create the default object group
	IGCGameLayer::VOnCreate();

	// -----

	///////////////////////////////////////////////////////////////////////////
	// Main Menu
	///////////////////////////////////////////////////////////////////////////

	// Game Start (Play Button
	cocos2d::MenuItemImage* pStartItem
		= cocos2d::MenuItemImage::create( "TexturePacker/UI/MainMenu/PlayButton/PlayButtonNormal.png",
			"TexturePacker/UI/MainMenu/PlayButton/PlayButtonSelected.png",
			CC_CALLBACK_1( CMainMenuSceneLayer::Callback_OnGameStartButton, this ) );

	pStartItem->setPosition( cocos2d::Vec2( visibleSize.width / 2, visibleSize.height / 2 ) );
	
	// Quit Button
	cocos2d::MenuItemImage* pQuitItem
		= cocos2d::MenuItemImage::create( "TexturePacker/UI/MainMenu/QuitButton/QuitButtonNormal.png",
			"TexturePacker/UI/MainMenu/QuitButton/QuitButtonSelected.png",
			CC_CALLBACK_1( CMainMenuSceneLayer::Callback_OnQuitButton, this ) );

	pQuitItem->setPosition( cocos2d::Vec2( visibleSize.width / 2  , ( visibleSize.height / 2 ) - 200.0f ) );


	// Create the Main Menu
	cocos2d::Menu* pMenu = cocos2d::Menu::create( pStartItem, pQuitItem, nullptr );
	pMenu->setPosition( cocos2d::Vec2::ZERO );
	this->addChild( pMenu, 1 );

	//////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// Labels
	///////////////////////////////////////////////////////////////////////////

	// Label - Manic Miner
	cocos2d::Label* pLabel = cocos2d::Label::createWithTTF( "MANIC MINER", "fonts/arial.ttf", 100 );

	// Setting the position to be top-centered
	pLabel->setPosition( cocos2d::Vec2( visibleSize.width / 2, visibleSize.height - 200 ) );
	// Setting the colour of the label
	pLabel->setColor( Color3B::WHITE );

	this->addChild( pLabel, 1 );
}


///////////////////////////////////////////////////////////////////////////////
// Game Start Buttom (Play)
///////////////////////////////////////////////////////////////////////////////
void CMainMenuSceneLayer::Callback_OnGameStartButton( Ref* pSender )
{
	// Transition into the CLevel scene
	Director::getInstance()->replaceScene( TransitionRotoZoom::create( 1.0f, TGCGameLayerSceneCreator< CLevel >::CreateScene() ) );
}

///////////////////////////////////////////////////////////////////////////////
// Quit Button
///////////////////////////////////////////////////////////////////////////////
void CMainMenuSceneLayer::Callback_OnQuitButton( Ref* pSender )
{
	// Quit (Close) the game
	Director::getInstance()->end();
}
