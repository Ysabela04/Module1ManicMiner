#ifndef	_CPLATFORMGROUP_H_
#define	_CPLATFORMGROUP_H_


#ifndef BOX2D_H
#include "Box2d/Box2D.h"
#endif

#ifndef	_GCOBJECTGROUP_H_
#include "GamerCamp/GCObject/GCObjectGroup.h"
#endif

//////////////////////////////////////////////////////////////////////////
// CPlatform Group derived from GCObjectGroup ////////////////////////////
//////////////////////////////////////////////////////////////////////////

// Forward declare
class CGCObjSprite;
class CPlatform;

// CPlatformGroup
class CPlatformGroup
	: public CGCObjectGroup
{
	// Destroy managed platforms
	void DestroyPlatforms(void);

public:
	//Constructor
	// Number of platforms
	CPlatformGroup();
	
	// Virtual Destructor
	virtual ~CPlatformGroup();

	// Overrides for CGCObjectGroup public interface
	// Virtual Boolean that Handles GCObjPlatform
	virtual bool		VHandlesThisTypeId(GCTypeID idQueryType);

	// Must return the typeid of the CGCObjectGroup derived class
	virtual GCTypeID	VGetTypeId(void);
	
	// Virtual Function
	virtual void		VOnGroupResourceRelease(void);
};

#endif // _CPLATFORMGROUP_H_
