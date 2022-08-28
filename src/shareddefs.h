#pragma once
#include <cstdint>
#include "olcPixelGameEngine.h"
enum class MsgHeaders : uint32_t
{
	// Generic server headers
	SERVER_STATUS,
	SERVER_PING,

	// Client headers
	CLIENT_VALIDATED,
	CLIENT_ASSIGNID,
	CLIENT_REGISTER,
	CLIENT_UNREGISTER,

	// Game headers
	GAME_JOIN_PLAYER,
	GAME_DISCONNECT_PLAYER,
	GAME_UPDATE_PLAYER


};

struct PlayerDescription
{
	uint32_t playerID;
	olc::vf2d vPos;
};