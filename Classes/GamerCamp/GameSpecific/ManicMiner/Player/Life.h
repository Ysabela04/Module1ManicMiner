#ifndef _Life_H_
#define _Life_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"


//////////////////////////////////////////////////////////////////////////
// Class: CLife
//
// This class handles the life of the player - for visual feedback
// in the level.
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
