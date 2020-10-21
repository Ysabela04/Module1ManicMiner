#ifndef _CPLATFORM_H_
#include "CPlatform.h"
#endif

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"

USING_NS_CC;

//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
IN_CPP_CREATION_PARAMS_DECLARE(CPlatform, "TexturePacker/Sprites/Platform/Platform.plist", "platform", b2_staticBody, true);
//virtual 
void CPlatform::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CPlatform);
	CGCObjSpritePhysics::VOnResourceAcquire();
}
