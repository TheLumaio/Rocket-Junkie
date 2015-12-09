#include "chatbox.hpp"

namespace lum {
	ChatBox::ChatBox(Engine& engine)
	{
		m_engine = &engine;
		
		m_engine->getemap()["type"] = thor::Action(sf::Event::TextEntered);
		m_engine->getsystem().connect("type", [&](thor::ActionContext<std::string> context){
			int u = context.event->text.unicode;
			
			if (u > 31 && u < 127) { // any character that's not "enter"
				m_message += (char)u;
			}
			
			if (u == 13) { // enter key
				tosend.push(m_message);
				m_message = "";
			}
			
			if (u == 8) { // backspace
				std::cout << "backspace" << std::endl;
				if (m_message.size() > 0)
					m_message.erase(m_message.size() - 1);
			}
			
		});
		
		
		resource_t font = m_engine->resmgr.getResource("opensans");
		if (font.type() == typeid(sf::Font)) {
			m_messagedraw.setFont(boost::get<sf::Font&>(font));
		}
		m_messagedraw.setColor(sf::Color::Black);
		m_messagedraw.setPosition(12, 720-28);
		m_messagedraw.setCharacterSize(12);
		m_messagedraw.setStyle(sf::Text::Style::Bold);
		
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
		changeRectangle(sf::Color(100, 100, 100), 10, 720-160, 300, 150, false, window);
		changeRectangle(sf::Color(75, 75, 75), 10, 720-30, 300, 20, false, window);
		changeRectangle(sf::Color(255, 255, 255), 10, 720-160, 300, 150, true, window);
		changeRectangle(sf::Color(255, 255, 255), 10, 720-30, 300, 20, true, window);
		window.draw(m_messagedraw);
	}
	
	void ChatBox::changeRectangle(sf::Color c, float x, float y, float w, float h, bool outline, sf::RenderWindow& window)
	{
		m_boxdraw.setPosition(x, y);
		m_boxdraw.setSize(sf::Vector2f(w, h));
		if (outline)
		{
			m_boxdraw.setOutlineColor(c);
			m_boxdraw.setFillColor(sf::Color::Transparent);
			m_boxdraw.setOutlineThickness(1);
		}
		else
		{
			m_boxdraw.setOutlineColor(sf::Color::Transparent);
			m_boxdraw.setFillColor(c);
			m_boxdraw.setOutlineThickness(0);
		}
		window.draw(m_boxdraw);
	}
	
}
