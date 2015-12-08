#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <locale>
#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>
#include <boost/any.hpp>
#include <boost/variant.hpp>
#include <boost/tokenizer.hpp>

namespace lum {
	
	typedef boost::variant<sf::Font&, sf::Texture&, std::nullptr_t> resource_t;
	
	enum file_t {
		TEXTURE,
		FONT,
		SOUND,
		UNKNOWN
	};
	
	struct ref_t {
		int index;
		file_t type;
		ref_t() {}
		ref_t(int i, file_t t) {
			index = i;
			type=t;
		}
	};
	
	class ResourceManager {
	private:
		std::map<std::string, ref_t> m_ref;
		std::vector<sf::Font> m_fonts;
		std::vector<sf::Texture> m_textures;
		file_t getFileExtension(std::string);
		
	public:
		ResourceManager();
		~ResourceManager();
		
		void loadResource(std::string, std::string);
		resource_t getResource(std::string);
		
	};
}
