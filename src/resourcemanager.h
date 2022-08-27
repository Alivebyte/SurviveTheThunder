#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "olcPixelGameEngine.h"
#include <unordered_map>

class cResourceManager
{
public:
	void Init();
	void Shutdown();

	olc::Sprite* LoadSprite(const std::string& filename);

private:
	std::unordered_map< std::string, olc::Sprite* > m_sprites;
};

extern cResourceManager* g_pResourceManager;

#endif // !RESOURCEMANAGER_H
