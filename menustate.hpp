#pragma once

#include <iostream>
#include <cmath>
#include "gamestate.hpp"
#include "chatbox.hpp"

namespace lum {
	class MenuState : public lum::GameState {
	private:
		sf::RectangleShape m_drawtest;
		ChatBox m_chatbox;
		float m_timer;
		float m_sine;

		sf::Text m_debugtext;
		
		GameServer m_server;
		GameClient m_client;
		
	public:
		MenuState(Engine& engine);
		MenuState();
		~MenuState();
		
		void init();
		void leave();
		void update(float, thor::ActionMap<std::string>&);
		void render(sf::RenderWindow&);
		
	};
}
