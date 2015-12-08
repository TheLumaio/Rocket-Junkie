#pragma once

#include <iostream>
#include <stack>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

namespace lum {
	class GameClient {
	private:
		sf::UdpSocket m_socket;
		sf::Thread m_thread;
		
		std::string m_serverip;
		unsigned short m_serverport;
		
		std::stack<std::string> m_data;
		
		void update();
		
	public:
		GameClient();
		~GameClient();
		
		void send(std::string);
		void start(std::string, unsigned short);
		void stop();
		
	};
}
