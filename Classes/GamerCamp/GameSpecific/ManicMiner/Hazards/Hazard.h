#ifndef _HAZARD_H_
#define _HAZARD_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

// -----

//////////////////////////////////////////////////////////////////////////
// Class: CHazard
//
// This is a base class for Hazards. The player should avoid these
// obstacles, otherwise they will lose a life and restart the level.
//
//////////////////////////////////////////////////////////////////////////
class CHazard : public CGCObjSpritePhysics
{
public:
    // Constructor & Deconstructor
	CHazard();
	virtual ~CHazard();
    
    // -----

    //////////////////////////////////////////////////////////////////////////
    // Virtual Functions
    //
    virtual void VOnResourceAcquire( void ) override;

};

#endif //_HAZARD_H_
