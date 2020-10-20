#include "CSoundManager.h"

#include "Classes/GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "SimpleAudioEngine.h"

#include "Classes/AppDelegate.h"

using namespace CocosDenshion;

CSoundManager::CSoundManager()
{
	pachSoundFiles[0] = {"Loose/BackgroundMusic.mp3"};
	pachSoundFiles[1] = {"Loose/JumpSFX.wav"};
	pachSoundFiles[2] = { "Loose/FallingSFX.wav" };
	pachSoundFiles[3] = { "Loose/BarLoopSFX.wav" };
	pachSoundFiles[4] = { "Loose/CollectablesSFX.wav" };
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
	m_cAudioEngine->playEffect(pachSoundFiles[index]);
}
