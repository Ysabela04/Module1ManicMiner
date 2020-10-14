#ifndef _GCLEVELWITHSTATES_H_
#define _GCLEVELWITHSTATES_H_

#include "Classes/GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/ManicMiner/Timer/CTimer.h"
#include "EGameState.h"

class CGCObjSprite;
class CGCObjPlatform;
class CGCObjGroupPlatform;
class CTimer;

class CLevel
	: public IGCGameLayer
	, public b2ContactListener
{
private:
	// Private Member Variables

	// Game States
	EGameState m_eGameState;

	// Game Objects Groups
	CGCObjGroupPlatform* m_pcDefaultGCGroupPlatform;

	// Game Objects
	CGCObjSprite* m_pcDefaultGCBackground;
	CTimer* m_pcTimer;

public:
	CLevel();
	~CLevel();

	virtual void VOnEnter();

	virtual void VOnCreate();
	virtual void VOnUpdate(f32 fTimeStep);
	virtual void VOnDestroy();

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
