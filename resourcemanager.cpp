#include "resourcemanager.hpp"

namespace lum {
	ResourceManager::ResourceManager() {}
	ResourceManager::~ResourceManager() {}
	
	void ResourceManager::loadResource(std::string id, std::string path)
	{
		if (m_res.find(id) != m_res.end())
			std::cout << "Resource with ID \"" << id << "\" exists, Aborting." << std::endl;
		
		// get file type
		file_t type = getFileExtension(path);
		
		// load file
		sf::Texture t;
		sf::Font f;
		switch (type)
		{
			case TEXTURE:
				std::cout << "TEXTURE FILE" << std::endl;
				t.loadFromFile(path);
				m_res[id] = f;
				break;
				
			case FONT:
				std::cout << "FONT FILE" << std::endl;
				f.loadFromFile(path);
				m_res[id] = t;
				break;
				
			case SOUND: // TODO
				std::cout << "SOUND FILE" << std::endl;
				break;
				
			case UNKNOWN:
				std::cout << "FILE NOT RECOGNIZED" << std::endl;
				break;
				
			default:
				break;
		}
	}
	
	boost::any ResourceManager::getResource(std::string id)
	{
		if (m_res.find(id) != m_res.end())
			return m_res[id];
		return nullptr;
	}
	
  file_t ResourceManager::getFileExtension(std::string file)
	{
		std::transform(file.begin(), file.end(), file.begin(), ::tolower);
		
		boost::char_separator<char> sep(".");
		boost::tokenizer<boost::char_separator<char>> tokens(file, sep);
		
		std::vector<std::string> strs;
		
		for (const auto& t: tokens)
			strs.emplace_back(t);
		
		std::string t=strs[1];
		if (strcmp(t.c_str(), "png")       == 0) return TEXTURE;
		else if (strcmp(t.c_str(), "jpg")  == 0) return TEXTURE;
		else if (strcmp(t.c_str(), "jpeg") == 0) return TEXTURE;
		else if (strcmp(t.c_str(), "mp3")  == 0) return SOUND;
		else if (strcmp(t.c_str(), "ogg")  == 0) return SOUND;
		else if (strcmp(t.c_str(), "ttf")  == 0) return FONT;
		else if (strcmp(t.c_str(), "otf")  == 0) return FONT;
		else return UNKNOWN;
		
	}
	
}
