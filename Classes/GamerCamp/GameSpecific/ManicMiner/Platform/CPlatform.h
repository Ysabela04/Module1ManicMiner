#ifndef _CPLATFORM_H_
#define _CPLATFROM_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CPlatform
	: public CGCObjSpritePhysics
{
public:
	CPlatform(void)
		: CGCObjSpritePhysics(GetGCTypeIDOf(CPlatform))
	{}

	virtual void VOnResourceAcquire(void) override;
};


#endif

