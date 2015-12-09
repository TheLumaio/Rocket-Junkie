#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

namespace lum {
	struct client_t {
		int id;
		unsigned short port;
		sf::IpAddress ip;
		
		client_t() {}
		client_t(int id, unsigned short port, sf::IpAddress ip) {
			this->id = id;
			this->port = port;
			this->ip = ip;
		}
	};
	
	class GameServer {
	private:
		sf::UdpSocket m_socket;
		sf::Thread m_thread;
		std::vector<client_t> m_clients;
		
		void update();
		void removeclient(sf::IpAddress);
		
	public:
		GameServer();
		~GameServer();
		
		void send(std::string);
		void start();
		void stop();
		
	};
}
