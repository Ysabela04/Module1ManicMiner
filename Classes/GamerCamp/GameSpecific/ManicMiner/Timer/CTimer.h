#ifndef _TIMER_H_
#define _TIMER_H_

#include "cocos2d/cocos/2d/CCProgressTimer.h"
#include "cocos2d/cocos/2d/CCSprite.h"
#include "GamerCamp/GameSpecific/ManicMiner/Base Level/CLevel.h"

// Timer Class that creates a new timer object. The timer is a bar timer that decrements as the time passes.
// The percentage is set using two floats, m_fMaximumTime and m_fCurrentTime. m_bHasTimerEnded is used to check if the timer has ended and is used
// as a getter.
// There is another getter that is used to get this timer's reference and a Reset function to reset the timer.

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
	void ResetTimer();

	cocos2d::ProgressTimer* GetTimerObj();
	bool TimerHasEnded();

};


#endif

