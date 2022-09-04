#include "weather.h"
#include "resourcemanager.h"

const float kSpriteChangeTime = 2.5f;

cThunder::cThunder()
{
	m_nCurrentState = THUNDER_ACTION_STATE_NONE;
	m_nTransitionState = THUNDER_ACTION_STATE_NONE;
	m_pThunderSprites[THUNDER_STATE_1] = g_pResourceManager->LoadSprite("res/test/thunder_1.png");
	m_pThunderSprites[THUNDER_STATE_2] = g_pResourceManager->LoadSprite("res/test/thunder_2.png");
	m_pThunderSprites[THUNDER_STATE_3] = g_pResourceManager->LoadSprite("res/test/thunder_3.png");
	m_pActiveSprite = nullptr;
}

cThunder::~cThunder()
{
	m_pThunderSprites[THUNDER_STATE_1] = nullptr;
	m_pThunderSprites[THUNDER_STATE_2] = nullptr;
	m_pThunderSprites[THUNDER_STATE_3] = nullptr;
	m_pActiveSprite = nullptr;
}

void cThunder::SetActionState(THUNDER_ACTION_STATE nActionState)
{
	//if ()
}

void cThunder::Update(float dt)
{
	if (m_nCurrentState == THUNDER_ACTION_STATE_ON_FIRE)
	{

	}
}

void cThunder::Render(olc::PixelGameEngine* pEngine)
{
	olc::vd2d vPosition = olc::vd2d(1.0f, 1.0f);
	pEngine->DrawSprite(vPosition, m_pThunderSprites[THUNDER_STATE_1]);
}
