#include "gameclient.hpp"

namespace lum {
	GameClient::GameClient() :
		m_thread(&GameClient::update, this)
	{
		m_socket.setBlocking(true);
	}
	GameClient::~GameClient() {}
	
	void GameClient::send(std::string data)
	{
		m_socket.send(data.c_str(), data.size(), m_serverip, m_serverport);
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

			char data[128];
			std::size_t received;
			sf::IpAddress sender;
			unsigned short port;

			memset(&data[0], 0, sizeof(data));
			
			m_socket.receive(data, sizeof(data), received, sender, port);

			m_tokens = tokenizepacket(std::string(data));
			if (m_tokens.size() > 0)
			{
				std::cout << data << std::endl;
				if (strcmp(m_tokens[0].c_str(), "message") == 0 && m_tokens.size() > 1)
				{
					std::string message = "";
					for (int i = 1; i < m_tokens.size(); i++) { message.append(m_tokens[i]); message.append(" "); }
					std::cout << "CLIENT: " << message << std::endl;
					messages.push(message);
				}
			}

		}
	}

	std::vector<std::string> GameClient::tokenizepacket(std::string packet)
	{
		std::transform(packet.begin(), packet.end(), packet.begin(), ::tolower);
		
		boost::char_separator<char> sep(" ");
		boost::tokenizer<boost::char_separator<char>> tokens(packet, sep);
		
		std::vector<std::string> strs;
		
		for (const auto& t: tokens)
			strs.emplace_back(t);

		return strs;
	}
	
}
