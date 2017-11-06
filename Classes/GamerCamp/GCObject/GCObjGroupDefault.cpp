////////////////////////////////////////////////////////////////////////////////////////////////////////////
// (C) Gamer Camp 2012 
// This document should not be distributed or reproduced in part or in whole without obtaining written 
// permission from the copyright holders.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "GamerCamp/GCObject/GCObjGroupDefault.h"

#include "GamerCamp/GCObject/GCObjectManager.h"


//////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////
CGCObjGroupDefault::CGCObjGroupDefault()
{
}



//////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////
// virtual
CGCObjGroupDefault::~CGCObjGroupDefault()
{}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
bool CGCObjGroupDefault::VHandlesThisTypeId( GCTypeID idQueryType )
{
	return true;
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
GCTypeID CGCObjGroupDefault::VGetTypeId( void )
{
	return GetGCTypeIDOf( CGCObjGroupDefault );
}
