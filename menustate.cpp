#include "menustate.hpp"

namespace lum {
	MenuState::MenuState(Engine& engine) :
		GameState(engine),
		m_chatbox(engine)
	{ }
	
	MenuState::MenuState()
	{
		std::cout << "NO ENGINE SPECIFIED. YOU MUST PASS THE ENGINE TO THE CONSTRUCTOR." << std::endl;
	}
	MenuState::~MenuState() {}
	
	
	void MenuState::init()
	{	
		m_drawtest.setFillColor(sf::Color::Red);
		m_drawtest.setPosition(100, 100);
		m_drawtest.setSize(sf::Vector2f(100, 10));
		m_timer = 0;
		m_sine = 0;

		m_debugtext.setFont(boost::get<sf::Font&>(m_engine->resmgr.getResource("opensans")));
		m_debugtext.setString("1. server, 2. client\n\nCurrently started:\n");
		m_debugtext.setPosition(10, 10);
		m_debugtext.setCharacterSize(14);

		m_engine->getemap()["selectserver"] = thor::Action(sf::Keyboard::Num1, thor::Action::PressOnce);
		m_engine->getemap()["selectclient"] = thor::Action(sf::Keyboard::Num2, thor::Action::PressOnce);

		m_engine->getsystem().connect("selectserver", [&](context_t context){ m_server.start(); m_debugtext.setString(m_debugtext.getString() + "SERVER\n"); });
		m_engine->getsystem().connect("selectclient", [&](context_t context){ m_client.start("localhost", 27015); m_debugtext.setString(m_debugtext.getString() + "CLIENT\n"); });

		m_engine->getemap()["enterchat"] = thor::Action(sf::Keyboard::Return, thor::Action::PressOnce);
		m_engine->getemap()["exitchat"] = thor::Action(sf::Keyboard::Escape, thor::Action::PressOnce);

		m_engine->getsystem().connect("enterchat", [&](context_t context) {
			if (m_chatbox.isEnabled())
				return;
			m_chatbox.setEnabled(true);
		});

		m_engine->getsystem().connect("exitchat", [&](context_t context) {
			if (m_chatbox.isEnabled())
				m_chatbox.setEnabled(false);
		});
	}

	void MenuState::leave()
	{
		m_client.stop();
		m_server.stop();
	}
	
	void MenuState::update(float dt, thor::ActionMap<std::string>& emap)
	{
		m_timer += dt;
		m_drawtest.setPosition(100+sin(0.3*m_timer)*100, 100);
		
		m_chatbox.update(dt);
		
		if (!m_chatbox.tosend.empty())
		{
			std::string packet = "message ";
			packet.append(m_chatbox.tosend.top());
			m_client.send(packet);
			m_chatbox.tosend.pop();
		}

		if (!m_client.messages.empty())
		{
			m_chatbox.addChat(m_client.messages.top());
			m_client.messages.pop();
		}

	}
	
	void MenuState::render(sf::RenderWindow& window)
	{
		window.draw(m_drawtest);
		window.draw(m_debugtext);
		m_chatbox.render(window);
	}
	
}
