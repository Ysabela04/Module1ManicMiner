////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCObject/GCObject.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// static initialisations


//////////////////////////////////////////////////////////////////////////
// protected constructor
CGCObject::CGCObject( GCTypeID idDerivedType )
: m_idConcreteClass	( idDerivedType )
{
	// move this!
	// add ourself to the object manager
	CGCObjectManager::ObjectRegister( this );
}


CGCObject::~CGCObject( void )
{
	CGCObjectManager::ObjectUnRegister( this );
}
