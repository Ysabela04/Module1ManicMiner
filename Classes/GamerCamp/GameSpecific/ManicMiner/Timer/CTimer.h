#ifndef _TIMER_H_
#define _TIMER_H_

#include "cocos2d/cocos/2d/CCProgressTimer.h"
#include "cocos2d/cocos/2d/CCSprite.h"
#include "GamerCamp/GameSpecific/ManicMiner/Base Level/CLevel.h"

class CTimer
{
private:
	float m_fMaximumTime;
	float m_fCurrentTime;

	bool m_bHasTimerEnded;

	cocos2d::Sprite* m_cTimerSpr;
	cocos2d::ProgressTimer* m_cTimerBar;

public:
	CTimer();
	~CTimer();

	void TimerUpdate(float deltaTime);

	cocos2d::ProgressTimer* GetTimerObj();
	bool TimerHasEnded();
};


#endif

