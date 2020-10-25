#ifndef _EXIT_H_
#define _EXIT_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

// -----

//////////////////////////////////////////////////////////////////////////
// Class: CExit
//
// This is a class for exits. If the player has collected enoough items
// they can use an exit to get to the next level.
//
//////////////////////////////////////////////////////////////////////////
class CExit : public CGCObjSpritePhysics
{
private:
    bool m_bIsOpen;  // check if the door is open for the player to go through


public:
    // Constructor & Deconstructor
	CExit();
	virtual ~CExit();

    // -----

    //////////////////////////////////////////////////////////////////////////
    // Virtual Functions
    //
    virtual void VOnResourceAcquire( void ) override;

    // -----

    //////////////////////////////////////////////////////////////////////////
    // Getters & Setters
    //
    //////////////////////////////////////////////////////////////////////////
    // Getters
    //
    bool getIsOpen() const { return m_bIsOpen; }

    //////////////////////////////////////////////////////////////////////////
    // Setters
    //
    void setIsOpen( bool isOpen ) { m_bIsOpen = isOpen; }
};

#endif //_EXIT_H
