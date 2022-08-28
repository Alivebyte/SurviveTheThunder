#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
//#include "Extensions/olcPGEX_Network.h"
//#include "network.h" Not using since I don't know everything about it
#define OLC_PGEX_TRANSFORMEDVIEW
#include "Extensions/olcPGEX_TransformedView.h"
#include "resourcemanager.h"
struct Player
{
	olc::vf2d vPos;
	olc::vf2d vVel;
	float flSize;
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
		tv = olc::TileTransformedView({ ScreenWidth(), ScreenHeight() }, { 8, 8 });
		
		// Resource manager init
		g_pResourceManager = new cResourceManager();
		g_pResourceManager->Init();

		player.vPos = { 3.0f, 3.0f };
		player.flSize = 0.1f;
		/*olc::ResourcePack* pResourcePack = new olc::ResourcePack();
		pResourcePack->AddFile("res/test.bmp");

		pResourcePack->SavePack("datapc_main.respack", "easy peasy lemon squeezy");*/

		m_pSprite = g_pResourceManager->LoadSprite("res/player.png");

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

		player.vVel = { 0,0 };
		if (GetKey(olc::Key::UP).bHeld || GetKey(olc::Key::W).bHeld) player.vVel += {0.0f, -1.0f};
		if (GetKey(olc::Key::DOWN).bHeld || GetKey(olc::Key::S).bHeld) player.vVel += {0.0f, +1.0f};
		if (GetKey(olc::Key::LEFT).bHeld || GetKey(olc::Key::A).bHeld) player.vVel += {-1.0f, 0.0f};
		if (GetKey(olc::Key::RIGHT).bHeld || GetKey(olc::Key::D).bHeld) player.vVel += {+1.0f, 0.0f};

		if (player.vVel.mag2() > 0)
			player.vVel = player.vVel.norm() * 4.0f;

		// Where will object be worst case?
		olc::vf2d vPotentialPosition = player.vPos + player.vVel * fElapsedTime;

		// Extract region of world cells that could have collision this frame
		olc::vi2d vCurrentCell = player.vPos;
		olc::vi2d vTargetCell = vPotentialPosition;
		olc::vi2d vAreaTL = (vCurrentCell.min(vTargetCell) - olc::vi2d(1, 1)).max({ 0,0 });
		olc::vi2d vAreaBR = (vCurrentCell.max(vTargetCell) + olc::vi2d(1, 1)).min(vWorldSize);

		// Iterate through each cell in test area
		olc::vi2d vCell;
		for (vCell.y = vAreaTL.y; vCell.y <= vAreaBR.y; vCell.y++)
		{
			for (vCell.x = vAreaTL.x; vCell.x <= vAreaBR.x; vCell.x++)
			{
				// Check if the cell is actually solid...
			//	olc::vf2d vCellMiddle = vCell.floor();
				if (sWorldMap[vCell.y * vWorldSize.x + vCell.x] == '#')
				{
					// ...it is! So work out nearest point to future player position, around perimeter
					// of cell rectangle. We can test the distance to this point to see if we have
					// collided.

					olc::vf2d vNearestPoint;
					// Inspired by this (very clever btw) 
					// https://stackoverflow.com/questions/45370692/circle-rectangle-collision-response
					vNearestPoint.x = std::max(float(vCell.x), std::min(vPotentialPosition.x, float(vCell.x + 1)));
					vNearestPoint.y = std::max(float(vCell.y), std::min(vPotentialPosition.y, float(vCell.y + 1)));

					// But modified to work :P
					olc::vf2d vRayToNearest = vNearestPoint - vPotentialPosition;
					float fOverlap = player.flSize - vRayToNearest.mag();
					if (std::isnan(fOverlap)) fOverlap = 0;// Thanks Dandistine!

					// If overlap is positive, then a collision has occurred, so we displace backwards by the 
					// overlap amount. The potential position is then tested against other tiles in the area
					// therefore "statically" resolving the collision
					if (fOverlap > 0)
					{
						// Statically resolve the collision
						vPotentialPosition = vPotentialPosition - vRayToNearest.norm() * fOverlap;
					}
				}
			}


			// Set the objects new position to the allowed potential position
			player.vPos = vPotentialPosition;
		}

		if (GetMouse(2).bPressed) tv.StartPan(GetMousePos());
		if (GetMouse(2).bHeld) tv.UpdatePan(GetMousePos());
		if (GetMouse(2).bReleased) tv.EndPan(GetMousePos());
		if (GetMouseWheel() > 0) tv.ZoomAtScreenPos(1.5f, GetMousePos());
		if (GetMouseWheel() < 0) tv.ZoomAtScreenPos(0.75f, GetMousePos());

		Clear(olc::BLACK);

		


		// Draw World
		olc::vi2d vTL = tv.GetTopLeftTile().max({ 0,0 });
		olc::vi2d vBR = tv.GetBottomRightTile().min(vWorldSize);
		olc::vi2d vTile;
		for (vTile.y = vTL.y; vTile.y < vBR.y; vTile.y++)
			for (vTile.x = vTL.x; vTile.x < vBR.x; vTile.x++)
			{
				if (sWorldMap[vTile.y * vWorldSize.x + vTile.x] == '#')
				{
					tv.DrawRect(vTile, { 1.0f, 1.0f });
					tv.DrawRect(olc::vf2d(vTile) + olc::vf2d(0.1f, 0.1f), { 0.8f, 0.8f });
				}
			}

		// Draw Player
		if (m_pSprite)
		{
			tv.DrawSprite(player.vPos.x - 1.0f, player.vPos.y - 1.0f, m_pSprite, player.flSize, player.flSize);
			
			//tv.DrawCircle(player.vPos, player.flSize);

			if (player.vVel.mag2() > 0)
				tv.DrawLine(player.vPos, player.vPos + player.vVel.norm() * player.flSize, olc::MAGENTA);
		}

		return true;
	}

private:
	olc::TileTransformedView tv;
	std::string sWorldMap =
		"################################"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#.......##...####..............#"
		"#.........##.........#.........#"
		"#.........#.#.......###........#"
		"#...................###........#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#.................####.........#"
		"#....................#.........#"
		"#..........#......#..###.......#"
		"#..........#.......###.........#"
		"#..........#....##..#####......#"
		"#..............................#"
		"#........####......#.#.#.#.....#"
		"#........#.....................#"
		"#........####......#.#.#.#.....#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"#..............................#"
		"################################";

	olc::vi2d vWorldSize = { 32, 32 };
	Player player;
	
};


int main()
{
	App application;
	if (application.Construct(512, 512, 1, 1))
		application.Start();

	return 0;
}