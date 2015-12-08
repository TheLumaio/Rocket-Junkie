#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include "engine.hpp"

namespace lum {
	class ChatBox {
	private:
		Engine* m_engine;
		std::vector<std::string> m_chats;
		std::string m_message;
		
		sf::RectangleShape m_draw;
		
	public:
		std::stack<std::string> tosend;
		
		ChatBox(Engine& engine);
		ChatBox();
		~ChatBox();
		
		void addChat(std::string);
		void update(float);
		void render(sf::RenderWindow&);
	};
}
