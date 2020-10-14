#include "GCLevel.h"
#include <algorithm>
#include <stdlib.h>

#include "Classes/GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "MenuScene.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjPlatform.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjGroupPlatform.h"

#include "AppDelegate.h"

USING_NS_CC;

#define ENABLE_COLLISION_TEST_LOGGING

#if defined (ENABLE_COLLISION_TEST_LOGGING)

#define COLLISIONTESTLOG( str )		CCLOG( str )

#else

#define COLLISIONTESTLOG( str )		/*nothing*/

#endif

GCLevel::GCLevel()
	: IGCGameLayer(GetGCTypeIDOf(GCLevel))
	, m_pcDefaultGCBackground (NULL)
	, m_bResetWasRequested (false)
{
	m_eGameState = EGameState::Running;
}

GCLevel::~GCLevel()
{
}

void GCLevel::VOnEnter()
{
}

void GCLevel::VOnCreate()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	IGCGameLayer::VOnCreate();

	// Creating and Registering the Object Groups //
	m_pcDefaultGCGroupPlatform = new CGCObjGroupPlatform();
	CGCObjectManager::ObjectGroupRegister(m_pcDefaultGCGroupPlatform);

	// Adding a Timer //
	m_pcTimer = new CGCTimer();
	this->addChild(m_pcTimer->GetTimerObj(), 1);

	// Setting up the Background //
	const char* pList_Background = "TexturePacker/Backgrounds/Placeholder/background.plist";
	{
		m_pcDefaultGCBackground = new CGCObjSprite();
		m_pcDefaultGCBackground->CreateSprite(pList_Background);
		m_pcDefaultGCBackground->SetResetPosition( Vec2( visibleSize.width / 2, visibleSize.height / 2 ) );
		m_pcDefaultGCBackground->SetParent( IGCGameLayer::ActiveInstance() );
	}

	// Physics Setup //
	B2dGetWorld()->SetContactListener(this);

	B2dLoadShapesFromPlist("PhysicsEditor/GameShapes.plist");

	// Creating Border //
	{
		f32 PTM_RATIO = IGCGAMELAYER_B2D_PIXELS_PER_METER;

		b2Vec2 b2v2ScreenCentre_Pixels((origin.x + (visibleSize.width * 0.5f)), (origin.y + (visibleSize.height * 0.5f)));
		Vec2 v2ScreenCentre_Pixels((origin.x + (visibleSize.width * 0.5f)), (origin.y + (visibleSize.height * 0.5f)));

		b2BodyDef groundBodyDef;
		groundBodyDef.position = IGCGameLayer::B2dPixelsToWorld(b2v2ScreenCentre_Pixels);
		groundBodyDef.type = b2_kinematicBody;

		b2Body* groundBody = B2dGetWorld()->CreateBody(&groundBodyDef);

		b2PolygonShape groundBox;

		// Bottom
		groundBox.SetAsBox(((visibleSize.width * 0.5f) / PTM_RATIO), 0.5f, b2Vec2(0.0f, -((visibleSize.height * 0.5f) / PTM_RATIO)), 0.0f);
		groundBody->CreateFixture(&groundBox, 0);

		// Top
		groundBox.SetAsBox(((visibleSize.width * 0.5f) / PTM_RATIO), 0.5f, b2Vec2(0.0f, ((visibleSize.height * 0.5f) / PTM_RATIO)), 0.0f);
		groundBody->CreateFixture(&groundBox, 0);

		// Left
		groundBox.SetAsBox(0.5f, ((visibleSize.height * 0.5f) / PTM_RATIO), b2Vec2(-((visibleSize.width * 0.5f) / PTM_RATIO), 0.0f), 0.0f);
		groundBody->CreateFixture(&groundBox, 0);

		// Right
		groundBox.SetAsBox(0.5f, ((visibleSize.height * 0.5f) / PTM_RATIO), b2Vec2(((visibleSize.width * 0.5f) / PTM_RATIO), 0.0f), 0.0f);
		groundBody->CreateFixture(&groundBox, 0);
	}

	// Creating Player //

	// Creating Platformss //
	const u32 uNumColumns = 3;
	const u32 uNumRows = 4;

	float fColumnSpacing = ( visibleSize.width / ( ( (float) uNumColumns + 1.0f ) ) );
	float fRowSpacing = ( visibleSize.height / ( ( (float) uNumRows ) + 1.0f ) );

	float fNextPlatformPos_x = fColumnSpacing;
	float fRowStartPos_y = fRowSpacing;

	for ( u32 uColumn = 0; uColumn < uNumColumns; uColumn++ )
	{
		Vec2 v2NextPlatformPos( fNextPlatformPos_x, fRowStartPos_y );

		for ( u32 uRow = 0; uRow < uNumRows; uRow++ )
		{
			CGCObjPlatform* pPlatform = new CGCObjPlatform();

			pPlatform->SetResetPosition( v2NextPlatformPos );

			v2NextPlatformPos.y += fRowSpacing;
		}

		fNextPlatformPos_x += fColumnSpacing;

	}
}

void GCLevel::VOnUpdate(f32 fTimeStep)
{
	switch (m_eGameState) 
	{
		case (EGameState::Running):
			// Insert Game Logic while Game is Running
			m_pcTimer->TimerUpdate(Director::getInstance()->getFrameRate() / 60);
			if (m_pcTimer->TimerHasEnded())
			{
				m_eGameState = EGameState::Over;
			}
			COLLISIONTESTLOG("Game is Running");
			break;

		case (EGameState::Won):
			// Insert Game Logic while Game is completed
			COLLISIONTESTLOG("Game is Winner");
			break;

		case (EGameState::Over) :
			// Insert Game Logic while Game is Over
			ReplaceScene(TransitionRotoZoom::create(1.0f, CMenuLayer::scene()));
			COLLISIONTESTLOG("Game is Over");
			break;


	}
}

void GCLevel::VOnDestroy()
{
	// De-allocate memory in opposite order of creation //
	delete m_pcTimer;
	m_pcTimer = NULL;

	delete m_pcDefaultGCBackground;
	m_pcDefaultGCBackground = NULL;

	// Don't forget to Unregister Groups Manually! //

	CGCObjectManager::ObjectGroupUnRegister( m_pcDefaultGCGroupPlatform );
	delete m_pcDefaultGCGroupPlatform;
	m_pcDefaultGCGroupPlatform = NULL;

	IGCGameLayer::VOnDestroy();
}

void GCLevel::SetGameState(EGameState newGameState)
{
	m_eGameState = newGameState;
}