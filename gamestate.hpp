#pragma once

#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>
#include "engine.hpp"

namespace lum {
	class Engine;
	class GameState {
	protected:
		lum::Engine* m_engine;
	
	public:
		GameState(Engine&);
		GameState();
		~GameState();
		
		virtual void init();
		virtual void update(float, thor::ActionMap<std::string>&);
		virtual void render(sf::RenderWindow&);
		
	};
}
