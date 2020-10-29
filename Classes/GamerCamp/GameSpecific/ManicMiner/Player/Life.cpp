#include "Life.h"

CLife::CLife()
	: CGCObjSpritePhysics( GetGCTypeIDOf( CLife ) )
{

}

CLife::~CLife()
{

}

// -----

IN_CPP_CREATION_PARAMS_DECLARE( CLife, "TexturePacker/Sprites/PlayerLife/Heart.plist", "heart", b2_staticBody, true );
//IN_CPP_CREATION_PARAMS_DECLARE( CHazard, m_strPlistFilePath, "hazard", b2_staticBody, true );

//////////////////////////////////////////////////////////////////////////
// Virtual 
void CLife::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CLife );

	CGCObjSpritePhysics::VOnResourceAcquire();
}