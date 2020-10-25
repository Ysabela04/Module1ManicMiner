#ifndef _GROUPCOLLECTABLES_H_
#define _GROUPCOLLECTABLES_H_

#include "GamerCamp/GameSpecific/ManicMiner/Collectables/Collectable.h"
#include "GamerCamp/GCObject/GCObjectGroup.h"

// -----

//////////////////////////////////////////////////////////////////////////
// Class: CGroupCollectables
//
// This is a base class for CGroupHazards. This class handles a specific
// number of Hazards. 
//
// This class CURRENTLY handles only 5 CCollectable. 
//
//////////////////////////////////////////////////////////////////////////
class CGroupCollectables : public CGCObjectGroup
{
private:
	CCollectable*	m_pcaCollectables;	

	int				m_iNumCollectables;	

	// The positions of the collectables
	cocos2d::Vec2	m_v2FirstCollectablePos;
	cocos2d::Vec2	m_v2SecondCollectablePos;
	cocos2d::Vec2	m_v2ThirdCollectablePos;
	cocos2d::Vec2	m_v2FourthCollectablePos;
	cocos2d::Vec2	m_v2FifthCollectablePos;

public:
	// Constructor & Destructor
	//CGroupCollectables();

	// Set positions of 5 CCollectable when constructed
	CGroupCollectables( cocos2d::Vec2 v2FirstCollectablePos,
						cocos2d::Vec2 v2SecondCollectablePos,
						cocos2d::Vec2 v2ThirdCollectablePos,
						cocos2d::Vec2 v2FourthCollectablePos,
						cocos2d::Vec2 v2FifthCollectablePos );
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

	// -----

	//////////////////////////////////////////////////////////////////////////
	// Getters & Setters
	//
	//////////////////////////////////////////////////////////////////////////
	// Getters
	//
	CCollectable*	getCollectables()				{ return m_pcaCollectables; }
	int				getMaxNumCollectables() const	{ return m_iNumCollectables; }

	//////////////////////////////////////////////////////////////////////////
	// Setters
	//
	void setMaxNumCollectables( int iMaxNumCollectables ) { m_iNumCollectables = iMaxNumCollectables; }

};

#endif // _GROUPCOLLECTABLES_H_
