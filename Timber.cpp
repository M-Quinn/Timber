#include <iostream>
#include<SFML/Graphics.hpp>
using namespace sf;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const String SCREEN_TITLE = "Timber!";
const String PATH_BACKGROUND_IMAGE = "graphics/background.png";

int main()
{
	//Create the window
	VideoMode vm(SCREEN_WIDTH, SCREEN_HEIGHT);
	RenderWindow window(vm, SCREEN_TITLE, Style::Fullscreen);

	Texture textureBackground;
	Sprite spriteBackground;

	if(!textureBackground.loadFromFile(PATH_BACKGROUND_IMAGE))
	{
		std::cout << "Error: Could not find Background texture";
	}
	spriteBackground.setTexture(textureBackground);

	spriteBackground.setPosition(0, 0);

	while(window.isOpen())
	{

		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

	//Double Buffering

		//clear the display
		window.clear();

		//Draw everything
		window.draw(spriteBackground);

		//Display
		window.display();
	}
	return 0;
}