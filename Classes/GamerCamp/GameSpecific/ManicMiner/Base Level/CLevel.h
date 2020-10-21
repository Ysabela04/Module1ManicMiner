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

class CLevel
	: public IGCGameLayer
	, public b2ContactListener
{
private:
	// Private Member Variables
	int								m_iCollectablesNeeded;

	// Game States
	EGameState						m_eGameState;

	// Game Objects Groups
	CPlatformGroup* 				m_pcPlatformGroup;
	CPlatform*						m_pcBottomPlatforms;

	CGroupCollectables*				m_pcGroupCollectables;

	CGCObjGroupProjectilePlayer*	m_pcGCGroupProjectilePlayer;

	// Game Objects
	CGCObjSprite*					m_pcDefaultGCBackground;
	CGCObjSprite*					m_pcUIBar;
	CPlayer*						m_pcPlayer;
	CExit*							m_pcExit;

	CGroupHazards*					m_pcGroupHazards;

	CTimer*							m_pcTimer;
	CEnemyGroup*					m_pcEnemyGroup;
	CSoundManager*					m_pcSoundManager;

	CLife*							m_pcaPlayerLives;



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

	void UpdatePlayerLives();

	void WinCondition();
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
