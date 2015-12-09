#include "gameclient.hpp"

namespace lum {
	GameClient::GameClient() :
		m_thread(&GameClient::update, this)
	{ }
	GameClient::~GameClient() {}
	
	void GameClient::send(std::string data)
	{
		// add data to buffer
		m_data.push(data);
	}
	
	void GameClient::start(std::string ip, unsigned short port)
	{
		m_serverip = ip;
		m_serverport = port;
		
		send("connect");
		
		m_thread.launch();
	}
	
	void GameClient::stop()
	{
		m_thread.terminate();
		send("disconnect");
	}
	
	void GameClient::update()
	{
		while (true)
		{
			// Send all buffered data
			while (!m_data.empty())
			{
				m_socket.send(m_data.top().c_str(), m_data.top().size(), m_serverip, m_serverport);
				m_data.pop();
			}
			
			char data[128];
			std::size_t received;
			sf::IpAddress sender;
			unsigned short port;
			
			m_socket.receive(data, sizeof(data), received, sender, port);
		}
	}
	
}
