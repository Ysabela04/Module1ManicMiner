#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include "SimpleAudioEngine.h"

class CSoundManager
{
private:
	char* a_chSoundFiles[1];
	CocosDenshion::SimpleAudioEngine* audioTest;

public:
	CSoundManager();
	~CSoundManager();

	void PlaySoundFile();
	void canyouseethismotherfucker();

};

#endif
