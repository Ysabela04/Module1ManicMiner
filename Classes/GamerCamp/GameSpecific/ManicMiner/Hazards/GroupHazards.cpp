#include "GroupHazards.h"

// -----

CGroupHazards::CGroupHazards( cocos2d::Vec2 v2FirstHazardPos,
							  cocos2d::Vec2 v2SecondHazardPos,
							  cocos2d::Vec2 v2ThirdHazardPos,
							  cocos2d::Vec2 v2FourthHazardPos,
							  cocos2d::Vec2 v2FifthHazardPos,
							  cocos2d::Vec2 v2SixthHazardPos )
	: m_iMaxNumHazards		( 6 )
	, m_v2FirstHazardPos	( v2FirstHazardPos )
	, m_v2SecondHazardPos	( v2SecondHazardPos )
	, m_v2ThirdHazardPos	( v2ThirdHazardPos )
	, m_v2FourthHazardPos	( v2FourthHazardPos )
	, m_v2FifthHazardPos	( v2FifthHazardPos )
	, m_v2SixthHazardPos	( v2SixthHazardPos )
{

}

CGroupHazards::~CGroupHazards()
{
	//////////////////////////////////////////////////////////////////////////
	// Delete pointers and set them to nullptr.
	delete[] m_paHazards;
	m_paHazards = nullptr;
}

// -----

//////////////////////////////////////////////////////////////////////////
// Handle only - Hazards
// Virtual
//////////////////////////////////////////////////////////////////////////
bool CGroupHazards::VHandlesThisTypeId(GCTypeID idQueryType)
{
	return(GetGCTypeIDOf(CGroupHazards) == idQueryType);
}

//////////////////////////////////////////////////////////////////////////
// Must return the typeid of the CGCObjectGroup derived class
// Virtual
//////////////////////////////////////////////////////////////////////////
GCTypeID CGroupHazards::VGetTypeId(void)
{
	return GetGCTypeIDOf(CGroupHazards);
}

void CGroupHazards::VOnGroupResourceAcquire()
{
	CreateHazards();

	CGCObjectGroup::VOnGroupResourceAcquire();
}

void CGroupHazards::VOnGroupResourceRelease()
{
	CGCObjectGroup::VOnGroupResourceRelease();

	DestroyHazards();
}

void CGroupHazards::VOnGroupResourceAcquire_PostObject()
{
	CGCObjectGroup::VOnGroupResourceAcquire_PostObject();
}

// -----

void CGroupHazards::CreateHazards()
{
	m_paHazards = new CHazard[ m_iMaxNumHazards ];

	// Manually set the position of the hazards
	m_paHazards[0].SetResetPosition( m_v2FirstHazardPos );
	m_paHazards[1].SetResetPosition( m_v2SecondHazardPos );
	m_paHazards[2].SetResetPosition( m_v2ThirdHazardPos );
	m_paHazards[3].SetResetPosition( m_v2FourthHazardPos );
	m_paHazards[4].SetResetPosition( m_v2FifthHazardPos );
	m_paHazards[5].SetResetPosition( m_v2SixthHazardPos );
}

void CGroupHazards::DestroyHazards()
{

}
