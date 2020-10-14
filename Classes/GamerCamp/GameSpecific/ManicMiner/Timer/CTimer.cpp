#include "CTimer.h"

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "cocos2d/cocos/2d/CCProgressTimer.h"
#include "cocos2d/cocos/2d/CCSprite.h"

#include "AppDelegate.h"


CTimer::CTimer()
{
	m_fMaximumTime = 600.0f;
	m_fCurrentTime = m_fMaximumTime;
	m_bHasTimerEnded = false;

	m_cTimerSpr = Sprite::create("Loose/Bar.png");

	m_cTimerBar = ProgressTimer::create(m_cTimerSpr);
	m_cTimerBar->setType(ProgressTimer::Type::BAR);
	m_cTimerBar->setMidpoint(Vec2(0.0f, 0.5f));
	m_cTimerBar->setBarChangeRate(Vec2(1.0f, 0.0f));
	m_cTimerBar->setPercentage(100.0f);
	m_cTimerBar->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
}

CTimer::~CTimer()
{
}

void CTimer::TimerUpdate(float dt)
{
	m_fCurrentTime -= dt;
	m_cTimerBar->setPercentage(100 * m_fCurrentTime / m_fMaximumTime);
	if (m_fCurrentTime <= 0 && m_bHasTimerEnded == false)
	{
		m_bHasTimerEnded = true;
	}
}

cocos2d::ProgressTimer* CTimer::GetTimerObj()
{
	return m_cTimerBar;
}

bool CTimer::TimerHasEnded()
{
	return m_bHasTimerEnded;
}