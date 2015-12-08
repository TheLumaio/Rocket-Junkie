#pragma once

#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

namespace lum {
	class GameServer {
	private:
		sf::UdpSocket m_socket;
		sf::Thread m_thread;
		
		void update();
		
	public:
		GameServer();
		~GameServer();
		
		void send(std::string);
		void start();
		void stop();
		
	};
}
