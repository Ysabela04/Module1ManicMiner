#include "Exit.h"

USING_NS_CC;

// -----

CExit::CExit()
	: CGCObjSpritePhysics( GetGCTypeIDOf( CExit ) )
	, m_bIsOpen( false )
{

}

CExit::~CExit()
{

}

// -----

//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
IN_CPP_CREATION_PARAMS_DECLARE( CExit, "TexturePacker/Sprites/Exit/Exit.plist", "exit", b2_staticBody, true );	// plist missing on clone repos on laptop 
//IN_CPP_CREATION_PARAMS_DECLARE(CExit, "TexturePacker/Sprites/Platform/Platform.plist", "platform", b2_staticBody, true);

//////////////////////////////////////////////////////////////////////////
// Virtual
void CExit::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CExit );

	CGCObjSpritePhysics::VOnResourceAcquire();
}
