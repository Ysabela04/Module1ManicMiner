////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MenuScene.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"


USING_NS_CC;


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
Scene* CMenuLayer::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    CMenuLayer *layer = CMenuLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
bool CMenuLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize	= Director::getInstance()->getVisibleSize();
    Vec2 origin			= Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemImage* pItemStartGame = MenuItemImage::create(
                                        "Loose/CloseNormal.png",
                                        "Loose/CloseSelected.png",
                                        CC_CALLBACK_1( CMenuLayer::CB_OnGameStartButton, this ) );
        
    pItemStartGame->setPosition( Vec2(	origin.x + (visibleSize.width * 0.5f ),
										origin.y + (visibleSize.height * 0.5f ) ) );

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pItemStartGame, nullptr);
    pMenu->setPosition( Vec2::ZERO );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    Label* pLabel = Label::createWithTTF( "Menu - Press Button to Play", "fonts/arial.ttf", 24 );

    // position the label on the center of the screen
    pLabel->setPosition( Vec2(	origin.x + ( visibleSize.width * 0.5f ),
								origin.y + ( visibleSize.height* 0.5f ) + pItemStartGame->getContentSize().height + ( pLabel->getContentSize().height * 0.5f) ));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    Sprite* pSprite = Sprite::create("Loose/HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CMenuLayer::CB_OnGameStartButton( Ref* pSender)
{
	Director::getInstance()->replaceScene( TransitionRotoZoom::create( 1.0f, TGCGameLayerSceneCreator< CGCGameLayerPlatformer >::CreateScene() ) );
}
