#include "CLevel.h"
#include <algorithm>
#include <stdlib.h>

#include "Classes/GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "MenuScene.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/GCObjSprite.h"
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
#include "GamerCamp/GameSpecific/ManicMiner/Sound/CSoundManager.h"
#include "GamerCamp/GameSpecific/ManicMiner/Player/Life.h"
#include "GamerCamp/GameSpecific/ManicMiner/MainMenu/MainMenuScene.h"
#include "GamerCamp/GameSpecific/ManicMiner/Platform/CPlatform.h"
#include "GamerCamp/GameSpecific/ManicMiner/Platform/CPlatformGroup.h"
#include "GamerCamp/GameSpecific/ManicMiner/Platform/CDisappearPlatform.h"
#include "GamerCamp/GameSpecific/ManicMiner/Score/CScore.h"

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
	, m_pcUIBar							( nullptr )
	, m_pcGCGroupProjectilePlayer		( nullptr )
	, m_eGameState						( EGameState::Running )
	, m_pcGroupCollectables				( nullptr )
	, m_pcPlayer						( nullptr )
	, m_pcExit							( nullptr )
	, m_pcGroupHazards					( nullptr )
	, m_iCollectablesNeeded				( 5 )
	, m_iScore							(0)
	, m_bResetWasRequested				( false )
	, m_pcEnemyGroup					( nullptr )
	, m_pcSoundManager					( nullptr )
	, m_pcaPlayerLives					( nullptr )
	, m_pcPlatformGroup 				( nullptr )
	, m_pcBottomPlatforms				( nullptr )
	, m_pcFirstRowPlatforms				( nullptr )
	, m_pcSecondRowPlatforms			( nullptr )
	, m_pcThirdRowPlatforms				( nullptr )
	, m_pcFourthRowPlatforms			( nullptr )
	, m_pcFifthRowPlatforms				( nullptr )
	, m_pcSixthRowPlatforms				( nullptr )
	, m_pcSeventhRowPlatforms           		( nullptr )
	, m_pcEighthRowPlatforms			( nullptr )
	, m_pcNinthRowPlatforms				( nullptr )
	, m_pcTenthRowPlatforms				( nullptr )
	, m_pcDisappearPlatforms			( nullptr )
		
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
	m_pcPlatformGroup = new CPlatformGroup();
	CGCObjectManager::ObjectGroupRegister(m_pcPlatformGroup);

	m_pcGCGroupProjectilePlayer = new CGCObjGroupProjectilePlayer();
	CGCObjectManager::ObjectGroupRegister(m_pcGCGroupProjectilePlayer);

	// Create number of colleactables needed and set the position of each one
	m_pcGroupCollectables = new CGroupCollectables( cocos2d::Vec2( 570.0f, 930.0f ),
													cocos2d::Vec2( 990.0f, 870.0f ),
													cocos2d::Vec2( 1470.0f, 690.0f ),
													cocos2d::Vec2( 1770.0f, 930.0f ),
													cocos2d::Vec2( 1830.0f, 570.0f ) );
	// 1 );
	CGCObjectManager::ObjectGroupRegister(m_pcGroupCollectables);
	//m_pcGroupCollectables->getpaCollectables( 0 )->SetResetPosition( cocos2d::Vec2( 100.0f, 200.0f ) );
	//m_pcGroupCollectables->getpaCollectables( 1 )->SetResetPosition( cocos2d::Vec2( 250.0f, 450.0f ) );
	//m_pcGroupCollectable->getpaCollectables( 1 )->SetResetPosition( cocos2d::Vec2( 100.0f, 200.0f ) );
	
	// Create Enemy group 
	m_pcEnemyGroup = new CEnemyGroup( 64 );
	CGCObjectManager::ObjectGroupRegister( m_pcEnemyGroup );

	// Create the CGroupHazards and set the position of the 5 CHazards
	m_pcGroupHazards = new CGroupHazards( cocos2d::Vec2( 690.0f, 930.0f ),
										  cocos2d::Vec2( 750.0f, 210.0f ),
										  cocos2d::Vec2( 990.0f, 930.0f ),
										  cocos2d::Vec2( 1290.0f, 450.0f ),
										  cocos2d::Vec2( 1410.0f, 690.0f ),
										  cocos2d::Vec2( 1650.0f, 690.0f ) );
	CGCObjectManager::ObjectGroupRegister( m_pcGroupHazards );
	
	// Sound Manager //
	m_pcSoundManager = new CSoundManager();
	m_pcSoundManager->PlayBackgroundMusic();

	// Adding a Timer //
	m_pcTimer = new CTimer();
	this->addChild(m_pcTimer->GetTimerObj(), 1);

	// Adding the Score text //
	m_pcScore = new CScore();
	this->addChild(m_pcScore->GetScoreObj(), 1);

	// Setting up the Background //
	const char* pList_Background = "TexturePacker/Backgrounds/Placeholder/OceanBG.plist";
	{
		m_pcDefaultGCBackground = new CGCObjSprite();
		m_pcDefaultGCBackground->CreateSprite(pList_Background);
		m_pcDefaultGCBackground->SetResetPosition( Vec2( visibleSize.width / 2, visibleSize.height / 2 ) );
		m_pcDefaultGCBackground->SetParent( IGCGameLayer::ActiveInstance() );
	}


	// UI Bar Blank - Placeholder Art
	const char* pList_UIBar = "TexturePacker/UI/UIBar/UIBarBlank.plist";
	{
		m_pcUIBar = new CGCObjSprite();
		m_pcUIBar->CreateSprite( pList_UIBar );
		m_pcUIBar->SetResetPosition( Vec2( visibleSize.width / 2, 1020.0f ) );
		m_pcUIBar->SetParent( IGCGameLayer::ActiveInstance() );
	}


	// Physics Setup //
	B2dGetWorld()->SetContactListener( this );

	B2dLoadShapesFromPlist( "PhysicsEditor/GameShapes.plist" );

	// Creating Screen Boundary//
		Vec2 v2ScreenCentre_Pixels((origin.x + (visibleSize.width * 0.5f)), (origin.y + (visibleSize.height * 0.5f)));
		Vec2 v2ScreenCentre_B2d = B2dPixelsToWorld(v2ScreenCentre_Pixels);
	
	{
		f32 fScreenWidthB2d = B2dPixelsToWorld(visibleSize.width);
		f32 fHalfScreenWidthB2d = (fScreenWidthB2d / 2.0f);

		f32 fScreenHeightB2d = B2dPixelsToWorld(visibleSize.height);
		f32 fHalfScreenHeightB2d = (fScreenHeightB2d / 2.0f);

		new CGCObjScreenBound(CGCObjScreenBound::EScreenBoundType::Bottom, (v2ScreenCentre_B2d + Vec2(0.0f, -fHalfScreenHeightB2d)), fScreenWidthB2d, 0.5f, 0.0f);
		new CGCObjScreenBound(CGCObjScreenBound::EScreenBoundType::Top, (v2ScreenCentre_B2d + Vec2(0.0f, fHalfScreenHeightB2d * 0.80f)), fScreenWidthB2d, 0.5f, 0.0f);
		new CGCObjScreenBound(CGCObjScreenBound::EScreenBoundType::Left, (v2ScreenCentre_B2d + Vec2(-fHalfScreenWidthB2d, 0.0f)), 0.5f, fScreenHeightB2d, 0.0f);
		new CGCObjScreenBound(CGCObjScreenBound::EScreenBoundType::Right, (v2ScreenCentre_B2d + Vec2(fHalfScreenWidthB2d, 0.0f)), 0.5f, fScreenHeightB2d, 0.0f);
	}

	// Creating Player // Old Mario player
	//Vec2 v2MarioStartPos = (v2ScreenCentre_Pixels - Vec2(0.0f, (visibleSize.height * 0.2f)));
	
	// Create new player with new sprite
	m_pcPlayer = new CPlayer();
	m_pcPlayer->SetResetPosition( cocos2d::Vec2( 150.0f, 150.0f ) );

	// Player lives --- needs refactoring, put in livesmanager class??
	m_pcaPlayerLives = new CLife[m_pcPlayer->getCurrentLives()];

	float LifeStartPosX = 1650.0f;
	float LifeStarPosY = 990.0f;
	float LifePosXIncrease = 80.0f;

	for (int i = 0; i < m_pcPlayer->getCurrentLives(); i++)
	{
		Vec2 v2LivesPos( LifeStartPosX, LifeStarPosY );
		m_pcaPlayerLives[i].SetResetPosition( v2LivesPos );
		LifeStartPosX += LifePosXIncrease;

		//m_pcPlayerLives->SetVisible( true );
	}

	// Creating Exit //
	m_pcExit = new CExit();
	m_pcExit->SetResetPosition( Vec2( 1800.0f, 120.0f ) );
	
	
	// Creating Enemy //
	m_pcEnemyGroup->SetFormationOrigin( v2ScreenCentre_Pixels + Vec2( -( visibleSize.width * 0.25f ), ( visibleSize.height * 0.25f ) ) );
	m_pcEnemyGroup->SetRowsAndColumns( 1, 1, -40.0f, 40.0f );

	// Create Platforms
	CreatePlatforms();

	// -----

	// Adding in Collision Handlers //

	// Collision for Player and Collectable
	GetCollisionManager().AddCollisionHandler
	(
		[this]
		( CPlayer& rcPlayer, CCollectable& rcCollectable, const b2Contact& rcContact ) -> void
		{
			// check if the player is not collecting anything else before collecting the item, then get the value of the collectable
			// and increase the players itemscollected
			if (m_pcPlayer->getIsCollecting() == false)
			{
				m_pcPlayer->setIsCollecting(true);
				m_pcPlayer->IncreaseItemCollected(rcCollectable.getRewardValue());
				//m_iScore += 100;
				m_iScore += rcCollectable.getPointsValue();
				m_pcSoundManager->PlaySoundEffect(ESoundList::CollectablesSFX, false);
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
			if (m_pcPlayer->getIsColliding() == false)
			{
				m_pcPlayer->setIsColliding(true);
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
			if (m_pcPlayer->getIsColliding() == false)
			{
				m_pcPlayer->setIsColliding(true);
				m_pcPlayer->DecreaseLife();

				RequestReset();

				CCLOG("Player hit Enemy!");
			}
		}
	);
	
	// Collisions for Player and Platform
	GetCollisionManager().AddCollisionHandler
	(
		[this]
	(CPlayer& rcPlayer, CPlatform& rcPlatform, const b2Contact& rcContact) -> void
		{
			// If the player collides with the platform, player IsGrounded
			if (m_pcPlayer->getbIsGrounded() == false)
			{
				m_pcPlayer->setIsGrounded(true);

				CCLOG("Player hit Ground!");
			}
		}
	);
	
	// Collisions for Player and Disappearing Platforms
	GetCollisionManager().AddCollisionHandler
	(
		[this]
	(CPlayer& rcPlayer, CDisappearPlatform& rcDisappearPlatform, const b2Contact& rcContact) -> void
		{
			if (m_pcPlayer->getbIsGrounded() == false)
			{
				// If player IsGrounded the platform disappears
				m_pcPlayer->setIsGrounded(true);
				CGCObjectManager::ObjectKill(&rcDisappearPlatform);
				CCLOG("Platform Disappears!");
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
			m_iScore = 0;
			VOnReset();
			ResetRequestWasHandled();
			m_pcTimer->ResetTimer();
			m_pcScore->ScoreReset();
		}

	switch (m_eGameState) 
	{
		case (EGameState::Running):
			// Insert Game Logic while Game is Running
			WinCondition();
			LoseCondition();

			m_pcTimer->TimerUpdate(Director::getInstance()->getFrameRate() / 60);

			if (m_pcTimer->TimerHasEnded())
			{
				m_pcPlayer->DecreaseLife();		
				RequestReset();
			}

			m_pcScore->ScoreUpdate(m_iScore);

			ManuallyHandleCollisions();

			UpdatePlayerLives();

			m_pcPlayer->setIsCollecting(false);
			m_pcPlayer->setIsColliding(false);

			COLLISIONTESTLOG("Game is Running");
			break;

		case (EGameState::Collected):
			// Insert Game Logic while all Collectables have been collected
			m_pcTimer->TimerUpdate(Director::getInstance()->getFrameRate() / 60);
			if (m_pcTimer->TimerHasEnded() || m_pcPlayer->getCurrentLives() <= 0)
			{
				m_eGameState = EGameState::Over;
			}

			m_pcExit->setIsOpen(true);

			ManuallyHandleCollisions();

			m_pcPlayer->setIsCollecting(false);
			m_pcPlayer->setIsColliding(false);

			COLLISIONTESTLOG("Game has Collected All Objects");
			break;

		case (EGameState::Won):
			// Insert Game Logic while Game is completed
			m_pcTimer->TimerUpdate(Director::getInstance()->getFrameRate() / 5);
			if (m_pcTimer->TimerHasEnded())
			{
				ReplaceScene(TransitionRotoZoom::create(1.0f, TGCGameLayerSceneCreator< CMainMenuSceneLayer >::CreateScene() ));
			}

			m_iScore += 10;
			m_pcScore->ScoreUpdate(m_iScore);
			
			COLLISIONTESTLOG("Game is Winner");
			break;

		case (EGameState::Over) :
			// Insert Game Logic while Game is Over
			ReplaceScene(TransitionRotoZoom::create(1.0f, TGCGameLayerSceneCreator< CMainMenuSceneLayer >::CreateScene() ));
			COLLISIONTESTLOG("Game is Over");
			break;

			
	}
}

void CLevel::VOnDestroy()
{
	// De-allocate memory in opposite order of creation //
	delete m_pcPlayer;
	m_pcPlayer = nullptr;

	delete[] m_pcaPlayerLives;
	m_pcaPlayerLives = nullptr;

	delete m_pcExit;
	m_pcExit = nullptr;

	//delete m_pcHazard;
	//m_pcHazard = nullptr;

	delete m_pcScore;
	m_pcScore = nullptr;

	delete m_pcTimer;
	m_pcTimer = nullptr;

	m_pcSoundManager->EndSound();
	delete m_pcSoundManager;
	m_pcSoundManager = nullptr;

	delete m_pcDefaultGCBackground;
	m_pcDefaultGCBackground = nullptr;

	delete m_pcUIBar;
	m_pcUIBar = nullptr;

	delete[] m_pcBottomPlatforms;
	m_pcBottomPlatforms = nullptr;

	delete[] m_pcFirstRowPlatforms;
	m_pcFirstRowPlatforms = nullptr;

	delete[] m_pcSecondRowPlatforms;
	m_pcSecondRowPlatforms = nullptr;

	delete[] m_pcThirdRowPlatforms;
	m_pcThirdRowPlatforms = nullptr;

	delete[] m_pcFourthRowPlatforms;
	m_pcFourthRowPlatforms = nullptr;

	delete[] m_pcFifthRowPlatforms;
	m_pcFifthRowPlatforms = nullptr;

	delete[] m_pcSixthRowPlatforms;
	m_pcSixthRowPlatforms = nullptr;

	delete[] m_pcSeventhRowPlatforms;
	m_pcSeventhRowPlatforms = nullptr;

	delete m_pcEighthRowPlatforms;
	m_pcEighthRowPlatforms = nullptr;

	delete[] m_pcNinthRowPlatforms;
	m_pcNinthRowPlatforms = nullptr;

	delete[] m_pcTenthRowPlatforms;
	m_pcTenthRowPlatforms = nullptr;

	delete[] m_pcDefaultGCBackground;
	m_pcDisappearPlatforms = nullptr;
	
	// Don't forget to Unregister Groups Manually! //
	
	CGCObjectManager::ObjectGroupUnRegister(m_pcPlatformGroup);
	delete m_pcPlatformGroup;
	m_pcPlatformGroup = nullptr;
	
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

// -----

void CLevel::CreatePlatforms()
{
	// Creating Platforms //
// Bottom Platform 	
	float PlatformPosXIncrease = 60.0f;

	m_pcBottomPlatforms = new CPlatform[32];

	float BottomPlatformStartPosX = 30.0f;
	float BottomPlatformStarPosY = 30.0f;

	for (int i = 0; i < 32; i++)
	{
		Vec2 v2BottomPlatformsPos( BottomPlatformStartPosX, BottomPlatformStarPosY );
		m_pcBottomPlatforms[i].SetResetPosition( v2BottomPlatformsPos );
		BottomPlatformStartPosX += PlatformPosXIncrease;

		//m_pcPlayerLives->SetVisible( true );
	}

	// First Row Platforms
	m_pcFirstRowPlatforms = new CPlatform[15];

	float FirstRowPlaformStartPosX = 330.0f;
	float FirstRowPlaformStarPosY = 150.0f;

	for (int i = 0; i < 15; i++)
	{
		Vec2 v2FirstRowPlatformsPos( FirstRowPlaformStartPosX, FirstRowPlaformStarPosY );
		m_pcFirstRowPlatforms[i].SetResetPosition( v2FirstRowPlatformsPos );
		FirstRowPlaformStartPosX += PlatformPosXIncrease;

		//m_pcPlayerLives->SetVisible( true );
	}

	// Second Row
	m_pcSecondRowPlatforms = new CPlatform[3];

	float SecondRowPlaformStartPosX = 1230.0f;
	float SecondRowPlaformStarPosY = 210.0f;

	for (int i = 0; i < 3; i++)
	{
		Vec2 v2SecondRowPlatformsPos( SecondRowPlaformStartPosX, SecondRowPlaformStarPosY );
		m_pcSecondRowPlatforms[i].SetResetPosition( v2SecondRowPlatformsPos );
		SecondRowPlaformStartPosX += PlatformPosXIncrease;

		//m_pcPlayerLives->SetVisible( true );
	}

	// Third Row
	m_pcThirdRowPlatforms = new CPlatform[3];

	float ThirdRowPlaformStartPosX = 1710.0f;
	float ThirdRowPlaformStarPosY = 210.0f;

	for (int i = 0; i < 3; i++)
	{
		Vec2 v2ThirdRowPlatformsPos( ThirdRowPlaformStartPosX, ThirdRowPlaformStarPosY );
		m_pcThirdRowPlatforms[i].SetResetPosition( v2ThirdRowPlatformsPos );
		ThirdRowPlaformStartPosX += PlatformPosXIncrease;

		//m_pcPlayerLives->SetVisible( true );
	}

	// Fourth
	m_pcFourthRowPlatforms = new CPlatform[2];

	float FourthRowPlaformStartPosX = 1770.0f;
	float FourthRowPlaformStarPosY = 330.0f;

	for (int i = 0; i < 2; i++)
	{
		Vec2 v2FourthRowPlatformsPos( FourthRowPlaformStartPosX, FourthRowPlaformStarPosY );
		m_pcFourthRowPlatforms[i].SetResetPosition( v2FourthRowPlatformsPos );
		FourthRowPlaformStartPosX += PlatformPosXIncrease;

		//m_pcPlayerLives->SetVisible( true );
	}

	// Fifth
	m_pcFifthRowPlatforms = new CPlatform[4];

	float FifthRowPlaformStartPosX = 90.0f;
	float FifthRowPlaformStarPosY = 390.0f;

	for (int i = 0; i < 4; i++)
	{
		Vec2 v2FifthRowPlatformsPos( FifthRowPlaformStartPosX, FifthRowPlaformStarPosY );
		m_pcFifthRowPlatforms[i].SetResetPosition( v2FifthRowPlatformsPos );
		FifthRowPlaformStartPosX += PlatformPosXIncrease;

		//m_pcPlayerLives->SetVisible( true );
	}

	// Sixth
	m_pcSixthRowPlatforms = new CPlatform[3];

	float SixthRowPlaformStartPosX = 90.0f;
	float SixthRowPlaformStarPosY = 510.0f;

	for (int i = 0; i < 3; i++)
	{
		Vec2 v2SixthRowPlatformsPos( SixthRowPlaformStartPosX, SixthRowPlaformStarPosY );
		m_pcSixthRowPlatforms[i].SetResetPosition( v2SixthRowPlatformsPos );
		SixthRowPlaformStartPosX += PlatformPosXIncrease;

		//m_pcPlayerLives->SetVisible( true );
	}

	// Seventh
	m_pcSeventhRowPlatforms = new CPlatform[13];

	float SeventhRowPlaformStartPosX = 90.0f;
	float SeventhRowPlaformStarPosY = 630.0f;

	for (int i = 0; i < 13; i++)
	{
		Vec2 v2SeventhRowPlatformsPos( SeventhRowPlaformStartPosX, SeventhRowPlaformStarPosY );
		m_pcSeventhRowPlatforms[i].SetResetPosition( v2SeventhRowPlatformsPos );
		SeventhRowPlaformStartPosX += PlatformPosXIncrease;

		//m_pcPlayerLives->SetVisible( true );
	}

	// Eigth
	m_pcEighthRowPlatforms = new CPlatform();
	m_pcEighthRowPlatforms->SetResetPosition( cocos2d::Vec2( 1110.0f, 630.0f ) );

	// Ninth
	m_pcNinthRowPlatforms = new CPlatform[8];

	float NinthRowPlaformStartPosX = 1410.0f;
	float NinthRowPlaformStarPosY = 630.0f;

	for (int i = 0; i < 8; i++)
	{
		Vec2 v2NinthRowPlatformsPos( NinthRowPlaformStartPosX, NinthRowPlaformStarPosY );
		m_pcNinthRowPlatforms[i].SetResetPosition( v2NinthRowPlatformsPos );
		NinthRowPlaformStartPosX += PlatformPosXIncrease;

		//m_pcPlayerLives->SetVisible( true );
	}

	// Tenth
	m_pcTenthRowPlatforms = new CPlatform[3];

	float TenthRowPlaformStartPosX = 1050.0f;
	float TenthRowPlaformStarPosY = 450.0f;

	for (int i = 0; i < 3; i++)
	{
		Vec2 v2TenthRowPlatformsPos( TenthRowPlaformStartPosX, TenthRowPlaformStarPosY );
		m_pcTenthRowPlatforms[i].SetResetPosition( v2TenthRowPlatformsPos );
		TenthRowPlaformStartPosX += PlatformPosXIncrease;

		//m_pcPlayerLives->SetVisible( true );
	}
	
	// Disappearing Platforms
	// Create platforms/Number of platform blocks
	m_pcDisappearPlatforms = new CDisappearPlatform[3];
	
	// Platforms position
	float DisappearPlaformStartPosX = 450.0f;
	float DisappearPlaformStarPosY = 450.0f;

	for (int i = 0; i < 3; i++)
	{
		Vec2 v2DisappearPlatformsPos(DisappearPlaformStartPosX, DisappearPlaformStarPosY);
		m_pcDisappearPlatforms[i].SetResetPosition(v2DisappearPlatformsPos);
		DisappearPlaformStartPosX += PlatformPosXIncrease;

		//m_pcPlayerLives->SetVisible( true );
	}
}

void CLevel::UpdatePlayerLives()
{
	for (int i = 2; i >= m_pcPlayer->getCurrentLives(); i--)
	{
		m_pcaPlayerLives[i].SetVisible( false );
	}
}

void CLevel::WinCondition()
{
	if (m_pcPlayer->getItemsCollected() >= m_iCollectablesNeeded)
	{
		m_eGameState = EGameState::Collected;
	}
}

void CLevel::LoseCondition()
{
	if (m_pcPlayer->getCurrentLives() <= 0)
	{
		m_eGameState = EGameState::Over;
	}
}

void CLevel::SetGameState(EGameState newGameState)
{
	m_eGameState = newGameState;
}
