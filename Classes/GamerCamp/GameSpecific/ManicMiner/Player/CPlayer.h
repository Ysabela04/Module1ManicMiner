#ifndef	_CPLAYER_H_
#define	_CPLAYER_H_

//	Include GCObjSpritePhysics.h
#ifndef _GCOBJSPRITEPHYSICS_H_
#include "../Classes/GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif

//	Include EPlayerActions.h
#include "EPlayerActions.h"

//	Include GCController.h
#include "GamerCamp/GameController/GCController.h"

///////////////////////////////////////////////////
//	CPlayer class	///////////////////////////////
///////////////////////////////////////////////////

class CPlayer
	: public CGCObjSpritePhysics
{
public:

	//	CPlayer Constructor
	CPlayer();
	virtual ~CPlayer();

	//	VOnResourceAcquire derived function
	virtual void VOnResourceAcquire() override;

	//	VOnReset derived function
	virtual void VOnReset() override;

	//	VOnUpdate derived function
	virtual void VOnUpdate(f32 fTimeStep) override;

	//	VOnResourceRelease derived function
	virtual void VOnResourceRelease() override;

	//	Updates the movement of the CCSprite
	void UpdateMovement(f32 fTimeStep);

	// ---

	//////////////////////////////////////////////////////////////////////////
	// Functions
	//////////////////////////////////////////////////////////////////////////
	void IncreaseItemCollected(int numItemCollected);

	// ---

	//////////////////////////////////////////////////////////////////////////
	// Getters & Setters
	//
	//////////////////////////////////////////////////////////////////////////
	// Getters
	//
	int getiItemsCollected() { return m_iItemsCollected; }
	bool getbIsCollecting() { return m_bIsCollecting; }

	//////////////////////////////////////////////////////////////////////////
	// Setters
	//
	void setiItemsCollected(int ivalue) { m_iItemsCollected = ivalue; }
	void setbIsCollecting(bool bIsCollecting) { m_bIsCollecting = bIsCollecting; }

private:

	// member variables for 'physicsy' handling
	// N.B. uses sprite to store position and has no rotation
	f32		m_fMaximumMoveForce_Horizontal;
	f32		m_fMaximumMoveForce_Vertical;
	f32		m_fDragCoefficient_Linear;
	f32		m_fDragCoefficient_Square;
	f32		m_fNoInput_ExtraDrag_Square;
	f32		m_fNoInput_VelocityThreshold;

	// action map for controllers
	TGCActionToKeyMap< EPlayerActions >* m_pcControllerActionToKeyMap;

	int m_iItemsCollected;	// the number of items the player has collected

	bool m_bIsCollecting;	// if the player is currently collecting an item
};

#endif
