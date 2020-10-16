#include "CEnemyGroup.h"
#include "CEnemy.h"
//////////////////
#include <string.h>

#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/ScreenBounds/GCObjScreenBound.h"


//////////////////////////////////////////////////////////////////////////
// using
using namespace cocos2d;



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
CEnemyGroup::CEnemyGroup(int iMaxNumEnemy)
	: m_iMaxEnemy(iMaxNumEnemy)
	, m_iNumRows(1)
	, m_iNumColumns(1)
	, m_fSpacingRow(0.0f)
	, m_fSpacingColumn(0.0f)
	, m_v2FormationOrigin(Vec2::ZERO)
	, m_eMoveDirection(EMoveDirection::Right)
	, m_bAtLeastOneEnemyTouchedTheEdgeOfTheScreenLastFrame(false)
{
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
// virtual
CEnemyGroup::~CEnemyGroup()
{}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CEnemyGroup::SetFormationOrigin(Vec2 v2FormationOrigin)
{
	m_v2FormationOrigin = v2FormationOrigin;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CEnemyGroup::SetRowsAndColumns(f32 iNumRows, int iNumColumns, f32 fPixelSpacingRow, f32 fPixelSpacingColumn)
{
	m_iNumRows = iNumRows;
	m_iNumColumns = iNumColumns;
	m_fSpacingRow = fPixelSpacingRow;
	m_fSpacingColumn = fPixelSpacingColumn;
}

//////////////////////////////////////////////////////////////////////////
// only handle invaders
//////////////////////////////////////////////////////////////////////////
//virtual 
bool CEnemyGroup::VHandlesThisTypeId(GCTypeID idQueryType)
{
	return(GetGCTypeIDOf(CEnemy) == idQueryType);
}



//////////////////////////////////////////////////////////////////////////
// must return the typeid of the CGCObjectGroup derived class
//////////////////////////////////////////////////////////////////////////
//virtual 
GCTypeID CEnemyGroup::VGetTypeId()
{
	return GetGCTypeIDOf(CEnemyGroup);
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CEnemyGroup::VOnGroupResourceAcquire()
{
	CreateEnemy();
	IGCGameLayer::ActiveInstance()->GetCollisionManager().AddCollisionHandler
	(
		[this]
	(CEnemy& rcInvader, CGCObjScreenBound& rcEdgeOfScreen, const b2Contact& rcContact) -> void
		{
			CheckForGroupWallCollisionInCurrentMoveDirection(rcEdgeOfScreen);
		}
	);

	SetResetBehaviour(CGCObjectGroup::EResetBehaviour::EResetDead);

	CGCObjectGroup::VOnGroupResourceAcquire();
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CEnemyGroup::VOnGroupResourceAcquire_PostObject()
{
	// we do this here because the alternative is to do it for each invader as they're created and it's

	// parent class version
	CGCObjectGroup::VOnGroupResourceAcquire_PostObject();

	// set up animations for all items
	const char* pszPlist = "TexturePacker/Sprites/KoopaTrooper/KoopaTrooper.plist";
	const char* pszAnim_Fly = "Fly";

	// make an animation
	ValueMap& rdictPList = GCCocosHelpers::CreateDictionaryFromPlist(pszPlist);
	Animation* pAnimation = GCCocosHelpers::CreateAnimation(rdictPList, pszAnim_Fly);

	ForEachObject([&](CGCObject* pObject) -> bool
		{
			CCAssert((GetGCTypeIDOf(CEnemy) == pObject->GetGCTypeID()),
				"CGCObject derived type mismatch!");

			CGCObjSprite* pItemSprite = (CGCObjSprite*)pObject;
			pItemSprite->RunAction(GCCocosHelpers::CreateAnimationActionLoop(pAnimation));
			return true;
		});
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual override
void CEnemyGroup::VOnGroupReset()
{
	CGCObjectGroup::VOnGroupReset();

	m_eMoveDirection = EMoveDirection::Right;
	m_bAtLeastOneEnemyTouchedTheEdgeOfTheScreenLastFrame = false;
	m_fTimeInCurrentMoveDirection = 0.0f;
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual override
void CEnemyGroup::VOnObjectReset()
{
	CGCObjectGroup::VOnObjectReset();

	int iRow = 0;
	int iColumn = 0;

	ForEachObject
	(
		[&, this]
	(CGCObject* pInvaderAsObject) -> bool
		{
			CEnemy* pEnemy = CGCObject::SafeCastToDerived< CEnemy* >(pInvaderAsObject);
			CCAssert((nullptr != pEnemy), "Aiiieeeee!! Houston we have a problem!");

			VOnObjectResurrect(pEnemy);
			pEnemy->SetResetPosition(Vec2((m_v2FormationOrigin.x + (m_fSpacingColumn * iColumn++)), (m_v2FormationOrigin.y + (m_fSpacingRow * iRow))));
			pEnemy->VOnReset();

			if (iColumn >= m_iNumColumns)
			{
				iColumn = 0;
				iRow++;
			}

			if (iRow >= m_iNumRows)
			{
				return false;
			}

			return true;
		}
	);
}


//////////////////////////////////////////////////////////////////////////
Vec2	s_EnemyGroup_v2VelocityRight = Vec2(5.0f, 0.0f);
Vec2	s_EnemyGroup_v2VelocityLeft = (-s_EnemyGroup_v2VelocityRight);

Vec2	s_EnemyGroup_v2VelocityDown = Vec2(0.0f, -6.0f);
f32		s_EnemyGroup_fMoveDownTime = 0.2f;
//////////////////////////////////////////////////////////////////////////
//virtual override
void CEnemyGroup::VOnGroupUpdate(f32 fTimeStep)
{
	CGCObjectGroup::VOnGroupUpdate(fTimeStep);

	// group movement logic

	m_fTimeInCurrentMoveDirection += fTimeStep;

	EMoveDirection eMoveDirBeforeDirectionLogic = m_eMoveDirection;

	switch (m_eMoveDirection)
	{
	case EMoveDirection::Right:
		if (m_bAtLeastOneEnemyTouchedTheEdgeOfTheScreenLastFrame)
		{
			m_eMoveDirection = EMoveDirection::DownBeforeLeft;
		}
		break;

	case EMoveDirection::DownBeforeLeft:
		if (m_fTimeInCurrentMoveDirection >= s_EnemyGroup_fMoveDownTime)
		{
			m_eMoveDirection = EMoveDirection::Left;
		}
		break;

	case EMoveDirection::Left:
		if (m_bAtLeastOneEnemyTouchedTheEdgeOfTheScreenLastFrame)
		{
			m_eMoveDirection = EMoveDirection::DownBeforeRight;
		}
		break;

	case EMoveDirection::DownBeforeRight:
		if (m_fTimeInCurrentMoveDirection >= s_EnemyGroup_fMoveDownTime)
		{
			m_eMoveDirection = EMoveDirection::Right;
		}
		break;
	}

	m_bAtLeastOneEnemyTouchedTheEdgeOfTheScreenLastFrame = false;

	if (eMoveDirBeforeDirectionLogic != m_eMoveDirection)
	{
		m_fTimeInCurrentMoveDirection = 0.0f;
	}


	// update invaders

	Vec2 v2CurrentGroupVelocity = Vec2::ZERO;

	switch (m_eMoveDirection)
	{
	case EMoveDirection::DownBeforeLeft:
	case EMoveDirection::DownBeforeRight:
		v2CurrentGroupVelocity = s_EnemyGroup_v2VelocityDown;
		break;

	case EMoveDirection::Left:
		v2CurrentGroupVelocity = s_EnemyGroup_v2VelocityLeft;
		break;

	case EMoveDirection::Right:
		v2CurrentGroupVelocity = s_EnemyGroup_v2VelocityRight;
		break;
	}

	ForEachObjectIn_LiveList
	(
		[&]										// capture locals by ref
	(CGCObject* pEnemyAsGcObj) -> bool	// return true to keep iterating
		{
			CEnemy* pEnemy = CGCObject::SafeCastToDerived< CEnemy* >(pEnemyAsGcObj);
			CCAssert((nullptr != pEnemy), "Aiiieeeee!! Houston we have a problem!");
			pEnemy->SetVelocity(v2CurrentGroupVelocity);
			return true;
		}
	);
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
//virtual 
void CEnemyGroup::VOnGroupResourceRelease()
{
	// N.B. need to do this first as it clears internal lists
	CGCObjectGroup::VOnGroupResourceRelease();
	DestroyEnemy();
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CEnemyGroup::CheckForGroupWallCollisionInCurrentMoveDirection(const CGCObjScreenBound& pScreenBound)
{
	switch (m_eMoveDirection)
	{
	case EMoveDirection::Left:
		if (pScreenBound.GetScreenBoundType() == CGCObjScreenBound::EScreenBoundType::Left)
		{
			m_bAtLeastOneEnemyTouchedTheEdgeOfTheScreenLastFrame = true;
		}
		break;

	case EMoveDirection::Right:
		if (pScreenBound.GetScreenBoundType() == CGCObjScreenBound::EScreenBoundType::Right)
		{
			m_bAtLeastOneEnemyTouchedTheEdgeOfTheScreenLastFrame = true;
		}
		break;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CEnemyGroup::CreateEnemy()
{
	for (i32 iLoop = 0; iLoop < m_iMaxEnemy; ++iLoop)
	{
		// n.b. these register themselves with this class on creation
		CEnemy* pEnemy = new CEnemy();
		pEnemy->SetName("Derek");
	}
}



//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
void CEnemyGroup::DestroyEnemy()
{
	// this iterates the array of registered CGCObjects 
	// calling the supplied functor then deleting them
	DestroyObjectsReverseOrder([&](CGCObject* pObject)
		{
			// do nothing - DestroyObjectsReverseOrder calls delete!
			GCASSERT(GetGCTypeIDOf(CEnemy) == pObject->GetGCTypeID(), "wrong type!");
		});
}


