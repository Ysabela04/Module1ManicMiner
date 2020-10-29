#include "CSoundManager.h"

#include "Classes/GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "SimpleAudioEngine.h"

#include "Classes/AppDelegate.h"

using namespace CocosDenshion;

// Creating an enum and setting them to char's using std::Map
// pchSoundName and pchBackgroundMusic are member varibles that are used to play a specific audio by being set what file to play using the enum
// Creating an instance of coco2d's audio engine
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

// This stops all audio being played. Used when level is being destroyed
void CSoundManager::EndSound()
{
	m_cAudioEngine->end();
}

// Function that simply just plays the audio file in the enum "BGM" and loops it
void CSoundManager::PlayBackgroundMusic()
{
	pchBackgroundMusic = CSoundMap[ESoundList::BGM];
	m_cAudioEngine->playEffect(pchBackgroundMusic, true);
}

// Function that takes in two arguments and pass them in. The Enum sets what audio to play and the bool checks whether or not to loop
void CSoundManager::PlaySoundEffect(ESoundList index, bool isLooping)
{
	pchSoundName = CSoundMap[index];
	m_cAudioEngine->playEffect(pchSoundName, isLooping);
}
