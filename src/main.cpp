#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Extensions/olcPGEX_Network.h"

#include "resourcemanager.h"

class Example : public olc::PixelGameEngine
{
	olc::Sprite* m_pSprite;
public:
	Example() :
		m_pSprite(nullptr)
	{
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override
	{
		// Resource manager init
		g_pResourceManager = new cResourceManager();
		g_pResourceManager->Init();

		/*olc::ResourcePack* pResourcePack = new olc::ResourcePack();
		pResourcePack->AddFile("res/test.bmp");

		pResourcePack->SavePack("datapc_main.respack", "easy peasy lemon squeezy");*/

		m_pSprite = g_pResourceManager->LoadSprite("res/mm_background.png");

		return true;
	}

	bool OnUserDestroy() override
	{
		g_pResourceManager->Shutdown();
		delete g_pResourceManager;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (m_pSprite)
		{
			DrawSprite(olc::vi2d(0, 0), m_pSprite);
		}

		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(512, 512, 1, 1))
		demo.Start();

	return 0;
}