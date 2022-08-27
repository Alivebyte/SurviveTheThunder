#include "resourcemanager.h"

cResourceManager* g_pResourceManager = nullptr;

void cResourceManager::Init()
{
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
		// #TODO: load from resource pack
		olc::Sprite* pSprite = new olc::Sprite(filename);
		m_sprites.emplace(filename, pSprite);
		return pSprite;
	}

	return (*spriteEntry).second;
}
