#include "Collectable.h"

// -----

CCollectable::CCollectable()
	: CGCObjSpritePhysics	( GetGCTypeIDOf( CCollectable ) )
	, m_iRewardValue		( 1 )
	, m_iPointsValue		( 100 )
{


}

CCollectable::~CCollectable()
{

}

// -----

//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
IN_CPP_CREATION_PARAMS_DECLARE( CCollectable, "TexturePacker/Sprites/Collectables/Key/Key.plist", "key", b2_staticBody, true );	

//////////////////////////////////////////////////////////////////////////
// Virtual 
void CCollectable::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CCollectable );

	CGCObjSpritePhysics::VOnResourceAcquire();
}
