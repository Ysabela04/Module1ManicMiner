#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include "SimpleAudioEngine.h"

class CSoundManager
{
private:
	char* pachSoundFiles[5];
	CocosDenshion::SimpleAudioEngine* m_cAudioEngine;

public:
	CSoundManager();
	~CSoundManager();

	void EndSound();

	void PlayBackgroundMusic();
	void PlaySoundEffect(int index);

};

#endif
