#include "board.hpp"

namespace lum {
	Board::Board(Engine& engine) :
		m_position(300, 50)
	{
		// how is this legal syntax?
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				m_nodes[i][j] = node_t(0);
	
		m_text.setFont(boost::get<sf::Font&>(engine.resmgr.getResource("anonymous")));
		m_text.setString("");
		m_text.setPosition(0, 0);
		m_text.setCharacterSize(12);
	
	}

	Board::Board() {}
	Board::~Board() {}

	void Board::update(float dt)
	{

	}

	void Board::render(sf::RenderWindow& window)
	{
		// board outline
		drawrectangle(sf::Color::White, m_position.x, m_position.y, 155, 155, true, window);
		// board background
		drawrectangle(sf::Color(125, 125, 125), m_position.x, m_position.y, 155, 155, false, window);
		
		// nodes
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				drawrectangle(sf::Color::White, m_position.x+5+i*30, m_position.y+5+j*30, 25, 25, true, window);
				drawrectangle(sf::Color(100, 100, 100), m_position.x+5+i*30, m_position.y+5+j*30, 25, 25, false, window);
				drawtext(std::to_string(m_nodes[i][j].value), m_position.x+13+i*30, m_position.y+8+j*30, window);
			}
		}
	}
	
	void Board::drawrectangle(sf::Color color, float x, float y, float w, float h, bool outline, sf::RenderWindow& window)
	{
		m_shape.setPosition(x, y);
		m_shape.setSize(sf::Vector2f(w, h));
		
		if (outline)
		{
			m_shape.setOutlineColor(color);
			m_shape.setFillColor(sf::Color::Transparent);
			m_shape.setOutlineThickness(1);
		}
		else
		{
			m_shape.setOutlineColor(sf::Color::Transparent);
			m_shape.setFillColor(color);
			m_shape.setOutlineThickness(0);
		}
		
		window.draw(m_shape);
	}
	
	void Board::drawtext(std::string text, float x, float y, sf::RenderWindow& window)
	{
		m_text.setString(text);
		m_text.setPosition(x, y);
		window.draw(m_text);
	}
}
