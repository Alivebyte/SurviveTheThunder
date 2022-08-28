#pragma once
#include "Extensions/olcPGEX_Network.h"
#include "shareddefs.h"
#include <vector>
#include <unordered_map>

class cListenServer : public olc::net::server_interface<MsgHeaders>
{
public:
	cListenServer(uint16_t n_Port) : olc::net::server_interface<MsgHeaders>(n_Port)
	{

	}				  

	std::unordered_map<uint32_t, PlayerDescription> m_mapPlayerRoster;
	std::vector<uint32_t> m_vGarbageIDs;

	bool IsCreated()
	{
		return true;
	}
protected:
	bool OnClientConnect(std::shared_ptr<olc::net::connection<MsgHeaders>> client) override
	{
		// For now we will allow all 
		return true;
	}

	void OnClientValidated(std::shared_ptr<olc::net::connection<MsgHeaders>> client) override
	{
		// Client passed validation check, so send them a message informing
		// them they can continue to communicate
		olc::net::message<MsgHeaders> msg;
		msg.header.id = MsgHeaders::CLIENT_VALIDATED;
		client->Send(msg);
	}

	void OnMessage(std::shared_ptr<olc::net::connection<MsgHeaders>> client, olc::net::message<MsgHeaders>& msg) override
	{
		switch (msg.header.id)
		{
		case MsgHeaders::CLIENT_REGISTER:
		{
			PlayerDescription desc;
			msg >> desc;
			desc.playerID = client->GetID();
			m_mapPlayerRoster.insert_or_assign(desc.playerID, desc);

			olc::net::message<MsgHeaders> msgSendID;
			msgSendID.header.id = MsgHeaders::CLIENT_ASSIGNID;
			msgSendID << desc;
			MessageClient(client, msgSendID);

			olc::net::message<MsgHeaders> msgAddPlayer;
			msgAddPlayer.header.id = MsgHeaders::GAME_JOIN_PLAYER;
			msgAddPlayer << desc;
			MessageAllClients(msgAddPlayer);

			for (const auto& player : m_mapPlayerRoster)
			{
				olc::net::message<MsgHeaders> msgAddOtherPlayers;
				msgAddOtherPlayers.header.id = MsgHeaders::GAME_JOIN_PLAYER;
				msgAddOtherPlayers << player.second;
				MessageClient(client, msgAddOtherPlayers);
			}

			break;
		}
		case MsgHeaders::CLIENT_UNREGISTER:
		{
			break;
		}
		case MsgHeaders::GAME_UPDATE_PLAYER:
		{
			MessageAllClients(msg, client);
			break;
		}
		}
	}

};

class cClient : public olc::net::client_interface<MsgHeaders>
{
public:
	cClient()
	{
		
	}

private:
};