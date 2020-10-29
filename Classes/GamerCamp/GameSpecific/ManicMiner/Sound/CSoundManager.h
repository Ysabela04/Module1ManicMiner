#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include "SimpleAudioEngine.h"
#include <map>

// Sound Manager is a class that obtains all SFX/Music and sets them in an enum called ESoundList. This enum will be used to play the sound effect when called.
// The sound manager has two functions to play audio. One is to play the BGM, the other is to play a specific SFX using the enum.
// BGM simply plays a looping track whilst SFX function needs to state if it needs to loop or not (example, SFX needs to loop while bar goes down)
// There is also a function to end all audio, usually for when the level is being destroyed

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
