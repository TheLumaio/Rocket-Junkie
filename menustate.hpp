#pragma once

#include <iostream>
#include <cmath>
#include "gamestate.hpp"
#include "chatbox.hpp"

namespace lum {
	class MenuState : public lum::GameState {
	private:
		sf::RectangleShape m_drawtest;
		ChatBox chatbox;
		float timer;
		float sine;
		
	public:
		MenuState(Engine& engine);
		MenuState();
		~MenuState();
		
		void init();
		void update(float, thor::ActionMap<std::string>&);
		void render(sf::RenderWindow&);
		
	};
}
