#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <boost/tokenizer.hpp>
#include "engine.hpp"
#include "server.hpp"

namespace lum {
	class ChatBox {
	private:
		Engine* m_engine;
		std::vector<std::string> m_chats;
		std::string m_message;
		
		sf::RectangleShape m_boxdraw;
		sf::Text m_messagedraw;
		sf::Text m_chatdraw;
		
		bool m_enabled;
		float m_alpha;
		
		void changeRectangle(sf::Color, float, float, float, float, bool, sf::RenderWindow&);
		void changeText(std::string, float, float, sf::RenderWindow&);
		std::vector<std::string> tokenizecommand(std::string);
	
	public:
		std::stack<std::string> tosend;
		
		ChatBox(Engine& engine);
		ChatBox();
		~ChatBox();
		
		void addChat(std::string);
		void update(float);
		void render(sf::RenderWindow&);
		
		void toggle();
		void setEnabled(bool);
		bool isEnabled();
	};
}
