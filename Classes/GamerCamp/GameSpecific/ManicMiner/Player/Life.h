#ifndef _Life_H_
#define _Life_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"


//////////////////////////////////////////////////////////////////////////
// Class: CHazard
//
// This is a base class for Hazards. The player should avoid these
// obstacles, otherwise they will lose a life and restart the level.
//
//////////////////////////////////////////////////////////////////////////
class CLife : public CGCObjSpritePhysics
{
private:
    //std::string m_strClassName;
    //std::string m_strPlistFilePath;


public:
    CLife();
    //CHazard(std::string strPlistFilePath);
    virtual ~CLife();

    //////////////////////////////////////////////////////////////////////////
    // Functions
    //
    //////////////////////////////////////////////////////////////////////////
    // Virtual
    //
    virtual void VOnResourceAcquire( void ) override;

};

#endif //_HAZARD_H_
