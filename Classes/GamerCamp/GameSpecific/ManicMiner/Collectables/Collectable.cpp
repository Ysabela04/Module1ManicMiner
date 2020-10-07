#include "Collectable.h"

CCollectable::CCollectable()
	: CGCObjSpritePhysics ( GetGCTypeIDOf( CCollectable ) )
	, m_iValue( 1 )
{


}

CCollectable::~CCollectable()
{

}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
//IN_CPP_CREATION_PARAMS_DECLARE( CCollectable, "TexturePacker/Sprites/Coin/Coin.plist", "coin", b2_staticBody, true );	// b2_dynamicBody
IN_CPP_CREATION_PARAMS_DECLARE( CCollectable, "TexturePacker/Sprites/Collectables/Key/Key.plist", "key", b2_staticBody, true );	// b2_dynamicBody // how to change name to key?


//////////////////////////////////////////////////////////////////////////
// Virtual 
void CCollectable::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CCollectable );

	CGCObjSpritePhysics::VOnResourceAcquire();
}