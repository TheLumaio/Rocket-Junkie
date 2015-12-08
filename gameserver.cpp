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
		while (true)
		{
			char data[128];
			std::size_t received;
			sf::IpAddress sender;
			unsigned short port;
			
			m_socket.receive(data, sizeof(data), received, sender, port);
			
		}
	}
	
}
