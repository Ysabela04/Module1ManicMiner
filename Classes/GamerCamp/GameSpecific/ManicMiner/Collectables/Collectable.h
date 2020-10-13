#ifndef _CCOLLECTABLE_H_
#define _CCOLLECTABLE_H_

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
    i32         m_iValue;    // Value of the collectable, e.g. can be 1 for every collectable that is collected

    //std::string m_strClassName;
    //std::string m_strPlistFilePath;

    //std::string m_sPhysicsNameShape;
    //bool m_bBodyIsFixedRotation;

public:
    //CCollectable();
    CCollectable(); // (std::string strClassName)  //, std::string strPlistFilePath);
    virtual ~CCollectable();

    //////////////////////////////////////////////////////////////////////////
    // Functions
    //
    //////////////////////////////////////////////////////////////////////////
    // Virtual
    //
    virtual void VOnResourceAcquire( void ) override;


    //////////////////////////////////////////////////////////////////////////
    // Getters & Setters
    //
    //////////////////////////////////////////////////////////////////////////
    // Getters
    //
    i32 getiValue() { return m_iValue; }

    //////////////////////////////////////////////////////////////////////////
    // Setters
    //
    void setiValue( i32 ivalue ) { m_iValue = ivalue; }

    // set rewardvalue
};

#endif // _CCOLLECTABLE_H_
