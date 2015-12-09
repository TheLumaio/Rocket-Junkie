#include "gameserver.hpp"

namespace lum {
	GameServer::GameServer() :
		m_thread(&GameServer::update, this)
	{ }
	GameServer::~GameServer() {}
	
	void GameServer::start()
	{
		m_socket.bind(27015);
		m_thread.launch();
	}
	
	void GameServer::stop()
	{
		m_thread.terminate();
	}
	
	void GameServer::update()
	{
		while (true) // TODO: change this to not be ass
		{
			char data[128];
			std::size_t received;
			sf::IpAddress sender;
			unsigned short port;
			
			m_socket.receive(data, sizeof(data), received, sender, port);
			if (strcmp(data, "connect") == 0)
				m_clients.emplace_back(client_t(m_clients.size()+1, port, sender));
			if (strcmp(data, "disconnect") == 0)
				removeclient(sender);
			
		}
	}
	
	void GameServer::removeclient(sf::IpAddress ip)
	{
		int index = 0;
		for (int i = 0; i < m_clients.size(); i++)
		{
			if (m_clients[i].ip == ip)
				index = i+1; // this is a really shitty way of doing it but I'm lazy
		}
		
		if (index > 0)
			m_clients.erase(m_clients.begin() + index-1);
	}
	
}
