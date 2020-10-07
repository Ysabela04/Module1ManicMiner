//#include "Exit.h"

#ifndef _GCOBJPLATFORMS_H_
	#include "Exit.h"
#endif

//#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
//#include "GamerCamp/GCObject/GCObjectManager.h"
//#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
//#include "GamerCamp/GCCocosInterface/GB2ShapeCache-x.h"

USING_NS_CC;
//using namespace cocos2d;

CExit::CExit()
	: CGCObjSpritePhysics( GetGCTypeIDOf( CExit ) )
	, m_isOpen ( false ) 
{

}


CExit::~CExit()
{

}


//////////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////////
IN_CPP_CREATION_PARAMS_DECLARE( CExit, "TexturePacker/Sprites/Exit/Door.plist", "door", b2_staticBody, true );

//////////////////////////////////////////////////////////////////////////
// Virtual
void CExit::VOnResourceAcquire( void )
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE( CExit );

	CGCObjSpritePhysics::VOnResourceAcquire();
}

//void CExit::VOnResourceRelease( void )
//{
//	CGCObjSpritePhysics::VOnResourceRelease();
//}
