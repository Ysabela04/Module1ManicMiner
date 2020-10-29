#ifndef _CDISAPPEARPLATFORM_H_
#define _CDISAPPEARPLATFORM_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CDisappearPlatform
	: public CGCObjSpritePhysics
{
public:
	CDisappearPlatform(void)
		: CGCObjSpritePhysics(GetGCTypeIDOf(CDisappearPlatform))
	{}

	virtual void VOnResourceAcquire(void) override;
};


#endif

