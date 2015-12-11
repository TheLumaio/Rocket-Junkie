#pragma once

#include <iostream>
#include <stack>
#include <cstring>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <boost/tokenizer.hpp>

namespace lum {
	class GameClient {
	private:
		sf::UdpSocket m_socket;
		sf::Thread m_thread;
		
		std::string m_serverip;
		unsigned short m_serverport;

		std::vector<std::string> m_tokens;
		
		void update();
		std::vector<std::string> tokenizepacket(std::string);
		
	public:
		std::stack<std::string> messages;

		GameClient();
		~GameClient();
		
		void send(std::string);
		void start(std::string, unsigned short);
		void stop();
		
	};
}
