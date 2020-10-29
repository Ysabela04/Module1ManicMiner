#ifndef _CDISAPPEARPLATFORM_H_
#include "CDisappearPlatform.h"
#endif

// Include Files
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"

USING_NS_CC;

// Macro
// Sprite Object implementation
IN_CPP_CREATION_PARAMS_DECLARE(CDisappearPlatform, "TexturePacker/Sprites/Platforms/Blue/CC_Platform_Regular.plist", "platformblue", b2_staticBody, true);

// Virtual Function
void CDisappearPlatform::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CDisappearPlatform);
	CGCObjSpritePhysics::VOnResourceAcquire();
}
