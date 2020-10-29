#ifndef _CDISAPPEARPLATFORM_H_
#define _CDISAPPEARPLATFORM_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"
///////////////////////////////////////////////////////////
// CDisappearPlatform /////////////////////////////////////
///////////////////////////////////////////////////////////
class CDisappearPlatform
	: public CGCObjSpritePhysics
{
public:
	CDisappearPlatform(void)
		: CGCObjSpritePhysics(GetGCTypeIDOf(CDisappearPlatform))
	{}
	// Virtual Function
	virtual void VOnResourceAcquire(void) override;
};


#endif // _CDISAPPEARPLATFORM_H_

