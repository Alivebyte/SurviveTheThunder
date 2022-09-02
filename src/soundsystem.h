#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include "shareddefs.h"

class cSound
{
public:
	cSound(int nSoundHandle, const std::string& filename);
	~cSound();

	void Play(bool forever = false);
	void Stop();

	bool IsPlaying();

private:
	std::string m_szFilename;
	int m_nSoundHandle;
	bool m_bIsPlaying;
};

class cSoundSystem
{
public:
	void Init();
	void Shutdown();

	cSound* CreateSound(const std::string& filename);

};

extern cSoundSystem* g_pSoundSystem;

#endif // !SOUNDSYSTEM_H
