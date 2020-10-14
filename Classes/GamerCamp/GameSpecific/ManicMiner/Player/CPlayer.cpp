#include <memory.h>

//	Include Files
#include "AppDelegate.h"
#include "CPlayer.h"
#include "GamerCamp/GCCocosInterface/IGCGameLayer.h"
#include "AppDelegate.h"
#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"
#include "GamerCamp/GameSpecific/GCGameLayerPlatformer.h"
#include "GamerCamp/GameController/GCController.h"
#include "GamerCamp/GCObject/GCObjectManager.h"

USING_NS_CC;

// action/button map arrays must match in length
static EPlayerActions s_aePlayerActions[] = 
{
	EPlayerActions::MoveLeft, 
	EPlayerActions::MoveRight,  
	EPlayerActions::Jump, 
};


static cocos2d::Controller::Key s_aeKeys[] = 
{
	cocos2d::Controller::Key::BUTTON_DPAD_LEFT, 
	cocos2d::Controller::Key::BUTTON_DPAD_RIGHT,  
	cocos2d::Controller::Key::BUTTON_A, 
};



//	Constructor
CPlayer::CPlayer()
	: CGCObjSpritePhysics(GetGCTypeIDOf(CPlayer))

	, m_fMaximumMoveForce_Horizontal(20.0f)
	, m_fDragCoefficient_Linear(0.25f)
	, m_fDragCoefficient_Square(0.2f)
	, m_fNoInput_ExtraDrag_Square(0.2f)
	, m_fNoInput_VelocityThreshold(0.25f)
	, m_pcControllerActionToKeyMap(nullptr)

{
	

}

CPlayer::~CPlayer()
{

}

//	Macro
IN_CPP_CREATION_PARAMS_DECLARE(CPlayer, "TexturePacker/Sprites/Mario/mario.plist", "mario", b2_dynamicBody, true);


void CPlayer::VOnResourceAcquire()
{
	IN_CPP_CREATION_PARAMS_AT_TOP_OF_VONRESOURCEACQUIRE(CPlayer);

	CGCObjSpritePhysics::VOnResourceAcquire();

	//	Player
	const char* pszAnim_player = "Jog";
	
	//	Animate Player
	ValueMap dicPList = GCCocosHelpers::CreateDictionaryFromPlist(GetFactoryCreationParams()->strPlistFile);
	RunAction(GCCocosHelpers::CreateAnimationActionLoop(GCCocosHelpers::CreateAnimation(dicPList, pszAnim_player)));

	m_pcControllerActionToKeyMap = TCreateActionToKeyMap(s_aePlayerActions, s_aeKeys);

}



void CPlayer::VOnReset()
{
	CGCObjSpritePhysics::VOnReset();

	//	reset velocity and flip state
	SetFlippedX(false);
	SetFlippedY(false);


	//	reset
	if (GetPhysicsBody())
	{
		Vec2 v2SpritePos = GetSpritePosition();
		GetPhysicsBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		GetPhysicsBody()->SetTransform(IGCGameLayer::B2dPixelsToWorld(b2Vec2(v2SpritePos.x, v2SpritePos.y)), 0.0f);
		GetPhysicsBody()->SetFixedRotation(true);
	}
}



void CPlayer::VOnUpdate(f32 fTimeStep)
{
	// handle movement
	UpdateMovement(fTimeStep);
}

// called immediately before the managing object group releases its own assets. (Note from GCFramework)
void CPlayer::VOnResourceRelease()
{
	CGCObjSpritePhysics::VOnResourceRelease();

	delete m_pcControllerActionToKeyMap;
	m_pcControllerActionToKeyMap = nullptr;

}


// updates the movement of the CCSprite owned by this instance
	f32 	g_CPlayer_fMass 				= 1.0f;			// kg
	f32	g_CPlayer_fMaximumMoveForce_Horizontal 		= 20.0f;		// newton
	f32	g_CPlayer_fMaximumMoveForce_Vertical 		= 40.0f;		// newton
	f32	g_CPlayer_fDragCoefficient_Linear 		= 0.25f;		// unitless
	f32	g_CPlayer_fDragCoefficient_Square 		= 0.2f;			// unitless
	f32	g_CPlayer_m_fNoInput_ExtraDrag_Square 		= 0.2f;			// unitless
	f32 	g_CPlayer_fNoInput_VelocityThreshold 		= 0.25f;		// m/s
	f32 	g_CPlayer_fPixelsPerMetre 			= 20.0f;		// pixels / metre
	f32 	g_CPlayer_fDamping 				= 0.999f;		// unitless


void CPlayer::UpdateMovement(f32 fTimeStep)
{
	m_fMaximumMoveForce_Horizontal 	=		g_CPlayer_fMaximumMoveForce_Horizontal;
	m_fMaximumMoveForce_Vertical 	= 		g_CPlayer_fMaximumMoveForce_Vertical;
	m_fDragCoefficient_Linear 	= 		g_CPlayer_fDragCoefficient_Linear;
	m_fDragCoefficient_Square 	= 		g_CPlayer_fDragCoefficient_Square;
	m_fNoInput_ExtraDrag_Square 	= 		g_CPlayer_m_fNoInput_ExtraDrag_Square;
	m_fNoInput_VelocityThreshold 	= 		g_CPlayer_fNoInput_VelocityThreshold;


	// we accumulate total force over the frame and apply it at the end
	Vec2 v2TotalForce(0.0f, 0.0f);


	// * calculate the control force direction
	Vec2 v2ControlForceDirection(0.0f, 0.0f);

	// this float is used to add / remove the effect of various terms 
	// in equations based on whether input has been applied this frame
	f32 fIsInputInactive = 1.0f;

	// instantiating templates is one of the few use cases where auto is a big improvement & arguably the best thing to do
	const CGCKeyboardManager* pKeyManager = AppDelegate::GetKeyboardManager();
	TGCController< EPlayerActions > cController = TGetActionMappedController(CGCControllerManager::eControllerOne, (*m_pcControllerActionToKeyMap));

	if (cController.IsActive())
	{
		Vec2 v2LeftStickRaw = cController.GetCurrentStickValueRaw(EPlayerActions::MoveLeft, EPlayerActions::MoveRight);
		v2ControlForceDirection.x = v2LeftStickRaw.x;
		v2ControlForceDirection.y = v2LeftStickRaw.y;

		if (v2ControlForceDirection.length() > 0.0f)
		{
			fIsInputInactive = 0.0f;
		}
	}
	else
	{
		if (pKeyManager->ActionIsPressed(CGCGameLayerPlatformer::EPA_Up))
		{
			v2ControlForceDirection.y = 1.0f;
			fIsInputInactive = 0.0f;
		}
		if (pKeyManager->ActionIsPressed(CGCGameLayerPlatformer::EPA_Down))
		{
			v2ControlForceDirection.y = -1.0f;
			fIsInputInactive = 0.0f;
		}

		if (pKeyManager->ActionIsPressed(CGCGameLayerPlatformer::EPA_Left))
		{
			v2ControlForceDirection.x = -1.0f;
			fIsInputInactive = 0.0f;
		}
		if (pKeyManager->ActionIsPressed(CGCGameLayerPlatformer::EPA_Right))
		{
			v2ControlForceDirection.x = 1.0f;
			fIsInputInactive = 0.0f;
		}
	}


	// normalise the control vector and multiply by movement force
	v2ControlForceDirection.x *= m_fMaximumMoveForce_Horizontal;
	v2ControlForceDirection.y *= m_fMaximumMoveForce_Vertical;

	// accumulate the force
	v2TotalForce += v2ControlForceDirection;


	// * calculate drag force
	Vec2 v2Velocity_Unit = GetVelocity();
	f32 fVelocity = v2Velocity_Unit.normalize();

	// N.B. the last term evaluates to 0.0f if there is controller input

	f32 fDragForce = ((m_fDragCoefficient_Linear * fVelocity)
		+ (m_fDragCoefficient_Square * (fVelocity * fVelocity))
		+ (m_fNoInput_ExtraDrag_Square * (fVelocity * fVelocity) * fIsInputInactive));

	// drag is applied in the opposite direction to the current velocity of the object
	// so scale out unit version of the object's velocity by -fDragForce
	// N.B. operator* is only defined for (float, Vec2) and not for (Vec2, float) !?!
	v2TotalForce += (-fDragForce * v2Velocity_Unit);


	// physics calcs handled by box 2d based on force applied
	ApplyForceToCenter(v2TotalForce);


	// * set sprite flip based on velocity
	// N.B. the else-if looks redundant, but we want the sprite's flip 
	// state to stay the same if its velocity is set to (0.0f, 0.0f)
	if (GetVelocity().y >= 0.0f)
	{
		SetFlippedY(false);
	}
	else if (GetVelocity().y < 0.0f)
	{
		SetFlippedY(true);
	}

	if (GetVelocity().x >= 0.0f)
	{
		SetFlippedX(true);
	}
	else if (GetVelocity().x < 0.0f)
	{
		SetFlippedX(false);
	}

}

