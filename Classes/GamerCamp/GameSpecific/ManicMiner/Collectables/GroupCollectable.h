#ifndef _GROUPCOLLECTABLE_H_
#define _GROUPCOLLECTABLE_H_

#include "GamerCamp/GCObject/GCObjectGroup.h"

class CGroupCollectable : public CGCObjectGroup
{
private:
	int m_iMaxNumCollectables;	


public:
	CGroupCollectable( int iMaxNumCollectables );
	virtual ~CGroupCollectable();

    //////////////////////////////////////////////////////////////////////////
	// Functions
	//////////////////////////////////////////////////////////////////////////

	void CreateCollectables();
	void DestroyCollectables();

	//////////////////////////////////////////////////////////////////////////
	// Virtual
	//
	virtual bool		VHandlesThisTypeId( GCTypeID idQueryType ) override;

	virtual GCTypeID	VGetTypeId( void ) override;

	virtual void		VOnGroupResourceAcquire() override;

	virtual void		VOnGroupResourceAcquire_PostObject( void );

	virtual void		VOnGroupResourceRelease() override;
};

#endif // _GROUPCOLLECTABLE_H_
