#include "Hazard.h"

CHazard::CHazard()	
	: CGCObjSpritePhysics( GetGCTypeIDOf( CHazard ) )
{

}

CHazard::~CHazard()
{

}

// -----

//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
IN_CPP_CREATION_PARAMS_DECLARE( CHazard, "TexturePacker/Sprites/Hazards/Hazard.plist", "hazard", b2_staticBody, true );

//////////////////////////////////////////////////////////////////////////
// Virtual 
void CHazard::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CHazard );

	CGCObjSpritePhysics::VOnResourceAcquire();
}
