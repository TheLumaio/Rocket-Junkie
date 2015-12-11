#include "gameserver.hpp"

namespace lum {
	GameServer::GameServer() :
		m_thread(&GameServer::update, this)
	{
		m_socket.setBlocking(true);
	}
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
			if (!m_tokens.empty())
				m_tokens.clear();

			char data[128];
			std::size_t received;
			sf::IpAddress sender;
			unsigned short port;

			memset(&data[0], 0, sizeof(data));
			
			m_socket.receive(data, sizeof(data), received, sender, port);
			if (strcmp(data, "connect") == 0)
				m_clients.emplace_back(client_t(m_clients.size()+1, port, sender));
			if (strcmp(data, "disconnect") == 0)
				removeclient(sender);

			m_tokens = tokenizepacket(std::string(data));
			if (m_tokens.size() > 0)
			{
				if (strcmp(m_tokens[0].c_str(), "message") == 0 && m_tokens.size() > 1)
				{
					std::string message = "message ";
					message += "<";
					message += std::to_string(getclientid(sender, port));
					message += "> ";
					for (int i = 1; i < m_tokens.size(); i++) { message.append(m_tokens[i]); message.append(" "); }
					std::cout << "SERVER: " << message << std::endl;
					for (client_t& c : m_clients)
					{
						std::cout << c.port << std::endl;
						m_socket.send(message.c_str(), message.size(), c.ip, c.port);
					}
				}
			}
			
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

	std::vector<std::string> GameServer::tokenizepacket(std::string packet)
	{
		std::transform(packet.begin(), packet.end(), packet.begin(), ::tolower);
		
		boost::char_separator<char> sep(" ");
		boost::tokenizer<boost::char_separator<char>> tokens(packet, sep);
		
		std::vector<std::string> strs;
		
		for (const auto& t: tokens)
			strs.emplace_back(t);

		return strs;
	}

	int GameServer::getclientid(sf::IpAddress ip, unsigned short port)
	{
		int index = -1;
		for (int i = 0; i < m_clients.size(); i++)
		{
			if (m_clients[i].ip == ip && m_clients[i].port == port)
				index = m_clients[i].id;
		}

		return index;
	}
	
}
