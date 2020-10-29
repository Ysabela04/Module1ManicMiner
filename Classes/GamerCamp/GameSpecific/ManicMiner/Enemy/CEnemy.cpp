////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <memory.h>

// Include Files
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GameSpecific/Player/GCObjProjectilePlayer.h"
#include "GamerCamp/GameSpecific/Player/GCObjGroupProjectilePlayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "CEnemy.h"

USING_NS_CC;

// Constructor
// GetGCTypeIDOf uses the template in GCTypeID to generate a unique ID for 
// This type - need this to construct our base type
CEnemy::CEnemy()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CEnemy))
{
}


// CEnemy interface
// Macro
// Implement Enemy sprite
IN_CPP_CREATION_PARAMS_DECLARE(CEnemy, "TexturePacker/Sprites/Enemies/CC_Enemy_Duck/CC_Enemy_Duck.plist", "enemy", b2_dynamicBody, true);

// Virtual Functions
void CEnemy::VOnResourceAcquire(void)
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CEnemy);
	CGCObjSpritePhysics::VOnResourceAcquire();
}

void CEnemy::VOnResurrected(void)
{
	CGCObjSpritePhysics::VOnResurrected();

	GetPhysicsBody()->SetGravityScale(0.0f);
}

void CEnemy::VOnUpdate(f32 fTimestep)
{}
