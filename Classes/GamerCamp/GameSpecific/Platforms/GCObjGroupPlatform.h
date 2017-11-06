////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef	_GCOBJECTGROUPPLATFORM_H_
#define	_GCOBJECTGROUPPLATFORM_H_


#ifndef BOX2D_H
	#include "Box2d/Box2D.h"
#endif

#ifndef	_GCOBJECTGROUP_H_
	#include "GamerCamp/GCObject/GCObjectGroup.h"
#endif


//////////////////////////////////////////////////////////////////////////
// forward declare
class CGCObjSprite;
class CGCObjPlatform;


//////////////////////////////////////////////////////////////////////////
// 
class CGCObjGroupPlatform
: public CGCObjectGroup
{
	// destroy managed platforms
	void DestroyPlatforms( void );

public:
	//// number of platforms
	//static const u32 k_uNumInvaders = 16;

	CGCObjGroupPlatform();		
	virtual ~CGCObjGroupPlatform();

//////////////////////////////////////////////////////////////////////////
// overrides for CGCObjectGroup public interface

	// handles GCObjPlatform
	virtual bool		VHandlesThisTypeId					( GCTypeID idQueryType );

	// must return the typeid of the CGCObjectGroup derived class
	virtual GCTypeID	VGetTypeId							( void );

	virtual void		VOnGroupResourceRelease				( void );	

// CGCObjectGroup public interface
//////////////////////////////////////////////////////////////////////////
};

#endif
