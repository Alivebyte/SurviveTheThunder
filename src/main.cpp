#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
//#include "Extensions/olcPGEX_Network.h"
//#include "network.h" Not using since I don't know everything about it
#include "resourcemanager.h"


struct Player
{
	olc::vf2d vPos;
};

class App : public olc::PixelGameEngine
{
	olc::Sprite* m_pSprite;
public:

	enum AI_STATE
	{
		AI_WAIT,
		AI_ATTACK
		//AI_Something...
	} nAIState, nNextAIState;

	enum GAME_STATE
	{
		GAME_RESET, // Stage when game is booted up ig
		GAME_PREPARE, // Stage starting each time when game round is ended
		GAME_PREPARING, // Stage for preparing stuff like deciding where to spawn player, start timer, idk
		GAME_ROUND_START, // Stage indicating round is start 
		GAME_ROUND_END, // Stage indicating round end, like when you survive
		GAME_OVER // Stage indicating that player failed ig or how it should be?
	} nGameState, nNextGameState;

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

		nAIState = AI_WAIT;
		nNextAIState = AI_WAIT;
		nGameState = GAME_RESET;
		nNextGameState = GAME_RESET;

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
		
		switch (nGameState)
		{
		case GAME_RESET:
			break;
		case GAME_PREPARE:
			break;
		case GAME_PREPARING:
			break;
		case GAME_ROUND_START:
			break;
		case GAME_ROUND_END:
			break;
		case GAME_OVER:
			break;
		}

		switch (nAIState)
		{
		case AI_WAIT:
			// Do waiting stuff like calculating players health and perfect... moment?
			nNextAIState = AI_ATTACK;

			break;
		case AI_ATTACK:
			// Attack the player, reduce player damage

			nNextAIState = AI_WAIT;
			break;
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