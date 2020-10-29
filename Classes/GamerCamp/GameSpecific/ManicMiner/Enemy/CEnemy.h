#ifndef _CENEMY_H_
#define _CENEMY_H_

#ifndef _GCOBJSPRITEPHYSICS_H_
#include "../Classes/GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif


//////////////////////////////////////////////////////////////////////////
// CEnemy class derived from CGCObject ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class CEnemy
	: public CGCObjSpritePhysics
{
private:

public:
	//	Constructor
	CEnemy();

	//	Destructor
	// Need a virtual destructor since delete will be called on pointers 
	// Used to delete derived types
	
	virtual ~CEnemy()
	{}

	// Overridden virtuals from the game object interface
	// VOnResourceAcquire virtual function
	virtual void VOnResourceAcquire(void)			override;
	
	// VOnResurrected virtual function
	virtual void VOnResurrected(void)			override;
	
	// VOnUpdate virtual function
	virtual void VOnUpdate(f32 fTimestep)	override;

};
#endif // #ifndef _CENEMY_H_
