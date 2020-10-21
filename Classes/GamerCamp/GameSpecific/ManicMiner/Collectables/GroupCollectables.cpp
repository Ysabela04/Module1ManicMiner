#include "GroupCollectables.h"

#include "GamerCamp/GameSpecific/ManicMiner/Collectables/Collectable.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"


using namespace cocos2d;

CGroupCollectables::CGroupCollectables( cocos2d::Vec2 v2FirstCollectablePos,
										cocos2d::Vec2 v2SecondCollectablePos,
										cocos2d::Vec2 v2ThirdCollectablePos,
										cocos2d::Vec2 v2FourthCollectablePos,
										cocos2d::Vec2 v2FifthCollectablePos	)
	 // int iNumCollectables )
	: m_iNumCollectables	( 5 )
	, m_v2FirstCollectablePos	( v2FirstCollectablePos )
	, m_v2SecondCollectablePos	( v2SecondCollectablePos )
	, m_v2ThirdCollectablePos	( v2ThirdCollectablePos )
	, m_v2FourthCollectablePos	( v2FourthCollectablePos )
	, m_v2FifthCollectablePos	( v2FifthCollectablePos )
	//: m_iMaxNumCollectables( 5 )	// iMaxNumCollectables )
	// iMaxNumCollectables )
{
	//m_paCollectables = new CCollectable[m_iMaxNumCollectables];

	//m_pReturnCollectables = m_paCollectables;

	//m_pReturnCollectables = m_paCollectables;
}

CGroupCollectables::~CGroupCollectables()
{
	//for (int i = 0; i < m_iMaxNumCollectables; i++)
	//{
	//	delete m_paCollectables[i];

	//	m_paCollectables[i] = nullptr;

	//}

	delete[] m_paCollectables;
	m_paCollectables = nullptr;


}

// ---

//////////////////////////////////////////////////////////////////////////
// Handle only - Collectables
// Virtual
//////////////////////////////////////////////////////////////////////////
bool CGroupCollectables::VHandlesThisTypeId( GCTypeID idQueryType )
{
	return( GetGCTypeIDOf ( CCollectable ) == idQueryType );
}

//////////////////////////////////////////////////////////////////////////
// must return the typeid of the CGCObjectGroup derived class
// Virtual
//////////////////////////////////////////////////////////////////////////
GCTypeID CGroupCollectables::VGetTypeId( void )
{
	return GetGCTypeIDOf( CGroupCollectables );
}

void CGroupCollectables::VOnGroupResourceAcquire()
{
	CreateCollectables();

	CGCObjectGroup::VOnGroupResourceAcquire();
}

void CGroupCollectables::VOnGroupResourceRelease()
{
	CGCObjectGroup::VOnGroupResourceRelease();

	//DestroyCollectables();
}

void CGroupCollectables::VOnGroupResourceAcquire_PostObject()
{
	CGCObjectGroup::VOnGroupResourceAcquire_PostObject();

	// Animating the collectables - keys
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

void CGroupCollectables::CreateCollectables()
{	

	m_paCollectables = new CCollectable[m_iNumCollectables];

	// manually setting positions of collectables
	m_paCollectables[0].SetResetPosition( m_v2FirstCollectablePos );
	m_paCollectables[1].SetResetPosition( m_v2SecondCollectablePos );
	m_paCollectables[2].SetResetPosition( m_v2ThirdCollectablePos );
	m_paCollectables[3].SetResetPosition( m_v2FourthCollectablePos );
	m_paCollectables[4].SetResetPosition( m_v2FifthCollectablePos );


}

void CGroupCollectables::DestroyCollectables()
{
	// this iterates the array of registered CGCObjects 
	// calling the supplied functor then deleting them
	//DestroyObjectsReverseOrder( [&]( CGCObject* pObject )
	//{
	//		// do nothing - DestroyObjectsReverseOrder calls delete!
	//		GCASSERT( GetGCTypeIDOf( CCollectable ) == pObject->GetGCTypeID(), "wrong type!" );
	//});
}

//CCollectable* CGroupCollectables::ReturnCollectables()
//{
//	//for (int i = 0; i < m_iMaxNumCollectables; i++)
//	//{
//	//	return m_paCollectables;
//	//}
//
//	return m_paCollectables;
//}