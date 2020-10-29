#include "CTimer.h"

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "cocos2d/cocos/2d/CCProgressTimer.h"
#include "cocos2d/cocos/2d/CCSprite.h"

#include "AppDelegate.h"

// Creating the timer bar and setting it's type, midpoint, rate the bar changes, percentage and position.
CTimer::CTimer()
{
	m_fMaximumTime = 6480.0f;
	m_fCurrentTime = m_fMaximumTime;
	m_bHasTimerEnded = false;

	m_cTimerSpr = Sprite::create("Loose/Bar.png");

	m_cTimerBar = ProgressTimer::create(m_cTimerSpr);
	m_cTimerBar->setType(ProgressTimer::Type::BAR);
	m_cTimerBar->setMidpoint(Vec2(0.0f, 0.5f));
	m_cTimerBar->setBarChangeRate(Vec2(1.0f, 0.0f));
	m_cTimerBar->setPercentage(100.0f);
	m_cTimerBar->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2.0f, Director::getInstance()->getVisibleSize().height * 0.96f));
}

CTimer::~CTimer()
{
}

// Takes in a float parameter that decrements the time and sets how much the bar is filled
// Checks if the timer has ended. If it has, then set the bool variable to true
void CTimer::TimerUpdate(float deltaTime)
{
	m_fCurrentTime -= deltaTime;
	m_cTimerBar->setPercentage(100 * m_fCurrentTime / m_fMaximumTime);
	if (m_fCurrentTime <= 0.0f && m_bHasTimerEnded == false)
	{
		m_bHasTimerEnded = true;
	}
}

// Reset Timer when level is reset
void CTimer::ResetTimer()
{
	m_fCurrentTime = m_fMaximumTime;
	m_bHasTimerEnded = false;
}

cocos2d::ProgressTimer* CTimer::GetTimerObj()
{
	return m_cTimerBar;
}

bool CTimer::TimerHasEnded()
{
	return m_bHasTimerEnded;
}