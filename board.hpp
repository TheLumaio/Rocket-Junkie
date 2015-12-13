#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <boost/tokenizer.hpp>
#include "engine.hpp"

namespace lum {
	struct node_t {
		int value;
		node_t () {};
		node_t (int v) { value = v; };
	};
	
	class Board {
	private:
		node_t m_nodes[5][5];
		sf::RectangleShape m_shape;
		sf::Text m_text;
		sf::Vector2f m_position;
		sf::Vector2i m_index;
		sf::Vector2i m_mpos;
		
		bool m_clicked;
		bool m_blocked;
		
		void drawrectangle(sf::Color, float, float, float, float, bool, sf::RenderWindow&);
		void drawtext(std::string, float, float, sf::RenderWindow&);

	public:
		Board(Engine&);
		Board();
		~Board();

		void update(float, bool);
		void render(sf::RenderWindow&);

	};
}
