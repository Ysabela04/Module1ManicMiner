#ifndef _HAZARD_H_
#define _HAZARD_H_

#include "GamerCamp/GCCocosInterface/GCObjSpritePhysics.h"

class CHazard : public CGCObjSpritePhysics
{
private:
    //std::string m_strClassName;
    //std::string m_strPlistFilePath;


public:
	CHazard();
    //CHazard(std::string strPlistFilePath);
	~CHazard();

	//////////////////////////////////////////////////////////////////////////
    // Functions
    //
    //////////////////////////////////////////////////////////////////////////
    // Virtual
    //
    virtual void VOnResourceAcquire( void ) override;

};

#endif //_HAZARD_H_
