#ifndef _CENEMY_H_
#define _CENEMY_H_

#ifndef _GCOBJSPRITEPHYSICS_H_
#include "../Classes/GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
#endif


//////////////////////////////////////////////////////////////////////////
// This is a sample class derived from CGCObject.
//////////////////////////////////////////////////////////////////////////
class CEnemy
	: public CGCObjSpritePhysics
{
private:

public:
	CEnemy();

	//////////////////////////////////////////////////////////////////////////
	// we need a virtual destructor since delete will be called on pointers of 
	// this class to delete derived types.
	virtual ~CEnemy()
	{}

	//////////////////////////////////////////////////////////////////////////
	// overridden virtuals from the game object interface
	virtual void VOnResourceAcquire(void)			override;
	virtual void VOnResurrected(void)			override;
	virtual void VOnUpdate(f32 fTimestep)	override;

};
#endif // #ifndef _CENEMY_H_
