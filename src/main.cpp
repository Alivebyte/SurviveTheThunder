#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
//#include "Extensions/olcPGEX_Network.h"
//#include "network.h" Not using since I don't know everything about it
#include "resourcemanager.h"

enum
{
	AI_WAIT,
	AI_ATTACK
};

struct Player
{
	olc::vf2d vPos;
};

class App : public olc::PixelGameEngine
{
	olc::Sprite* m_pSprite;
public:
	App() :
		m_pSprite(nullptr)
	{
		sAppName = "TBD";
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

		m_pSprite = g_pResourceManager->LoadSprite("res/test.bmp");

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
		Clear(olc::BLACK);
		if(!bGameOver)
		{
			
			int ai_state;
			switch (ai_state)
			{
			case AI_WAIT:
				// Do waiting stuff like calculating players health and perfect... moment?


				break;
			case AI_ATTACK:
				// Attack attack, reduce the damage


				break;
			}

		}




		



		/*if (m_pSprite)
		{
			DrawSprite(olc::vi2d(0, 0), m_pSprite);
		}*/

		return true;
	}

private:
	bool bGameOver = false;

};


int main()
{
	App application;
	if (application.Construct(512, 512, 1, 1))
		application.Start();

	return 0;
}