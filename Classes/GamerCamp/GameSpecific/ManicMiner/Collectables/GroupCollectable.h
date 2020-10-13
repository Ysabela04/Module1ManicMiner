#ifndef _GROUPCOLLECTABLE_H_
#define _GROUPCOLLECTABLE_H_

#include "GamerCamp/GameSpecific/ManicMiner/Collectables/Collectable.h"
#include "GamerCamp/GCObject/GCObjectGroup.h"

class CGroupCollectable : public CGCObjectGroup
{
private:
	int m_iMaxNumCollectables;	

	//CCollectable* m_paCollectables;

	CCollectable* m_paCollectables[5];



public:
	CGroupCollectable(); // int iMaxNumCollectables );
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

	//////////////////////////////////////////////////////////////////////////
	// Getters & Setters
	//
	//////////////////////////////////////////////////////////////////////////
	// Getters
	//
	int getiMaxNumCollectables() { return m_iMaxNumCollectables; }

	//////////////////////////////////////////////////////////////////////////
	// Setters
	//
	void setiMaxNumCollectables( int iMaxNumCollectables ) { m_iMaxNumCollectables = iMaxNumCollectables; }

};

#endif // _GROUPCOLLECTABLE_H_
