#include "Collectable.h"

CCollectable::CCollectable(std::string strClassName, std::string strPlistFilePath)
	: CGCObjSpritePhysics ( GetGCTypeIDOf( CCollectable ) )
	, m_iValue( 1 )
	, m_strClassName( strClassName )
	, m_strPlistFilePath( strPlistFilePath )
	, m_strFilePath ( strPlistFilePath )
{


}

CCollectable::~CCollectable()
{

}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
// So that when a collectable is made the right texture and phyiscs is used
//IN_CPP_CREATION_PARAMS_DECLARE( CCollectable, "TexturePacker/Sprites/Coin/Coin.plist", "coin", b2_staticBody, true );	// b2_dynamicBody
//IN_CPP_CREATION_PARAMS_DECLARE( CCollectable, "TexturePacker/Sprites/Collectables/Key/Key.plist", "key", b2_staticBody, true );	// b2_dynamicBody // how to change name to key?
IN_CPP_CREATION_PARAMS_DECLARE( m_strClassName, "TexturePacker/Sprites/Collectables/Key/Key.plist", "key", b2_staticBody, true );	// b2_dynamicBody // how to change name to key?



//////////////////////////////////////////////////////////////////////////
// Virtual 
void CCollectable::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( m_strClassName );

	CGCObjSpritePhysics::VOnResourceAcquire();
}