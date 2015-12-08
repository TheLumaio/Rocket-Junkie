#include <iostream>
#include "engine.hpp"
#include "menustate.hpp"

using namespace std;

int main(void)
{
	std::cout << "Test" << std::endl;
	
	lum::Engine engine;
	engine.changeState(new lum::MenuState(engine));
	engine.start();
	
	return 0;
}
