#include <iostream>
#include<SFML/Graphics.hpp>
using namespace sf;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const String SCREEN_TITLE = "Timber!";
const String PATH_BACKGROUND_IMAGE = "graphics/background.png";
const String PATH_TREE_IMAGE = "graphics/tree.png";
const String PATH_BEE_IMAGE = "graphics/bee.png";
const String PATH_CLOUD_IMAGE = "graphics/cloud.png";
const Vector2<float> TREE_POSITION = { 810,0 };
const Vector2<float> BEE_POSITION = { 0,800 };
const Vector2<float> CLOUD1_POSITION = { 0,0 };
const Vector2<float> CLOUD2_POSITION = { 0,250 };
const Vector2<float> CLOUD3_POSITION = { 0,500 };

int main()
{
	//Create the window
	VideoMode vm(SCREEN_WIDTH, SCREEN_HEIGHT);
	RenderWindow window(vm, SCREEN_TITLE, Style::Fullscreen);

	Texture textureBackground;
	Texture textureTree;
	Texture textureBee;
	Texture textureCloud;
	Sprite spriteClouds[3];
	Sprite spriteBackground;
	Sprite spriteTree;
	Sprite spriteBee;

	bool beeActive = false;
	bool cloud1Active, cloud2Active, cloud3Active;
	cloud1Active = cloud2Active = cloud3Active = false;

	float beeSpeed = 0.0f;
	float cloud1Speed, cloud2Speed, cloud3Speed;
	cloud1Speed = cloud2Speed = cloud3Speed = 0.0f;

	if(!textureBackground.loadFromFile(PATH_BACKGROUND_IMAGE))
	{
		std::cout << "Error: Could not find Background texture";
	}
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	if (!textureTree.loadFromFile(PATH_TREE_IMAGE))
	{
		std::cout << "Error: Could not find Tree texture";
	}
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(TREE_POSITION);

	if(!textureBee.loadFromFile(PATH_BEE_IMAGE))
	{
		std::cout << "Error: Could not find bee texture";
	}
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(BEE_POSITION);

	if(!textureCloud.loadFromFile(PATH_CLOUD_IMAGE))
	{
		std::cout << "Error: Could not find cloud texture";
	}
	spriteClouds[0].setTexture(textureCloud);
	spriteClouds[0].setPosition(CLOUD1_POSITION);
	spriteClouds[1].setTexture(textureCloud);
	spriteClouds[1].setPosition(CLOUD2_POSITION);
	spriteClouds[2].setTexture(textureCloud);
	spriteClouds[2].setPosition(CLOUD3_POSITION);

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
		window.draw(spriteTree);
		window.draw(spriteBee);
		for (auto sprite_cloud : spriteClouds)
		{
			window.draw(sprite_cloud);
		}

		//Display
		window.display();
	}
	return 0;
}