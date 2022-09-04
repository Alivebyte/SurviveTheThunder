#include "resourcemanager.h"

#include <vector>

static std::vector<std::string> s_filePathes;

cResourceManager* g_pResourceManager = nullptr;

void cResourceManager::Init()
{
	m_pResourcePack = nullptr;

#ifdef WIN32



#endif
}

void cResourceManager::Shutdown()
{
	for (auto it : m_sprites)
	{
		if (it.second)
		{
			delete it.second;
			it.second = nullptr;
		}
	}

	m_sprites.clear();
}

olc::Sprite* cResourceManager::LoadSprite(const std::string& filename)
{
	auto spriteEntry = m_sprites.find(filename);
	if (spriteEntry == m_sprites.end())
	{
		s_filePathes.push_back(filename);

		// #TODO: load from resource pack
		olc::Sprite* pSprite = new olc::Sprite(filename);
		m_sprites.emplace(filename, pSprite);
		return pSprite;
	}

	return (*spriteEntry).second;
}

int cResourceManager::LoadSound(const std::string& filename)
{
	s_filePathes.push_back(filename);

	return olc::SOUND::LoadAudioSample(filename);
}

void cResourceManager::SaveResourcePack()
{
	olc::ResourcePack* pResourcePack = new olc::ResourcePack();

	for (auto it : s_filePathes)
		pResourcePack->AddFile(it);

	pResourcePack->SavePack("data.pack", "We start make this game too late.");

	delete pResourcePack;
}
