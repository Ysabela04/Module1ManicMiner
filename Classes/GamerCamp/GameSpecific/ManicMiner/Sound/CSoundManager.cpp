#include "CSoundManager.h"

#include "Classes/GamerCamp/GCCocosInterface/GCCocosHelpers.h"

#include "SimpleAudioEngine.h"

#include "Classes/AppDelegate.h"

using namespace CocosDenshion;

CSoundManager::CSoundManager()
{
	a_chSoundFiles[0] = {"Loose/BackgroundMusic.mp3"};
	audioTest = SimpleAudioEngine::getInstance();
}

CSoundManager::~CSoundManager()
{
}

void CSoundManager::PlaySoundFile()
{
	audioTest->playEffect("Loose/BackgroundMusic.mp3", true);
}

void CSoundManager::canyouseethismotherfucker()
{
	auto test = SimpleAudioEngine::getInstance();
	test->playBackgroundMusic("Loose/BackgroundMusic.mp3", true);
}
