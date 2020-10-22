#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include "SimpleAudioEngine.h"
#include <map>

enum class ESoundList
{
	BGM,
	JumpSFX,
	FallingSFX,
	BarLoopSFX,
	CollectablesSFX
};

class CSoundManager
{
private:
	char* pchSoundName;
	char* pchBackgroundMusic;
	std::map<ESoundList, char*> CSoundMap;
	CocosDenshion::SimpleAudioEngine* m_cAudioEngine;

public:
	CSoundManager();
	~CSoundManager();

	void EndSound();

	void PlayBackgroundMusic();
	void PlaySoundEffect(ESoundList index, bool isLooping);

};

#endif
