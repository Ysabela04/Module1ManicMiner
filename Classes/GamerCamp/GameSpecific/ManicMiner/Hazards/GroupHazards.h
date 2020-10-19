#ifndef _GROUPHAZARDS_H_
#define _GROUPHAZARDS_H_

#include "GamerCamp/GameSpecific/ManicMiner/Hazards/Hazard.h"
#include "GamerCamp/GCObject/GCObjectGroup.h"


//////////////////////////////////////////////////////////////////////////
// Class: CGroupHazards
//
// This is a base class for CGroupHazards. This class handles a specific
// number of Hazards. 
//
// This class handles only 5 CHazards.
//
//////////////////////////////////////////////////////////////////////////
class CGroupHazards : public CGCObjectGroup
{
private:
	// Create the member variable that will store the CHazards
	CHazard* m_paHazards;
	
	// The maximum number if hazards that can be handles in this class
	// Set to 5 in the constructor
	int m_iMaxNumHazards;

	// The positions of the 
	cocos2d::Vec2	m_v2FirstHazardPos;
	cocos2d::Vec2	m_v2SecondHazardPos;
	cocos2d::Vec2	m_v2ThirdHazardPos;
	cocos2d::Vec2	m_v2FourthHazardPos;
	cocos2d::Vec2	m_v2FifthHazardPos;


public:
	//CGroupHazards();
	CGroupHazards( cocos2d::Vec2 v2FirstHazardPos, 
				   cocos2d::Vec2 v2SecondHazardPos, 
				   cocos2d::Vec2 v2ThirdHazardPos, 
				   cocos2d::Vec2 v2FourthHazardPos, 
				   cocos2d::Vec2 v2FifthHazardPos );
	virtual ~CGroupHazards();

	//////////////////////////////////////////////////////////////////////////
	// Functions
	//////////////////////////////////////////////////////////////////////////
	void CreateHazards();
	void DestroyHazards();

	//////////////////////////////////////////////////////////////////////////
	// Virtual
	//
	virtual bool		VHandlesThisTypeId(GCTypeID idQueryType) override;

	virtual GCTypeID	VGetTypeId(void) override;

	virtual void		VOnGroupResourceAcquire() override;

	virtual void		VOnGroupResourceAcquire_PostObject(void);

	virtual void		VOnGroupResourceRelease() override;

	//////////////////////////////////////////////////////////////////////////
	// Getters & Setters
	//
	//////////////////////////////////////////////////////////////////////////
	// Getters
	//
	//CHazard*	getpaHazards(int index)		{ return m_paHazards; }
	int			getiMaxNumHazards()			{ return m_iMaxNumHazards; }


	//////////////////////////////////////////////////////////////////////////
	// Setters
	//
	void setiMaxNumHazards( int iMaxNumHazards ) { m_iMaxNumHazards = iMaxNumHazards; }
	
};

#endif // _GROUPHAZARDS_H_
