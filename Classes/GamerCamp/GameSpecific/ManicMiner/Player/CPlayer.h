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
	
	//	Virtual Destructor
	// 	Used to delete derived types
	virtual ~CPlayer();

	//	VOnResourceAcquire derived function
	// 	Call of CGCObject derived class instance
	virtual void VOnResourceAcquire() override;

	//	VOnReset derived function
	//	Called to reset CGCObject
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

	// Increase the number of m_iItemsCollected by what is passed in (int numItemCollected)
	// This is done everytime the player collides (collects) a CCollectable.
	void IncreaseItemCollected(int numItemCollected);

	// Increase the players life (m_iCurrentLives) by 1
	// This can be called everytime the player gets 10,000 points
	void IncreaseLife();

	// Decrease the players life (m_iCurrentLives) by 1
	// This can be called when the player collides with a CHazard
	void DecreaseLife();

	// ---

	//////////////////////////////////////////////////////////////////////////
	// Getters & Setters
	//
	//////////////////////////////////////////////////////////////////////////
	// Getters
	//
	int		getItemsCollected()	const { return m_iItemsCollected; }
	int		getCurrentLives()	const { return m_iCurrentLives; }
	int		getMaxLives()		const { return m_iMaxLives; }
	bool	getIsCollecting()	const { return m_bIsCollecting; }
	bool	getIsColliding()	const { return m_bIsColliding; }
	bool	getbIsGrounded() { return m_bIsGrounded; }

	//////////////////////////////////////////////////////////////////////////
	// Setters
	//
	void	setItemsCollected	( int ivalue )			{ m_iItemsCollected = ivalue; }
	void	setCurrentLives		( int iLives )			{ m_iCurrentLives = iLives; }
	void	setMaxLives			( int iMaxLives )		{ m_iMaxLives = iMaxLives; }
	void	setIsCollecting		( bool bIsCollecting )	{ m_bIsCollecting = bIsCollecting; }
	void	setIsColliding		( bool bIsColliding )	{ m_bIsColliding = bIsColliding; }
	void	setIsGrounded(bool bIsGrounded) { m_bIsGrounded = bIsGrounded; }

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

	int		m_iItemsCollected;	// the number of items the player has collected

	int		m_iCurrentLives;	// the current number of lives the player has
	int		m_iMaxLives;		// the max number of lives the player can have

	bool	m_bIsCollecting;	// if the player is currently collecting an item

	bool	m_bIsColliding;		// check to see if the player is colliding with anything
	
	bool	m_bIsGrounded;		//check to see if the player is grounded 
};

#endif
