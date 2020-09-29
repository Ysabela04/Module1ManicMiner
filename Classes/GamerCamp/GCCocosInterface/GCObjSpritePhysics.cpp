////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp / Alex Darby 2018
// Distributed under the MIT license - see readme.md
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "GCObjSpritePhysics.h"

#ifndef _GCCOCOSHELPERS_H_
	#include "../GCCocosInterface/GCCocosHelpers.h"
#endif

#ifndef _IGCGAMELAYER_H_
	#include "IGCGameLayer.h"
#endif

#ifndef __COCOS2D_H__
	#include "cocos2d.h"
#endif

#include "GB2ShapeCache-x.h"



//////////////////////////////////////////////////////////////////////////
// save ourselves some typing later
using namespace cocos2d;



//////////////////////////////////////////////////////////////////////////
// protected version to pass through id to GCObject
//////////////////////////////////////////////////////////////////////////
CGCObjSpritePhysics::CGCObjSpritePhysics( GCTypeID idDerivedType )
: CGCObjSprite			( idDerivedType )
, m_psCreateParams		( nullptr )
, m_pb2Body				( nullptr )
, m_v2LastMoveVelocity	( cocos2d::Vec2::ZERO )
{
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
CGCObjSpritePhysics::CGCObjSpritePhysics()
: CGCObjSprite		( GetGCTypeIDOf( CGCObjSpritePhysics ) )
, m_psCreateParams	( nullptr )
, m_pb2Body			( nullptr )
{
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
CGCObjSpritePhysics::~CGCObjSpritePhysics()
{
	// this object is owned by the box2d world
	m_pb2Body = nullptr;
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjSpritePhysics::InitBox2DParams( const b2BodyDef& rBodyDef, const char* pszShapeName )
{
	m_b2BodyDef		= rBodyDef;
	m_strShapeName	= pszShapeName; 
}


//////////////////////////////////////////////////////////////////////////
// params are buffered and then resources acquired on VOnResourceAcquire
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjSpritePhysics::VHandleFactoryParams( const CGCFactoryCreationParams& rCreationParams, Vec2 v2InitialPosition )
{
	m_psCreateParams = &rCreationParams; 
	SetResetPosition( v2InitialPosition );
}


//////////////////////////////////////////////////////////////////////////
// called once per game frame to update sprite positions from b2d
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjSpritePhysics::VUpdateSpriteFromBody( const b2Body* pcb2Body )
{
	CCAssert( pcb2Body == m_pb2Body, "called back for a body that we did not expect to be!" );
	b2Vec2 b2v2Pos = IGCGameLayer::B2dWorldToPixels( pcb2Body->GetPosition() );
	SetSpritePosition( Vec2( b2v2Pos.x, b2v2Pos.y ) );

	cocos2d::Vec2 v2Current = GetVelocity();
	SetVelocity( v2Current - m_v2LastMoveVelocity );
	m_v2LastMoveVelocity = cocos2d::Vec2::ZERO;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CGCObjSpritePhysics::MoveToPixelPosition( const cocos2d::Vec2& rv2NewPosPixels )
{
	// convert pixel position delta into b2d world space
	cocos2d::Vec2 v2PosDeltaPixels	= ( rv2NewPosPixels - GetSpritePosition() );
	cocos2d::Vec2 v2PosDeltaB2d		= IGCGameLayer::B2dPixelsToWorld( v2PosDeltaPixels );

	// v = ( p1 - p0 ) / t
	cocos2d::Vec2 v2VelocityToMoveByDeltaInOneFrame = ( v2PosDeltaB2d / IGCGameLayer::ActiveInstance()->B2dGetTimestep() );
	SetVelocity( v2VelocityToMoveByDeltaInOneFrame );

	// n.b. need to cache this so we can remove it from the velocity after the 
	// physics simulation has stepped handily we can do this in 
	m_v2LastMoveVelocity = v2VelocityToMoveByDeltaInOneFrame;
}


//////////////////////////////////////////////////////////////////////////
// Acquires the resources needed for the obje sprite asked for in VHandleFactoryParams
// 
// N.B. default is to parent self to the layer (needed to render within cocos)
//
//////////////////////////////////////////////////////////////////////////
void CGCObjSpritePhysics::VOnResourceAcquire()
{
	// if we have set m_psCreateParams we assume we have been created by 
	// the factory and require default setup
	const CGCFactoryCreationParams* const pcCreateParams = GetFactoryCreationParams();
	if( nullptr != pcCreateParams )
	{	
		cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile( pcCreateParams->strPlistFile );
		CreateSprite( pcCreateParams->strPlistFile.c_str() );

		// N.B. default is to parent self to the layer (needed to render within cocos)
		SetParent( IGCGameLayer::ActiveInstance() );

		b2BodyDef bodyDef;
		bodyDef.type			= pcCreateParams->eB2dBody_BodyType;
		bodyDef.fixedRotation	= pcCreateParams->bB2dBody_FixedRotation;

		InitBox2DParams( bodyDef, pcCreateParams->strPhysicsShape.c_str() );
	}
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjSpritePhysics::VOnReset()
{
	CGCObjSprite::VOnReset();
	m_v2LastMoveVelocity = cocos2d::Vec2::ZERO;
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjSpritePhysics::VOnKilled()
{
	CGCObjSprite::VOnKilled();
	IGCGameLayer::ActiveInstance()->B2dGetWorld()->DestroyBody( m_pb2Body );
	m_pb2Body				= nullptr;
	m_v2LastMoveVelocity	= cocos2d::Vec2::ZERO;
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual  
void CGCObjSpritePhysics::VOnResurrected()
{
	CGCObjSprite::VOnResurrected();

	// create the physics body
	m_pb2Body = IGCGameLayer::ActiveInstance()->B2dGetWorld()->CreateBody( &m_b2BodyDef );
	cocos2d::GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody( m_pb2Body, m_strShapeName );
	m_pb2Body->SetUserData( this );

	Vec2 v2Position = GetSpritePosition();
	m_pb2Body->SetTransform( IGCGameLayer::B2dPixelsToWorld( b2Vec2( v2Position.x, v2Position.y ) ), 0.0f );

	m_v2LastMoveVelocity = cocos2d::Vec2::ZERO;
}


//////////////////////////////////////////////////////////////////////////
// ALEX: I do not like this, but this ensures that all objects created via 
// the CGCObjSpritePhysics::VHandleFactoryParams() factory interface will 
// still get cleaned up properly...
//////////////////////////////////////////////////////////////////////////
//virtual 
void CGCObjSpritePhysics::VOnResourceRelease()
{
	if( nullptr != m_pb2Body )
	{
		IGCGameLayer::ActiveInstance()->B2dGetWorld()->DestroyBody( m_pb2Body );
		m_pb2Body = nullptr;
	}
	CGCObjSprite::VOnResourceRelease();
}

