#ifndef _GROUPCOLLECTABLES_H_
#define _GROUPCOLLECTABLES_H_

#include "GamerCamp/GameSpecific/ManicMiner/Collectables/Collectable.h"
#include "GamerCamp/GCObject/GCObjectGroup.h"


//////////////////////////////////////////////////////////////////////////
// Class: CGroupCollectables
//
// This is a base class for CGroupHazards. This class handles a specific
// number of Hazards. 
//
// This class handles a an m_iMaxNumCollectables number of CCollectable.
// When mades, make sure to SetResetPosition() for CCollectable.
//
//////////////////////////////////////////////////////////////////////////
class CGroupCollectables : public CGCObjectGroup
{
private:
	CCollectable* m_paCollectables;
	//CCollectable** m_paCollectables;


	//CCollectable* m_pReturnCollectables;

	int m_iNumCollectables;	

	// The positions of the 
	cocos2d::Vec2	m_v2FirstHazardPos;
	cocos2d::Vec2	m_v2SecondHazardPos;
	cocos2d::Vec2	m_v2ThirdHazardPos;
	cocos2d::Vec2	m_v2FourthHazardPos;
	cocos2d::Vec2	m_v2FifthHazardPos;
	//cocos2d::Vec2	m_v2SixthHazardPos;
	
	//CCollectable* m_paCollectables[5];



public:
	//CGroupCollectables();
	CGroupCollectables( cocos2d::Vec2 v2FirstHazardPos,
						cocos2d::Vec2 v2SecondHazardPos,
						cocos2d::Vec2 v2ThirdHazardPos,
						cocos2d::Vec2 v2FourthHazardPos,
						cocos2d::Vec2 v2FifthHazardPos );
						//cocos2d::Vec2 v2SixthHazardPos ); // int iNumCollectables );
	virtual ~CGroupCollectables();

	// -----

	//////////////////////////////////////////////////////////////////////////
	// Virtual Functions 
	//
	virtual bool		VHandlesThisTypeId( GCTypeID idQueryType ) override;

	virtual GCTypeID	VGetTypeId( void ) override;

	virtual void		VOnGroupResourceAcquire() override;

	virtual void		VOnGroupResourceAcquire_PostObject( void );

	virtual void		VOnGroupResourceRelease() override;

	// -----

    //////////////////////////////////////////////////////////////////////////
	// Functions
	//////////////////////////////////////////////////////////////////////////
	void CreateCollectables();
	void DestroyCollectables();

	//CCollectable* ReturnCollectables();

	//////////////////////////////////////////////////////////////////////////
	// Getters & Setters
	//
	//////////////////////////////////////////////////////////////////////////
	// Getters
	//
	CCollectable* getpaCollectables() { return m_paCollectables; }
	//CCollectable* getpaCollectables( int index ) { return *(m_paCollectables + index); }
	//CCollectable* getpaCollectables( int index ) { return *(&m_pReturnCollectables + index); }
	//CCollectable* getpaCollectables( int index ) const { return *(m_paCollectables + index); }
	//CCollectable* getpaCollectables( int index ) { return &m_paCollectables[index]; }

	int getiMaxNumCollectables() const { return m_iNumCollectables; }

	//////////////////////////////////////////////////////////////////////////
	// Setters
	//
	void setiMaxNumCollectables( int iNumCollectables ) { m_iNumCollectables = iNumCollectables; }

};

#endif // _GROUPCOLLECTABLES_H_
