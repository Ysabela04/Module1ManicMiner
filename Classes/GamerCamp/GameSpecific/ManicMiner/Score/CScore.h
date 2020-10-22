#ifndef _SCORE_H_
#define _SCORE_H_

#include "cocos2d/cocos/2d/CCLabel.h"

class CScore
{
private:
	std::string m_scoreText;

	cocos2d::Label* m_cScoreLabel;

public:
	CScore();
	~CScore();

	void ScoreUpdate(int iScore);
	void ScoreReset();

	cocos2d::Label* GetScoreObj();

};

#endif
