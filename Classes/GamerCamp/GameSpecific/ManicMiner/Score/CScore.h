#ifndef _SCORE_H_
#define _SCORE_H_

#include "cocos2d/cocos/2d/CCLabel.h"

// Score class that creates a label object to display score. The object takes in the level score as a parameter in the funtion ScoreUpdate.
// m_scoreText is used to convert the integer score into a string and then set the string of the label to the score.
// There is also a getter to get a reference to the label object

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
