#include "menustate.hpp"

namespace lum {
	MenuState::MenuState(Engine& engine) :
		GameState(engine),
		chatbox(engine)
	{
		m_drawtest.setFillColor(sf::Color::Red);
		m_drawtest.setPosition(100, 100);
		m_drawtest.setSize(sf::Vector2f(100, 10));
		timer = 0;
		sine = 0;
	}
	
	MenuState::MenuState()
	{
		std::cout << "NO ENGINE SPECIFIED. YOU MUST PASS THE ENGINE TO THE CONSTRUCTOR." << std::endl;
	}
	MenuState::~MenuState() {}
	
	
	void MenuState::init()
	{
	}
	
	void MenuState::update(float dt, thor::ActionMap<std::string>& emap)
	{
		timer += dt;
		m_drawtest.setPosition(100+sin(0.3*timer)*100, 100);
		
		chatbox.update(dt);
	}
	
	void MenuState::render(sf::RenderWindow& window)
	{
		window.draw(m_drawtest);
		chatbox.render(window);
	}
	
}
