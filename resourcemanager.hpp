#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <locale>
#include <algorithm>
#include <string>
#include <SFML/Graphics.hpp>
#include <boost/any.hpp>
#include <boost/tokenizer.hpp>

namespace lum {
	enum file_t {
		TEXTURE,
		FONT,
		SOUND,
		UNKNOWN
	};
	
	class ResourceManager {
	private:
		std::map<std::string, boost::any> m_res;
		file_t getFileExtension(std::string);
		
	public:
		ResourceManager();
		~ResourceManager();
		
		void loadResource(std::string, std::string);
		boost::any getResource(std::string);
		
	};
}
