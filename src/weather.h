#ifndef WEATHER_H
#define WEATHER_H

#include "shareddefs.h"

enum THUNDER_ACTION_STATE
{
	THUNDER_ACTION_STATE_NONE,
	THUNDER_ACTION_STATE_START_ACTIVE,
	THUNDER_ACTION_STATE_ON_FIRE,
	THUNDER_ACTION_STATE_END_ACTIVE,

	THUNDER_ACTION_STATE_MAX
};

class cThunder
{
public:
	cThunder();
	~cThunder();

	void SetActionState(THUNDER_ACTION_STATE nActionState);

	void Update(float dt);

	void Render(olc::PixelGameEngine* pEngine);

private:
	enum THUNDER_STATE
	{
		THUNDER_STATE_1,
		THUNDER_STATE_2,
		THUNDER_STATE_3,

		THUNDER_STATE_MAX
	};

	olc::Sprite* m_pThunderSprites[THUNDER_STATE_MAX];
	olc::Sprite* m_pActiveSprite;

	THUNDER_ACTION_STATE m_nCurrentState;
	THUNDER_ACTION_STATE m_nTransitionState;

	float m_fTime;
};

#endif