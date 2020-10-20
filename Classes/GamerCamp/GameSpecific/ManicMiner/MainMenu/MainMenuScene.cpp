#include "MainMenuScene.h"

USING_NS_CC;

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
Scene* CMainMenuSceneLayer::scene()
{
    // 'scene' is an autorelease object
    Scene* scene = Scene::create();

    // 'layer' is an autorelease object
    // Create the layer
    CMainMenuSceneLayer* layer = CMainMenuSceneLayer::create();

    // Add layer as a child to scene
    scene->addChild( layer );

    // Return the scene
    return scene;
}


bool CMainMenuSceneLayer::init()
{
    


    return true;
}
