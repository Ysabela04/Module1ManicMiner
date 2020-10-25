#ifndef _COLLECTABLE_H_
#define _COLLECTABLE_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

// -----

//////////////////////////////////////////////////////////////////////////
// Class: CCollectable
//
// This is a base class for collectables, the player will collect these 
// items to get to the next level.
//
//////////////////////////////////////////////////////////////////////////
class CCollectable : public CGCObjSpritePhysics
{
private:
    int         m_iRewardValue;    // Value of the collectable, e.g. can be 1 for every collectable that is collected
    int         m_iPointsValue;    // The number of points that is rewarded for collecting the collectable

public:
    // Constructor & Destructor
    CCollectable();
    virtual ~CCollectable();

    // -----

    //////////////////////////////////////////////////////////////////////////
    // Virtual Functions
    //
    virtual void VOnResourceAcquire( void ) override;

    //////////////////////////////////////////////////////////////////////////
    // Getters & Setters
    //
    //////////////////////////////////////////////////////////////////////////
    // Getters
    //
    int getRewardValue() const { return m_iRewardValue; }
    int getPointsValue() const { return m_iPointsValue; }

    //////////////////////////////////////////////////////////////////////////
    // Setters
    //
    void setRewardValue( int iRewardValue ) { m_iRewardValue = iRewardValue; }
    void setPointsValue( int iPointsValue ) { m_iPointsValue = iPointsValue; }

};

#endif // _COLLECTABLE_H_
