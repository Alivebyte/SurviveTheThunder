#include "soundsystem.h"

#define OLC_PGEX_SOUND
#include "Extensions/olcPGEX_Sound.h"

#include "resourcemanager.h"

cSoundSystem* g_pSoundSystem = nullptr;

void cSoundSystem::Init()
{
	olc::SOUND::InitialiseAudio(44100, 1, 8, 512);
}

void cSoundSystem::Shutdown()
{
	olc::SOUND::DestroyAudio();
}

cSound* cSoundSystem::CreateSound(const std::string& filename)
{
	int nSoundHandle = g_pResourceManager->LoadSound(filename);
	return new cSound(nSoundHandle, filename);
}

//////////////////////// SOUND IMPLEMENTATION ////////////////////////
cSound::cSound(int nSoundHandle, const std::string& filename) :
	m_szFilename(filename),
	m_nSoundHandle(nSoundHandle),
	m_bIsPlaying(false)
{
}

cSound::~cSound()
{
	m_nSoundHandle = -1;
}

void cSound::Play(bool forever)
{
	olc::SOUND::PlaySample(m_nSoundHandle, forever);
	m_bIsPlaying = true;
}

void cSound::Stop()
{
	m_bIsPlaying = false;
	olc::SOUND::StopSample(m_nSoundHandle);
}

bool cSound::IsPlaying()
{
	return m_bIsPlaying;
}
