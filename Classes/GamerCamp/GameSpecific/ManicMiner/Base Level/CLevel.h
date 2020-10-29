#ifndef _GCLEVELWITHSTATES_H_
#define _GCLEVELWITHSTATES_H_

#include "Classes/GamerCamp/GCCocosInterface/IGCGameLayer.h"
//#include "GamerCamp/GameSpecific/ManicMiner/Timer/CTimer.h"
#include "EGameState.h"

// Forward Declaration
class CGCObjSprite;
class CCollectable;
class CGroupCollectables;
class CGCObjGroupProjectilePlayer;
class CPlayer;
class CExit;
class CGroupHazards;
class CTimer;
class CEnemy;
class CEnemyGroup;
class CSoundManager;
class CLife;
class CPlatform;
class CPlatformGroup;
class CDisappearPlatform;
class CScore;

class CLevel
	: public IGCGameLayer
	, public b2ContactListener
{
private:
	// Private Member Variables
	int								m_iCollectablesNeeded;
	int								m_iScore;

	// Game States
	EGameState						m_eGameState;

	// Game Objects Groups
	CPlatformGroup* 				m_pcPlatformGroup;

	// Platforms
	CPlatform*						m_pcBottomPlatforms;
	CPlatform*						m_pcFirstRowPlatforms;
	CPlatform*						m_pcSecondRowPlatforms;
	CPlatform*						m_pcThirdRowPlatforms;
	CPlatform*						m_pcFourthRowPlatforms;
	CPlatform*						m_pcFifthRowPlatforms;
	CPlatform*						m_pcSixthRowPlatforms;
	CPlatform*						m_pcSeventhRowPlatforms;
	CPlatform*						m_pcEighthRowPlatforms;
	CPlatform*						m_pcNinthRowPlatforms;
	CPlatform*						m_pcTenthRowPlatforms;
	
	//Disappearing Platform
	CDisappearPlatform*					m_pcDisappearPlatforms;

	// Group of collectables
	CGroupCollectables*				m_pcGroupCollectables;

	CGCObjGroupProjectilePlayer*	m_pcGCGroupProjectilePlayer;

	// Game Objects
	CGCObjSprite*					m_pcDefaultGCBackground;
	CGCObjSprite*					m_pcUIBar;
	
	// Player 
	CPlayer*						m_pcPlayer;
	
	// Holds the player lives
	CLife*							m_pcaPlayerLives;

	// Exit - For getting to the next level
	CExit*							m_pcExit;

	// Group of hazards
	CGroupHazards*					m_pcGroupHazards;

	CTimer*							m_pcTimer;
	
	// Group of Enemy
	CEnemyGroup*					m_pcEnemyGroup;
	CSoundManager*					m_pcSoundManager;
	CScore*							m_pcScore;


public:
	CLevel();
	~CLevel();

	enum EPlayerActions
	{
		EPA_Up = 0,
		EPA_Down,
		EPA_Left,
		EPA_Right,
		EPA_Fire
	};

	void ManuallyHandleCollisions();

	virtual void onEnter();

	virtual void VOnCreate();
	virtual void VOnUpdate(f32 fTimeStep);
	virtual void VOnDestroy();

	//////////////////////////////////////////////////////////////////////////
	// b2ContactListener interface - see b2ContactListener for details of 
	// when these get called and what they are

	virtual void BeginContact(b2Contact* pB2Contact);
	virtual void EndContact(b2Contact* pB2Contact);
	virtual void PreSolve(b2Contact* pB2Contact, const b2Manifold* pOldManifold);
	virtual void PostSolve(b2Contact* pB2Contact, const b2ContactImpulse* pImpulse);

	// Create the platforms
	// Call in VOnCreate();
	void CreatePlatforms();

	// Give visual feedback to the player, showing them how many lives they currently have
	void UpdatePlayerLives();

	// The condition needed to win the level
	// Collecting the number of CCollectables
	void WinCondition();

	// The condition to lose the level
	// Lose when the number of player lives has hit 0
	void LoseCondition();

	void SetGameState(EGameState newGameState);

private:
	bool m_bResetWasRequested;

	void RequestReset()
	{
		m_bResetWasRequested = true;
	}

	void ResetRequestWasHandled()
	{
		m_bResetWasRequested = false;
	}

	bool ResetWasRequested()
	{
		return m_bResetWasRequested;
	}
};

#endif
