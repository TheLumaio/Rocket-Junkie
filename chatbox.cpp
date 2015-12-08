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
				m_message.pop_back();
			}
			
		});
		
	}
	ChatBox::ChatBox() {}
	ChatBox::~ChatBox() {}
	
	void ChatBox::addChat(std::string chat)
	{
		m_chats.emplace_back(chat);
	}
	
	void ChatBox::update(float dt)
	{
		
	}
	
	void ChatBox::render(sf::RenderWindow& window)
	{
		
	}
	
}
