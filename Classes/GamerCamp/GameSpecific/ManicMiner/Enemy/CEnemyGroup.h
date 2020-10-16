////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef	_CENEMYGROUP_H_
#define	_CENEMYGROUP_H_

#ifndef MATH_VEC2_H
#include "cocos2d/cocos/math/Vec2.h"
#endif

#ifndef	_GCOBJECTGROUP_H_
#include "GamerCamp/GCObject/GCObjectGroup.h"
#endif


//////////////////////////////////////////////////////////////////////////
// forward declare
class CGCObjSprite;
class CEnemy;
class CGCObjScreenBound;

//////////////////////////////////////////////////////////////////////////
// responsible for newing, managing, & deleting the invaders
//
// This shows how an object group can be used as an allocation pool.
//
//////////////////////////////////////////////////////////////////////////
class CEnemyGroup
	: public CGCObjectGroup
{
private:
	enum EMoveDirection
	{
		Left,
		Right,
		DownBeforeLeft,
		DownBeforeRight,
	};

	int				m_iMaxEnemy;
	int				m_iNumRows;
	int				m_iNumColumns;
	f32				m_fSpacingRow;
	f32				m_fSpacingColumn;

	cocos2d::Vec2	m_v2FormationOrigin; // origin of the formation
	EMoveDirection	m_eMoveDirection;
	float			m_fTimeInCurrentMoveDirection;
	bool			m_bAtLeastOneEnemyTouchedTheEdgeOfTheScreenLastFrame;

	void	CreateEnemy();
	void	DestroyEnemy();

	void	CheckForGroupWallCollisionInCurrentMoveDirection(const CGCObjScreenBound& pScreenBound);

public:
	CEnemyGroup(int iMaxNumEnemy);
	virtual ~CEnemyGroup() override;

	void SetFormationOrigin(cocos2d::Vec2 m_v2FormationOrigin);

	void SetRowsAndColumns(f32 iNumRows, int iNumColumns, f32 fPixelSpacingRow, f32 fPixelSpacingColumn);

	//////////////////////////////////////////////////////////////////////////
	// overrides for CGCObjectGroup public interface

		// handles CEnemy
	virtual bool		VHandlesThisTypeId(GCTypeID idQueryType) override;

	// must return the typeid of the CGCObjectGroup derived class
	virtual GCTypeID	VGetTypeId() override;

	virtual void		VOnGroupResourceAcquire() override;
	virtual void		VOnGroupResourceAcquire_PostObject() override;
	virtual void		VOnGroupReset() override;
	virtual void		VOnObjectReset() override;
	virtual void		VOnGroupUpdate(f32 fTimeStep) override;
	virtual void		VOnGroupResourceRelease() override;
	// CGCObjectGroup public interface
//////////////////////////////////////////////////////////////////////////
};

#endif // _CENEMYGROUP_H_

