#include "engine.hpp"

namespace lum {
	Engine::Engine() :
		m_window(sf::VideoMode(1280, 720), "Rocket Junkie", sf::Style::Close)
	{
		m_emap["close"] = thor::Action(sf::Event::Closed);
		
		resmgr.loadResource("opensans", "assets/OpenSans.ttf");
		resmgr.loadResource("anonymous", "assets/anonymouspro.ttf");
	}
	
	Engine::~Engine()
	{
	}
	
	void Engine::start()
	{
		
		sf::Clock deltaClock;
		
		while (m_window.isOpen())
		{
			m_emap.invokeCallbacks(m_sys, &m_window);
			
			m_emap.update(m_window);
			if (m_emap.isActive("close"))
				m_window.close();
				
			float dt = deltaClock.restart().asSeconds();
			
			if (!m_states.empty())
				m_states.top()->update(dt, m_emap);
			
			m_window.clear(sf::Color::Black);
			
			if (!m_states.empty())
				m_states.top()->render(m_window);
			
			m_window.display();
			
		}
	}
	
	void Engine::changeState(lum::GameState *state)
	{
		if (!m_states.empty())
		{
			m_states.top()->leave();
			m_states.top() = nullptr;
			m_states.pop();
		}
		m_states.push(state);
		m_states.top()->init();
	}
	
	
	thor::ActionMap<std::string>& Engine::getemap()
	{
		return m_emap;
	}
	
	thor::ActionMap<std::string>::CallbackSystem& Engine::getsystem()
	{
		return m_sys;
	}
	
	void Engine::printHello(thor::ActionContext<std::string> context)
	{
		std::cout << "hello" << std::endl;
	}
	
}
