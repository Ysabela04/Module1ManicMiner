#ifndef _COLLECTABLE_H_
#define _COLLECTABLE_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

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

    //std::string m_strClassName;
    //std::string m_strPlistFilePath;

    //std::string m_sPhysicsNameShape;
    //bool m_bBodyIsFixedRotation;

public:
    //CCollectable();
    CCollectable(); // (std::string strClassName)  //, std::string strPlistFilePath);
    virtual ~CCollectable();

    // -----

    //////////////////////////////////////////////////////////////////////////
    // Virtual
    //
    virtual void VOnResourceAcquire( void ) override;

    //////////////////////////////////////////////////////////////////////////
    // Functions
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    // Getters & Setters
    //
    //////////////////////////////////////////////////////////////////////////
    // Getters
    //
    int getiRewardValue() const { return m_iRewardValue; }
    int getiPointsValue() const { return m_iPointsValue; }

    //////////////////////////////////////////////////////////////////////////
    // Setters
    //
    void setiRewardValue( int iRewardValue ) { m_iRewardValue = iRewardValue; }
    void setiPointsValue( int iPointsValue ) { m_iPointsValue = iPointsValue; }

};

#endif // _COLLECTABLE_H_
