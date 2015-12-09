#include "chatbox.hpp"

namespace lum {
	ChatBox::ChatBox(Engine& engine)
	{
		m_engine = &engine;
		
		m_engine->getemap()["type"] = thor::Action(sf::Event::TextEntered);
		m_engine->getsystem().connect("type", [&](thor::ActionContext<std::string> context){
			int u = context.event->text.unicode;
			
			if (u != 13) { // any character that's not "enter"
				m_message += (char)u;
			}
			
			if (u == 13) { // enter key
				tosend.push(m_message);
				m_message = "";
			}
			
			if (u == 8) { // backspace
				std::cout << "backspace" << std::endl;
				m_message = m_message.erase(m_message.size() - 1);
			}
			
		});
		
		
		resource_t font = m_engine->resmgr.getResource("opensans");
		if (font.type() == typeid(sf::Font)) {
			m_messagedraw.setFont(boost::get<sf::Font&>(font));
		}
		m_messagedraw.setPosition(20, 540-50);
		m_messagedraw.setCharacterSize(12);
		
	}
	ChatBox::ChatBox() {}
	ChatBox::~ChatBox() {}
	
	void ChatBox::addChat(std::string chat)
	{
		m_chats.emplace_back(chat);
	}
	
	void ChatBox::update(float dt)
	{
		m_messagedraw.setString(m_message);
	}
	
	void ChatBox::render(sf::RenderWindow& window)
	{
		window.draw(m_messagedraw);
	}
	
}
