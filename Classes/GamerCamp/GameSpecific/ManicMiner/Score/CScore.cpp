#include "CScore.h"

#include "GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "cocos2d/cocos/2d/CCLabel.h"

#include "AppDelegate.h"

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

void CScore::ScoreUpdate(int iScore)
{
	m_scoreText = std::to_string(iScore);
	m_cScoreLabel->setString(m_scoreText);
}

void CScore::ScoreReset()
{
	m_scoreText = "0";
	m_cScoreLabel->setString(m_scoreText);
}

cocos2d::Label* CScore::GetScoreObj()
{
	return m_cScoreLabel;
}
