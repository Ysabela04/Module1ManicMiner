#include "GroupCollectable.h"

#include "GamerCamp/GameSpecific/ManicMiner/Collectables/Collectable.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"


using namespace cocos2d;

CGroupCollectable::CGroupCollectable( int iMaxNumCollectables )
	: m_iMaxNumCollectables( iMaxNumCollectables )
{

}

CGroupCollectable::~CGroupCollectable()
{

}

// ---

//////////////////////////////////////////////////////////////////////////
// Handle only - Collectables
// Virtual
//////////////////////////////////////////////////////////////////////////
bool CGroupCollectable::VHandlesThisTypeId( GCTypeID idQueryType )
{
	return( GetGCTypeIDOf ( CCollectable ) == idQueryType );
}

//////////////////////////////////////////////////////////////////////////
// must return the typeid of the CGCObjectGroup derived class
// Virtual
//////////////////////////////////////////////////////////////////////////
GCTypeID CGroupCollectable::VGetTypeId( void )
{
	return GetGCTypeIDOf( CGroupCollectable );
}

void CGroupCollectable::VOnGroupResourceAcquire()
{
	CreateCollectables();

	CGCObjectGroup::VOnGroupResourceAcquire();
}

void CGroupCollectable::VOnGroupResourceRelease()
{
	CGCObjectGroup::VOnGroupResourceRelease();

	DestroyCollectables();
}

void CGroupCollectable::VOnGroupResourceAcquire_PostObject()
{
	CGCObjectGroup::VOnGroupResourceAcquire_PostObject();

	const char* pszPlist_Key = "TexturePacker/Sprites/Collectables/Key/Key.plist";
	const char* pszAnim_Key_Rotate = "Rotate";

	// make an animation
	// N.B. pdictPList is returned autoreleased - will clean itself at end of frame if not retained
	ValueMap& rdicPList = GCCocosHelpers::CreateDictionaryFromPlist( pszPlist_Key );
	Animation* pAnimation = GCCocosHelpers::CreateAnimation( rdicPList, pszAnim_Key_Rotate );

	ForEachObject( [&]( CGCObject* pcItemAsObject ) -> bool
		{
			// this check is essentially redundant, but they say assumption is the mother of all something or others...
			CCAssert( (GetGCTypeIDOf( CCollectable ) == pcItemAsObject->GetGCTypeID()),
				"CGCObject derived type mismatch!" );

			CGCObjSprite* pItemSprite = (CGCObjSprite*)pcItemAsObject;
			pItemSprite->RunAction( GCCocosHelpers::CreateAnimationActionLoop( pAnimation ) );
			return true;
		} 
	);
}


// ---

void CGroupCollectable::CreateCollectables()
{
	
	float f_x = 200.0f;
	float f_y = 100.0f;

	for (int i = 0; i < m_iMaxNumCollectables; i++)
	{
		cocos2d::Vec2 v2CollectablePos( f_x, f_y );

		CCollectable* pCollectable = new CCollectable;

		pCollectable->SetResetPosition( v2CollectablePos );

		f_x += 120.0f;
	}
}

void CGroupCollectable::DestroyCollectables()
{
	// this iterates the array of registered CGCObjects 
	// calling the supplied functor then deleting them
	DestroyObjectsReverseOrder( [&]( CGCObject* pObject )
		{
			// do nothing - DestroyObjectsReverseOrder calls delete!
			GCASSERT( GetGCTypeIDOf( CCollectable ) == pObject->GetGCTypeID(), "wrong type!" );
		} );
}
