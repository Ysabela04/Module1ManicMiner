////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string.h>

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerSpaceInvaders.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

#include "GamerCamp/GameSpecific/Player/GCObjProjectilePlayer.h"
#include "GamerCamp/GameSpecific/Player/GCObjGroupProjectilePlayer.h"



//////////////////////////////////////////////////////////////////////////
// using
using namespace cocos2d;



//////////////////////////////////////////////////////////////////////////
// N.B. we want reset to put the projectiles on the dead list
//////////////////////////////////////////////////////////////////////////
CGCObjGroupProjectilePlayer::CGCObjGroupProjectilePlayer()
{
	SetResetBehaviour( CGCObjectGroup::EResetDead );
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
// virtual
CGCObjGroupProjectilePlayer::~CGCObjGroupProjectilePlayer()
{}



//////////////////////////////////////////////////////////////////////////
// only handle invaders
//////////////////////////////////////////////////////////////////////////
//virtual 
bool CGCObjGroupProjectilePlayer::VHandlesThisTypeId( GCTypeID idQueryType )
{
	return( GetGCTypeIDOf( CGCObjProjectilePlayer ) == idQueryType );
}



//////////////////////////////////////////////////////////////////////////
// must return the typeid of the CGCObjectGroup derived class
//////////////////////////////////////////////////////////////////////////
//virtual 
GCTypeID CGCObjGroupProjectilePlayer::VGetTypeId( void )
{
	return GetGCTypeIDOf( CGCObjGroupProjectilePlayer );
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjGroupProjectilePlayer::CreateProjectiles( void )
{
	const char* pszPlist_Egg = "TexturePacker/Sprites/Egg/Egg.plist";

	// create the player's b2dBody...
	b2BodyDef bodyDef;
	bodyDef.type			= b2_dynamicBody;
	bodyDef.fixedRotation	= true;
	bodyDef.gravityScale	= 0.0f;

	// get the sprite info as a dictionary so we can create loads of them with only one load of the plist
	// n.b. pdictspriteInfo is set to autorelease so we don't need to release it manually
	cocos2d::ValueMap cSpriteInfo = GCCocosHelpers::Sprite_LoadTextureAndFramesToCachesAndGetDictionary( pszPlist_Egg );

	// n.b. these register themselves with this class on creation
	for( u32 uLoop = 0; uLoop < k_uNumInvaders; ++uLoop )
	{
		CGCObjProjectilePlayer* pProjectile = new CGCObjProjectilePlayer(); 
		pProjectile->CreateSpriteFast( cSpriteInfo );
		pProjectile->SetParent( IGCGameLayer::ActiveInstance() );
		pProjectile->CGCObjSpritePhysics::InitBox2DParams( bodyDef, "egg" ); 
	}
}



//////////////////////////////////////////////////////////////////////////
//
struct SArrayOfProjectiles
{
	u32 uCount;
	CGCObjProjectilePlayer* apProjectiles[ CGCObjectGroup::EMaxGCObjects ];
};
//////////////////////////////////////////////////////////////////////////
void CGCObjGroupProjectilePlayer::DestroyProjectiles( void )
{
	// this iterates the array of registered CGCObjects 
	// calling the supplied functor then deleting them
	DestroyObjectsReverseOrder( [&]( CGCObject* pObject )
	{
		GCASSERT( GetGCTypeIDOf( CGCObjProjectilePlayer ) == pObject->GetGCTypeID(), "wrong type!" );
		CGCObjSprite* pProjectileAsSprite = static_cast< CGCObjSprite* >( pObject );
		pProjectileAsSprite->DestroySprite();
	});
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjGroupProjectilePlayer::SpawnProjectile( b2Vec2 v2Position, b2Vec2 v2Velocity, f32 fMaxLifeTime )
{
	// check we have a projectile to spawn...
	if( GetCountDead() )
	{
		// this case is safe because we know what type this group manages
		CGCObjProjectilePlayer* pProjectile = static_cast< CGCObjProjectilePlayer* >( GetDeadObject() );

		// set up the projectile
		pProjectile->SetSpritePosition( v2Position );
		pProjectile->SetVelocity( v2Velocity );
		pProjectile->SetLifeTime( fMaxLifeTime );

		// resurrect it to fire	it
		VOnObjectResurrect( pProjectile	);
	}
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
// called from CGCObjectManager::Initialise
//virtual 
void CGCObjGroupProjectilePlayer::VOnGroupResourceAcquire( void )
{
	CreateProjectiles();
	CGCObjectGroup::VOnGroupResourceAcquire();
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjGroupProjectilePlayer::VOnGroupResourceRelease( void )
{
	// need to do this first as it resets the state of internal lists
	CGCObjectGroup::VOnGroupResourceRelease();
	DestroyProjectiles();
}


