////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string.h>

#include "GamerCamp/GameSpecific/Platforms/GCObjGroupPlatform.h"

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GameSpecific/Platforms/GCObjPlatform.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"


//////////////////////////////////////////////////////////////////////////
// using
using namespace cocos2d;



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
CGCObjGroupPlatform::CGCObjGroupPlatform()
{
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
// virtual
CGCObjGroupPlatform::~CGCObjGroupPlatform()
{}



//////////////////////////////////////////////////////////////////////////
// only handle platforms
//////////////////////////////////////////////////////////////////////////
//virtual 
bool CGCObjGroupPlatform::VHandlesThisTypeId( GCTypeID idQueryType )
{
	return( GetGCTypeIDOf( CGCObjPlatform ) == idQueryType );
}



//////////////////////////////////////////////////////////////////////////
// must return the typeid of the CGCObjectGroup derived class
//////////////////////////////////////////////////////////////////////////
//virtual 
GCTypeID CGCObjGroupPlatform::VGetTypeId( void )
{
	return GetGCTypeIDOf( CGCObjGroupPlatform );
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjGroupPlatform::VOnGroupResourceAcquire_PostObject( void )
{
	// parent class version
	CGCObjectGroup::VOnGroupResourceAcquire();

	// set up animations for all platforms
	const char* pszPlist_Platform		= "TexturePacker/Sprites/Platform/Platform.plist";
	const char* pszAnim_Platfrom_Rotate	= "Hover";

	// make an animation
	// N.B. pdictPList is returned autoreleased - will clean itslef at end of frame if not retained
	cocos2d::ValueMap	cSpriteInfo	= GCCocosHelpers::CreateDictionaryFromPlist( pszPlist_Platform );
	cocos2d::Animation*	pAnimation	= GCCocosHelpers::CreateAnimation( cSpriteInfo, pszAnim_Platfrom_Rotate );

	auto cMyLambda = [&] ( CGCObject* pcPlatformAsObject )
	{
		GCASSERT( GetGCTypeIDOf( CGCObjPlatform ) == pcPlatformAsObject->GetGCTypeID(), "wrong type!" );
		CGCObjSprite* pSprite = (CGCObjSprite*) pcPlatformAsObject;
		pSprite->RunAction( GCCocosHelpers::CreateAnimationActionLoop( pAnimation ) );
		return true;
	};

	ForEachObject( cMyLambda );
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjGroupPlatform::VOnGroupResourceRelease( void )
{
	// n.b. this must happen first, as will fail if objects destroyed before 
	CGCObjectGroup::VOnGroupResourceRelease(); 
}


