#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "olcPixelGameEngine.h"
#include "Extensions/olcPGEX_Sound.h"
#include <unordered_map>

class cResourceManager
{
public:
	void Init();
	void Shutdown();

	olc::Sprite* LoadSprite(const std::string& filename);
	int LoadSound(const std::string& filename);

	void SaveResourcePack();

private:
	std::unordered_map< std::string, olc::Sprite* > m_sprites;
	olc::ResourcePack* m_pResourcePack;
};

extern cResourceManager* g_pResourceManager;

#endif // !RESOURCEMANAGER_H
