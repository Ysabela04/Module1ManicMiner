#include "CLevel.h"
#include <algorithm>
#include <stdlib.h>

#include "Classes/GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "MenuScene.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjPlatform.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjGroupPlatform.h"
#include "GamerCamp/GameSpecific/ManicMiner/Collectables/Collectable.h"
#include "GamerCamp/GameSpecific/ManicMiner/Collectables/GroupCollectables.h"
#include "GamerCamp/GameSpecific/Player/GCObjGroupProjectilePlayer.h"
#include "GamerCamp/GameSpecific/Player/GCObjProjectilePlayer.h"
#include "GamerCamp/GameSpecific/ScreenBounds/GCObjScreenBound.h"
#include "GamerCamp/GameSpecific/ManicMiner/Player/CPlayer.h"
#include "GamerCamp/GameSpecific/ManicMiner/Exit/Exit.h"
#include "GamerCamp/GameSpecific/ManicMiner/Hazards/GroupHazards.h"
#include "GamerCamp/GameSpecific/ManicMiner/Hazards/Hazard.h"
#include "GamerCamp/GameSpecific/ManicMiner/Timer/CTimer.h"
#include "GamerCamp/GameSpecific/ManicMiner/Enemy/CEnemy.h"
#include "GamerCamp/GameSpecific/ManicMiner/Enemy/CEnemyGroup.h"
#include "GamerCamp/GameSpecific/ManicMiner/Player/Life.h"

#include "AppDelegate.h"

USING_NS_CC;

using namespace cocos2d;

#define ENABLE_COLLISION_TEST_LOGGING

#if defined (ENABLE_COLLISION_TEST_LOGGING)

#define COLLISIONTESTLOG( str )		CCLOG( str )

#else

#define COLLISIONTESTLOG( str )		/*nothing*/

#endif

CLevel::CLevel()
	: IGCGameLayer						( GetGCTypeIDOf ( CLevel ) )
	, m_pcDefaultGCBackground			( nullptr )
	, m_pcGCGroupProjectilePlayer		( nullptr )
	, m_eGameState						( EGameState::Running )
	, m_pcGroupCollectables				( nullptr )
	, m_pcPlayer						( nullptr )
	, m_pcExit							( nullptr )
	, m_pcGroupHazards					( nullptr )
	, m_iCollectablesNeeded				( 5 )
	, m_bResetWasRequested				( false )
	, m_pcEnemyGroup					( nullptr )
	, m_pcPlayerLives					( nullptr)
{
}

CLevel::~CLevel()
{
}

void CLevel::onEnter()
{
	IGCGameLayer::onEnter();

	//////////////////////////////////////////////////////////////////////////
	// init the actions
	// N.B. these 
	cocos2d::EventKeyboard::KeyCode aeKeyCodesForActions[] =
	{
		EventKeyboard::KeyCode::KEY_UP_ARROW,		// EPA_Up,
		EventKeyboard::KeyCode::KEY_DOWN_ARROW,		// EPA_Down,
		EventKeyboard::KeyCode::KEY_LEFT_ARROW,		// EPA_Left,		
		EventKeyboard::KeyCode::KEY_RIGHT_ARROW,	// EPA_Right,
		EventKeyboard::KeyCode::KEY_SPACE,			// EPA_Fire	
	};

	u32 uSizeOfActionArray = (sizeof(aeKeyCodesForActions) / sizeof(cocos2d::EventKeyboard::KeyCode));

	// call base class function	to init the keyboard manager
	AppDelegate::InitialiseKeyboardManager(uSizeOfActionArray, aeKeyCodesForActions);
}

void CLevel::VOnCreate()
{
	// Helpful Information
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	IGCGameLayer::VOnCreate();

	// Creating and Registering the Object Groups //
	m_pcDefaultGCGroupPlatform = new CGCObjGroupPlatform();
	CGCObjectManager::ObjectGroupRegister(m_pcDefaultGCGroupPlatform);

	m_pcGCGroupProjectilePlayer = new CGCObjGroupProjectilePlayer();
	CGCObjectManager::ObjectGroupRegister(m_pcGCGroupProjectilePlayer);

	// Create number of colleactables needed and set the position of each one
	m_pcGroupCollectables = new CGroupCollectables();// 1 );
	CGCObjectManager::ObjectGroupRegister(m_pcGroupCollectables);
	//m_pcGroupCollectables->getpaCollectables( 0 )->SetResetPosition( cocos2d::Vec2( 100.0f, 200.0f ) );
	//m_pcGroupCollectables->getpaCollectables( 1 )->SetResetPosition( cocos2d::Vec2( 250.0f, 450.0f ) );
	//m_pcGroupCollectable->getpaCollectables( 1 )->SetResetPosition( cocos2d::Vec2( 100.0f, 200.0f ) );
	
	m_pcEnemyGroup = new CEnemyGroup( 64 );
	CGCObjectManager::ObjectGroupRegister( m_pcEnemyGroup );

	// Create the CGroupHazards and set the position of the 5 CHazards
	m_pcGroupHazards = new CGroupHazards( cocos2d::Vec2( 100.0f, 100.0f ),
										  cocos2d::Vec2( 250.0f, 350.0f ),
										  cocos2d::Vec2( 550.0f, 450.0f ),
										  cocos2d::Vec2( 750.0f, 250.0f ),
										  cocos2d::Vec2( 650.0f, 200.0f ) );
	CGCObjectManager::ObjectGroupRegister( m_pcGroupHazards );
	
	// Adding a Timer //
	m_pcTimer = new CTimer();
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
	B2dGetWorld()->SetContactListener( this );

	B2dLoadShapesFromPlist( "PhysicsEditor/GameShapes.plist" );

	// Creating Screen Boundary//
	Vec2 v2ScreenCentre_Pixels((origin.x + (visibleSize.width * 0.5f)), (origin.y + (visibleSize.height * 0.5f)));
	Vec2 v2ScreenCentre_B2d = B2dPixelsToWorld(v2ScreenCentre_Pixels);

	f32 fScreenWidthB2d = B2dPixelsToWorld(visibleSize.width);
	f32 fHalfScreenWidthB2d = (fScreenWidthB2d / 2.0f);

	f32 fScreenHeightB2d = B2dPixelsToWorld(visibleSize.height);
	f32 fHalfScreenHeightB2d = (fScreenHeightB2d / 2.0f);

	new CGCObjScreenBound(CGCObjScreenBound::EScreenBoundType::Bottom, (v2ScreenCentre_B2d + Vec2(0.0f, -fHalfScreenHeightB2d)), fScreenWidthB2d, 0.5f, 0.0f);
	new CGCObjScreenBound(CGCObjScreenBound::EScreenBoundType::Top, (v2ScreenCentre_B2d + Vec2(0.0f, fHalfScreenHeightB2d)), fScreenWidthB2d, 0.5f, 0.0f);
	new CGCObjScreenBound(CGCObjScreenBound::EScreenBoundType::Left, (v2ScreenCentre_B2d + Vec2(-fHalfScreenWidthB2d, 0.0f)), 0.5f, fScreenHeightB2d, 0.0f);
	new CGCObjScreenBound(CGCObjScreenBound::EScreenBoundType::Right, (v2ScreenCentre_B2d + Vec2(fHalfScreenWidthB2d, 0.0f)), 0.5f, fScreenHeightB2d, 0.0f);
	//{
	//	f32 PTM_RATIO = IGCGAMELAYER_B2D_PIXELS_PER_METER;

	//	b2Vec2 b2v2ScreenCentre_Pixels((origin.x + (visibleSize.width * 0.5f)), (origin.y + (visibleSize.height * 0.5f)));
	//	Vec2 v2ScreenCentre_Pixels((origin.x + (visibleSize.width * 0.5f)), (origin.y + (visibleSize.height * 0.5f)));

	//	b2BodyDef groundBodyDef;
	//	groundBodyDef.position = IGCGameLayer::B2dPixelsToWorld(b2v2ScreenCentre_Pixels);
	//	groundBodyDef.type = b2_kinematicBody;

	//	b2Body* groundBody = B2dGetWorld()->CreateBody(&groundBodyDef);

	//	b2PolygonShape groundBox;

	//	// Bottom
	//	groundBox.SetAsBox(((visibleSize.width * 0.5f) / PTM_RATIO), 0.5f, b2Vec2(0.0f, -((visibleSize.height * 0.5f) / PTM_RATIO)), 0.0f);
	//	groundBody->CreateFixture(&groundBox, 0);

	//	// Top
	//	groundBox.SetAsBox(((visibleSize.width * 0.5f) / PTM_RATIO), 0.5f, b2Vec2(0.0f, ((visibleSize.height * 0.5f) / PTM_RATIO)), 0.0f);
	//	groundBody->CreateFixture(&groundBox, 0);

	//	// Left
	//	groundBox.SetAsBox(0.5f, ((visibleSize.height * 0.5f) / PTM_RATIO), b2Vec2(-((visibleSize.width * 0.5f) / PTM_RATIO), 0.0f), 0.0f);
	//	groundBody->CreateFixture(&groundBox, 0);

	//	// Right
	//	groundBox.SetAsBox(0.5f, ((visibleSize.height * 0.5f) / PTM_RATIO), b2Vec2(((visibleSize.width * 0.5f) / PTM_RATIO), 0.0f), 0.0f);
	//	groundBody->CreateFixture(&groundBox, 0);
	//}

	// Creating Player //
	Vec2 v2MarioStartPos = (v2ScreenCentre_Pixels - Vec2(0.0f, (visibleSize.height * 0.45f)));

	m_pcPlayer = new CPlayer();
	m_pcPlayer->SetResetPosition(v2MarioStartPos);

	// Player lives
	m_pcPlayerLives = new CLife[3];

	float PosX = 850.0f;
	float PosY = 650.0f;
	float PosXIncrease = 50.0f;	

	for (int i = 0; i < m_pcPlayer->getiLives(); i++)
	{
		Vec2 v2LivesPos( PosX, PosY );
		m_pcPlayerLives[i].SetResetPosition( v2LivesPos );
		PosX += PosXIncrease;

		//m_pcPlayerLives->SetVisible( true );
	}

	// Creating Exit //
	m_pcExit = new CExit();
	m_pcExit->SetResetPosition( Vec2( 100.0f, 65.0f ) );


	// Creating Platforms //
	const u32 uNumColumns = 3;
	const u32 uNumRows = 4;
	
	// Creating Enemy //
	m_pcEnemyGroup->SetFormationOrigin( v2ScreenCentre_Pixels + Vec2( -( visibleSize.width * 0.25f ), ( visibleSize.height * 0.25f ) ) );
	m_pcEnemyGroup->SetRowsAndColumns( 1, 1, -40.0f, 40.0f );


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

	// Adding in Collision Handlers //

	// Collision for Player and Collectable
	GetCollisionManager().AddCollisionHandler
	(
		[this]
		( CPlayer& rcPlayer, CCollectable& rcCollectable, const b2Contact& rcContact ) -> void
		{
			// check if the player is not collecting anything else before collecting the item, then get the value of the collectable
			// and increase the players itemscollected
			if (m_pcPlayer->getbIsCollecting() == false)
			{
				m_pcPlayer->setbIsCollecting(true);
				m_pcPlayer->IncreaseItemCollected(rcCollectable.getiRewardValue());
				CGCObjectManager::ObjectKill(&rcCollectable);
				CCLOG("Player Item Collected");
			}
		}
	);

	// Collisions for Player and Exit
	GetCollisionManager().AddCollisionHandler
	(
		[this]
		(CPlayer& rcPlayer, CExit& rcExit, const b2Contact& rcContact) -> void
		{
			if (m_pcExit->getIsOpen() == true)
			{
				m_eGameState = EGameState::Won;
			}
		}
	);

	// Collisions for Player and Hazard
	GetCollisionManager().AddCollisionHandler
	(
		[this]
		(CPlayer& rcPlayer, CHazard& rcHazard, const b2Contact& rcContact) -> void
		{
			if (m_pcPlayer->getbIsColliding() == false)
			{
				m_pcPlayer->setbIsColliding(true);
				m_pcPlayer->DecreaseLife();

				RequestReset();

				CCLOG("Player hit Hazard!");
			}
		}
	);
	
	// Collisions for Player and Enemy
	GetCollisionManager().AddCollisionHandler
	(
		[this]
	(CPlayer& rcPlayer, CEnemy& rcEnemy, const b2Contact& rcContact) -> void
		{
			if (m_pcPlayer->getbIsColliding() == false)
			{
				m_pcPlayer->setbIsColliding(true);
				m_pcPlayer->DecreaseLife();

				RequestReset();

				CCLOG("Player hit Enemy!");
			}
		}
	);
}
// End VOnCreate();

void CLevel::VOnUpdate(f32 fTimeStep)
{
	IGCGameLayer::VOnUpdate(fTimeStep);

	if (ResetWasRequested())
		{
			VOnReset();
			ResetRequestWasHandled();
		}

	switch (m_eGameState) 
	{
		case (EGameState::Running):
			// Insert Game Logic while Game is Running
			WinCondition();

			m_pcTimer->TimerUpdate(Director::getInstance()->getFrameRate() / 60);
			if (m_pcTimer->TimerHasEnded() || m_pcPlayer->getiLives() <= 0)
			{
				m_eGameState = EGameState::Over;
			}

			ManuallyHandleCollisions();

			UpdatePlayerLives();

			m_pcPlayer->setbIsCollecting(false);
			m_pcPlayer->setbIsColliding(false);

			COLLISIONTESTLOG("Game is Running");
			break;

		case (EGameState::Collected):
			m_pcTimer->TimerUpdate(Director::getInstance()->getFrameRate() / 60);
			if (m_pcTimer->TimerHasEnded() || m_pcPlayer->getiLives() <= 0)
			{
				m_eGameState = EGameState::Over;
			}

			m_pcExit->setIsOpen(true);

			ManuallyHandleCollisions();

			m_pcPlayer->setbIsCollecting(false);
			m_pcPlayer->setbIsColliding(false);

			COLLISIONTESTLOG("Game has Collected All Objects");
			break;

		case (EGameState::Won):
			// Insert Game Logic while Game is completed
			ReplaceScene(TransitionRotoZoom::create(1.0f, CMenuLayer::scene()));
			COLLISIONTESTLOG("Game is Winner");
			break;

		case (EGameState::Over) :
			// Insert Game Logic while Game is Over
			ReplaceScene(TransitionRotoZoom::create(1.0f, CMenuLayer::scene()));
			COLLISIONTESTLOG("Game is Over");
			break;

			
	}
}

void CLevel::VOnDestroy()
{
	// De-allocate memory in opposite order of creation //
	delete m_pcPlayer;
	m_pcPlayer = nullptr;

	delete[] m_pcPlayerLives;
	m_pcPlayerLives = nullptr;

	delete m_pcExit;
	m_pcExit = nullptr;

	//delete m_pcHazard;
	//m_pcHazard = nullptr;

	delete m_pcTimer;
	m_pcTimer = nullptr;
	
	//delete m_pcEnemyGroup;
	//m_pcEnemyGroup = nullptr;

	delete m_pcDefaultGCBackground;
	m_pcDefaultGCBackground = nullptr;

	// Don't forget to Unregister Groups Manually! //

	CGCObjectManager::ObjectGroupUnRegister( m_pcDefaultGCGroupPlatform );
	delete m_pcDefaultGCGroupPlatform;
	m_pcDefaultGCGroupPlatform = nullptr;

	CGCObjectManager::ObjectGroupUnRegister(m_pcGCGroupProjectilePlayer);
	delete m_pcGCGroupProjectilePlayer;
	m_pcGCGroupProjectilePlayer = nullptr;

	CGCObjectManager::ObjectGroupUnRegister( m_pcGroupCollectables );
	delete m_pcGroupCollectables;
	m_pcGroupCollectables = nullptr;

	CGCObjectManager::ObjectGroupUnRegister( m_pcGroupHazards );
	delete m_pcGroupHazards;
	m_pcGroupHazards = nullptr;
	
	CGCObjectManager::ObjectGroupUnRegister(m_pcEnemyGroup);
	delete m_pcEnemyGroup;
	m_pcEnemyGroup = nullptr;

	IGCGameLayer::VOnDestroy();
}

///////////////////////////////////////////////////////////////////////////////
// begin contact
// insert any logic that relies on detecting the first frame where a 
// contact exists
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CLevel::BeginContact(b2Contact* pB2Contact)
{
}

///////////////////////////////////////////////////////////////////////////////
// end contact
// insert any logic that relies on detecting the last frame where a 
// contact exists
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CLevel::EndContact(b2Contact* pB2Contact)
{
}

///////////////////////////////////////////////////////////////////////////////
// pre solve
// insert any logic that needs to be done before a contact is resolved
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CLevel::PreSolve(b2Contact* pB2Contact, const b2Manifold* pOldManifold)
{
	const b2Fixture* pFixtureA = pB2Contact->GetFixtureA();
	const b2Fixture* pFixtureB = pB2Contact->GetFixtureB();

	const b2Body* pBodyA = pFixtureA->GetBody();
	const b2Body* pBodyB = pFixtureB->GetBody();

	CGCObjSpritePhysics* pGcSprPhysA = (CGCObjSpritePhysics*)pBodyA->GetUserData();
	// if( this is not a GC object )
	if (pGcSprPhysA == nullptr)
	{
		return;
	}

	CGCObjSpritePhysics* pGcSprPhysB = (CGCObjSpritePhysics*)pBodyB->GetUserData();
	// if( this is not a GC object )
	if (pGcSprPhysB == nullptr)
	{
		return;
	}
}

///////////////////////////////////////////////////////////////////////////////
// post solve
// insert any logic that needs to be done after a contact is resolved
// e.g. check the types and double the impulse
///////////////////////////////////////////////////////////////////////////////
//virtual 
void CLevel::PostSolve(b2Contact* pB2Contact, const b2ContactImpulse* pImpulse)
{
}

void CLevel::ManuallyHandleCollisions()
{
	for (const b2Contact* pB2Contact = IGCGameLayer::ActiveInstance()->B2dGetWorld()->GetContactList();
		nullptr != pB2Contact;
		pB2Contact = pB2Contact->GetNext())
	{
		const b2Fixture* pFixtureA = CGCObjSpritePhysics::FromB2DContactGetFixture_A(pB2Contact);
		const b2Fixture* pFixtureB = CGCObjSpritePhysics::FromB2DContactGetFixture_B(pB2Contact);

		// return if either physics body has null user data
		CGCObjSpritePhysics* pGcSprPhysA = CGCObjSpritePhysics::FromB2DFixtureGetSpritePhysics(pFixtureA);
		if (!pGcSprPhysA)
		{
			return;
		}

		CGCObjSpritePhysics* pGcSprPhysB = CGCObjSpritePhysics::FromB2DFixtureGetSpritePhysics(pFixtureB);
		if (!pGcSprPhysB)
		{
			return;
		}

		// check for user data - this is defined in physics editor as the 'Id' text
		// in the text box immediately below the 'Is Sensor?' checkbox
		// 
		// Mario has a fixture that is a sensor with id 'bottom_left' 
		// and this is what we're checking for - put a breakpoint on 
		const std::string* pstrCheckMe = cocos2d::GB2ShapeCache::getFixtureIdText(pFixtureA);
		bool				bNameMatches = (0 == pstrCheckMe->compare("bottom_left"));
		bool				bIsASensor = pFixtureA->IsSensor();

		if (pstrCheckMe && bNameMatches && bIsASensor)
		{
			// put a breakpoint on the next line to see the sensor detection
			int i = 0;
			++i;
		}

		pstrCheckMe = cocos2d::GB2ShapeCache::getFixtureIdText(pFixtureB);
		if (pstrCheckMe
			&& (0 == pstrCheckMe->compare("bottom_left"))
			&& pFixtureB->IsSensor())
		{
			int i = 0;
			++i;
		}
	}
}


void CLevel::UpdatePlayerLives()
{
	for (int i = 2; i >= m_pcPlayer->getiLives(); i--)
	{
		m_pcPlayerLives[i].SetVisible( false );
	}
}

void CLevel::WinCondition()
{
	if (m_pcPlayer->getiItemsCollected() >= m_iCollectablesNeeded)
	{
		m_eGameState = EGameState::Collected;
	}
}

void CLevel::LoseCondition()
{
	if (m_pcPlayer->getiLives() <= 0)
	{
		ReplaceScene(TransitionRotoZoom::create(1.0f, CMenuLayer::scene()));
	}
}

void CLevel::SetGameState(EGameState newGameState)
{
	m_eGameState = newGameState;
}
