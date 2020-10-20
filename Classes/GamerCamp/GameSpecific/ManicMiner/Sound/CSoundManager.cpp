#include "CSoundManager.h"

#include "Classes/GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "SimpleAudioEngine.h"

#include "Classes/AppDelegate.h"

using namespace CocosDenshion;

CSoundManager::CSoundManager()
{
	pachSoundFiles[0] = {"Loose/BackgroundMusic.mp3"};
	m_cAudioEngine = SimpleAudioEngine::getInstance();
}

CSoundManager::~CSoundManager()
{
}

void CSoundManager::EndSound()
{
	m_cAudioEngine->end();
}

void CSoundManager::PlayBackgroundMusic()
{
	m_cAudioEngine->playEffect(pachSoundFiles[0], true);
}

void CSoundManager::PlaySoundEffect(int index)
{
	m_cAudioEngine->playEffect(pachSoundFiles[index], false);
}
