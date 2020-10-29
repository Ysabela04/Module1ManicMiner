#include <string.h>

// Include Files 
#include "GamerCamp/GameSpecific/ManicMiner/Platform/CPlatformGroup.h"
#include "GamerCamp/GameSpecific/ManicMiner/Platform/CPlatform.h"
#include "GamerCamp/GCObject/GCObjectManager.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/Core/GCTypes.h"
#include "GamerCamp/GCObject/GCObject.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

// Using Cocos2d Library
using namespace cocos2d;

// Constructor 
CPlatformGroup::CPlatformGroup()
{
}

// Virtual Destructor 
CPlatformGroup::~CPlatformGroup()
{}

// Only handle platforms
// Virtual Boolean
bool CPlatformGroup::VHandlesThisTypeId(GCTypeID idQueryType)
{
	return(GetGCTypeIDOf(CPlatform) == idQueryType);
}

// Must return the typeid of the CGCObjectGroup derived class
// Virtual TypeID
GCTypeID CPlatformGroup::VGetTypeId(void)
{
	return GetGCTypeIDOf(CPlatformGroup);
}

// Virtual Function VOnGroupResourceRelease
void CPlatformGroup::VOnGroupResourceRelease(void)
{
	// n.b. this must happen first, as will fail if objects destroyed before 
	CGCObjectGroup::VOnGroupResourceRelease();
	//DestroyPlatforms();
}

// DestroyPlatforms Function
void CPlatformGroup::DestroyPlatforms(void)
{
	// This iterates the array of registered CGCObjects 
	// Calling the supplied functor then deleting them
	DestroyObjectsReverseOrder([&](CGCObject* pObject)
		{
			// Do nothing - DestroyObjectsReverseOrder calls delete!
			GCASSERT(GetGCTypeIDOf(CPlatform) == pObject->GetGCTypeID(), "wrong type!");
		});
}
