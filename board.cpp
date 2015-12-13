#include "board.hpp"

namespace lum {
	Board::Board(Engine& engine) :
		m_position(300, 50),
		m_index(-1, -1),
		m_mpos(0, 0)
	{
		// how is this legal syntax?
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				m_nodes[i][j] = node_t(0);
	
		m_text.setFont(boost::get<sf::Font&>(engine.resmgr.getResource("anonymous")));
		m_text.setString("");
		m_text.setPosition(0, 0);
		m_text.setCharacterSize(12);
		
		m_clicked = false;
		m_blocked = false;
		
		engine.getemap()["increment"] = thor::Action(sf::Event::MouseButtonPressed);
		engine.getsystem().connect("increment", [&](context_t context){
			if (m_blocked) return;
			if (context.event->mouseButton.button == sf::Mouse::Left)
			{
				if (m_index.x > -1 && m_index.y > -1)
				{
					if (m_nodes[m_index.x][m_index.y].value < 3)
						m_nodes[m_index.x][m_index.y].value++;
					else
						m_nodes[m_index.x][m_index.y].value = 0;
				}
			}
			if (context.event->mouseButton.button == sf::Mouse::Right)
			{
				if (m_index.x > -1 && m_index.y > -1)
				{
					if (m_nodes[m_index.x][m_index.y].value > 0)
						m_nodes[m_index.x][m_index.y].value--;
					else
						m_nodes[m_index.x][m_index.y].value = 3;
				}
			}
		});
	
	}

	Board::Board() {}
	Board::~Board() {}

	void Board::update(float dt, bool blocked)
	{
		m_blocked = blocked;
		if (m_blocked) return;
		
		m_index.x = -1;
		m_index.y = -1;
		
		std::cout << m_mpos.x << ":" << m_mpos.y << "     " << m_position.x+5+0*30 << ":" << m_position.y+5+0*30 << "\r";
		
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				float x = m_position.x+5+i*30;
				float y = m_position.y+5+j*30;
				if (m_mpos.x > x && m_mpos.y > y && m_mpos.x < x+25 && m_mpos.y < y+25)
				{
					m_index.x = i;
					m_index.y = j;
				}
			}
		}
	}

	void Board::render(sf::RenderWindow& window)
	{
		m_mpos = sf::Mouse::getPosition(window);
		
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
				if (m_index.x == i && m_index.y == j)
					drawrectangle(sf::Color(155, 155, 155), m_position.x+5+i*30, m_position.y+5+j*30, 25, 25, false, window);
				else
				{
					switch (m_nodes[i][j].value)
					{
						case 0:
							drawrectangle(sf::Color(100, 100, 100), m_position.x+5+i*30, m_position.y+5+j*30, 25, 25, false, window);
							break;
						case 1:
							drawrectangle(sf::Color(155, 100, 100), m_position.x+5+i*30, m_position.y+5+j*30, 25, 25, false, window);
							break;
						case 2:
							drawrectangle(sf::Color(100, 155, 100), m_position.x+5+i*30, m_position.y+5+j*30, 25, 25, false, window);
							break;
						case 3:
							drawrectangle(sf::Color(100, 100, 155), m_position.x+5+i*30, m_position.y+5+j*30, 25, 25, false, window);
							break;
						default:
							break;
					}
				}
				
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
