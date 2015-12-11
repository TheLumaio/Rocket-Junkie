#include "chatbox.hpp"

namespace lum {
	ChatBox::ChatBox(Engine& engine)
	{
		m_engine = &engine;
		
		m_enabled = false;
		m_alpha = 1;
		
		m_engine->getemap()["type"] = thor::Action(sf::Event::TextEntered);
		m_engine->getsystem().connect("type", [&](thor::ActionContext<std::string> context){
			if (!m_enabled)
				return;
			
			int u = context.event->text.unicode;
			
			if (u > 31 && u < 127) { // ascii text characters
				if (!m_enabled) return;
				m_message += (char)u;
			}
			
			if (u == 13) { // enter key
				if (!m_enabled || m_message.size() < 1) return;
				tosend.push(m_message);
				m_message = "";
			}
			
			if (u == 8) { // backspace
				if (!m_enabled) return;
				if (m_message.size() > 0)
					m_message.erase(m_message.size() - 1);
			}
			
		});
		
		
		resource_t font = m_engine->resmgr.getResource("anonymous");
		if (font.type() == typeid(sf::Font)) {
			m_messagedraw.setFont(boost::get<sf::Font&>(font));
			m_chatdraw.setFont(boost::get<sf::Font&>(font));
		}
		m_messagedraw.setString("");
		m_messagedraw.setColor(sf::Color::Black);
		m_messagedraw.setPosition(12, 720-28);
		m_messagedraw.setCharacterSize(12);
		
		m_chatdraw.setColor(sf::Color::Black);
		m_chatdraw.setPosition(0, 0);
		m_chatdraw.setCharacterSize(12);
		
		for (int i = 0; i < 10; i++) { m_chats.emplace_back(""); }
		
	}
	ChatBox::ChatBox() {}
	ChatBox::~ChatBox() {}
	
	void ChatBox::addChat(std::string chat)
	{
		m_chats.emplace_back(chat);
	}
	
	void ChatBox::update(float dt)
	{
		if (!m_enabled)
		{
			if (m_alpha > 0)
				m_alpha *= 0.994;
			if (m_alpha <= 0.01)
				m_alpha = 0.01;
		}
		else
		{
			if (m_alpha < 1)
				m_alpha /= 0.994;
			if (m_alpha >= 0.99)
				m_alpha = 0.99;
		}
		m_messagedraw.setString(m_message);
	}
	
	void ChatBox::render(sf::RenderWindow& window)
	{
		// set text alpha
		m_messagedraw.setColor(sf::Color(0, 0, 0, m_alpha*255));
		m_chatdraw.setColor(sf::Color(0, 0, 0, m_alpha*255));

		// draw bounding boxes
		changeRectangle(sf::Color(100, 100, 100, m_alpha*255), 10, 720-160, 300, 150, false, window);
		changeRectangle(sf::Color(75, 75, 75, m_alpha*255), 10, 720-30, 300, 20, false, window);
		changeRectangle(sf::Color(255, 255, 255, m_alpha*255), 10, 720-160, 300, 150, true, window);
		changeRectangle(sf::Color(255, 255, 255, m_alpha*255), 10, 720-30, 300, 20, true, window);
		// draw current text
		changeText(m_message, 12, 720-28, window);

		float width = m_messagedraw.findCharacterPos(m_message.size()-1).x - m_messagedraw.findCharacterPos(0).x;
		// draw cursor
		changeRectangle(sf::Color::Black, 12+width+(width/m_message.size()), 720-28, 1, 15, false, window);
		
		// draw previous messages
		for (int i = 0; i < 10; i++)
		{
			std::string text = m_chats[m_chats.size()-(i+1)];
			changeText(text, 12, (720-50)-i*12, window);
		}
	}
	
	void ChatBox::toggle()
	{
		m_enabled = !m_enabled;
	}

	void ChatBox::setEnabled(bool e)
	{
		m_enabled = e;
	}

	bool ChatBox::isEnabled()
	{
		return m_enabled;
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
	
	void ChatBox::changeText(std::string text, float x, float y, sf::RenderWindow& window)
	{
		m_chatdraw.setString(text);
		m_chatdraw.setPosition(x, y);
		window.draw(m_chatdraw);
	}
	
}
