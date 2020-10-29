#include "CScore.h"

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "cocos2d/cocos/2d/CCLabel.h"

#include "AppDelegate.h"

// Creating and initialising the score text to be "0" and creating the label, setting its colour and position
CScore::CScore()
{
	m_scoreText = "0";

	m_cScoreLabel = Label::createWithTTF(m_scoreText, "fonts/arial.ttf", 32);
	m_cScoreLabel->setTextColor(Color4B::RED);
	m_cScoreLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2.0f, Director::getInstance()->getVisibleSize().height * 0.90f));
}

CScore::~CScore()
{
}

// ScoreUpdate takes in the score from the level as an integer argument and converts it to a string. The string is then set for the label's string
void CScore::ScoreUpdate(int iScore)
{
	m_scoreText = std::to_string(iScore);
	m_cScoreLabel->setString(m_scoreText);
}

// ScoreReset simply resets the text back as "0"
void CScore::ScoreReset()
{
	m_scoreText = "0";
	m_cScoreLabel->setString(m_scoreText);
}

// Getter to return a reference to the label object
cocos2d::Label* CScore::GetScoreObj()
{
	return m_cScoreLabel;
}
