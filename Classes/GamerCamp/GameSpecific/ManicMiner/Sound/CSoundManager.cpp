#include "CSoundManager.h"

#include "Classes/GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "SimpleAudioEngine.h"

#include "Classes/AppDelegate.h"

using namespace CocosDenshion;

CSoundManager::CSoundManager()
{
	CSoundMap[ESoundList::BGM] = "Loose/BackgroundMusic.mp3";
	CSoundMap[ESoundList::JumpSFX] = "Loose/JumpSFX.wav";
	CSoundMap[ESoundList::FallingSFX] = "Loose/FallingSFX.wav";
	CSoundMap[ESoundList::BarLoopSFX] = "Loose/BarLoopSFX.wav";
	CSoundMap[ESoundList::CollectablesSFX] = "Loose/CollectableSFX.wav";

	pchSoundName = "";
	pchBackgroundMusic = "";
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
	pchBackgroundMusic = CSoundMap[ESoundList::BGM];
	m_cAudioEngine->playEffect(pchBackgroundMusic, true);
}

void CSoundManager::PlaySoundEffect(ESoundList index, bool isLooping)
{
	pchSoundName = CSoundMap[index];
	m_cAudioEngine->playEffect(pchSoundName, isLooping);
}
