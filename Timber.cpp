#include<SFML/Graphics.hpp>
using namespace sf;

int main()
{
	VideoMode vm(1920, 1080);

	RenderWindow window(vm, "Timber!", Style::Fullscreen);

	while(window.isOpen())
	{

		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
	}
	return 0;
}