#pragma once

#include <iostream>
#include <stack>
#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>
#include "resourcemanager.hpp"
#include "gamestate.hpp"
#include "gameserver.hpp"
#include "gameclient.hpp"

namespace lum {
	class GameState;
	class Engine {
	private:
		sf::RenderWindow m_window;
		thor::ActionMap<std::string> m_emap;
		thor::ActionMap<std::string>::CallbackSystem m_sys;
		std::stack<lum::GameState*> m_states;
		
		GameServer m_server;
		GameClient m_client;
		
		void printHello(thor::ActionContext<std::string> context);
		
	public:
		lum::ResourceManager resmgr;
		
		Engine();
		~Engine();
		
		void start();
		void changeState(lum::GameState*);
		
		thor::ActionMap<std::string>& getemap();
		thor::ActionMap<std::string>::CallbackSystem& getsystem();
		
	};
}
