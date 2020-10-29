#ifndef _CPLATFORM_H_
#define _CPLATFROM_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

///////////////////////////////////////////////////////////
// CPlatform class ////////////////////////////////////////
///////////////////////////////////////////////////////////
class CPlatform
	: public CGCObjSpritePhysics
{
public:
	CPlatform(void)
		: CGCObjSpritePhysics(GetGCTypeIDOf(CPlatform))
	{}
	// Virtual Function
	virtual void VOnResourceAcquire(void) override;
};


#endif // _CPLATFROM_H_

