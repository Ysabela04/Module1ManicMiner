#include "GroupHazards.h"

CGroupHazards::CGroupHazards()
{

}

CGroupHazards::~CGroupHazards()
{

}

// ---

//////////////////////////////////////////////////////////////////////////
// Handle only - Hazards
// Virtual
//////////////////////////////////////////////////////////////////////////
bool CGroupHazards::VHandlesThisTypeId(GCTypeID idQueryType)
{
	return(GetGCTypeIDOf(CGroupHazards) == idQueryType);
}

//////////////////////////////////////////////////////////////////////////
// must return the typeid of the CGCObjectGroup derived class
// Virtual
//////////////////////////////////////////////////////////////////////////
GCTypeID CGroupHazards::VGetTypeId(void)
{
	return GetGCTypeIDOf(CGroupHazards);
}

void CGroupHazards::VOnGroupResourceAcquire()
{
	

	CGCObjectGroup::VOnGroupResourceAcquire();
}

void CGroupHazards::VOnGroupResourceRelease()
{
	CGCObjectGroup::VOnGroupResourceRelease();

	
}

void CGroupHazards::VOnGroupResourceAcquire_PostObject()
{
	CGCObjectGroup::VOnGroupResourceAcquire_PostObject();


}
