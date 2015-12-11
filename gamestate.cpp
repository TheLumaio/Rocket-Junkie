#include "gamestate.hpp"

namespace lum {
	GameState::GameState(lum::Engine& engine)
	{
		this->m_engine = &engine;
	}
	
	GameState::GameState() {}
	GameState::~GameState() {}
	
	void GameState::init() {}
	void GameState::leave() {}
	void GameState::update(float dt, thor::ActionMap<std::string>& map) {}
	void GameState::render(sf::RenderWindow& window) {}
}
