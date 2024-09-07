#include <iostream>
#include<SFML/Graphics.hpp>
using namespace sf;

const int SCREEN_WIDTH_ = 1920;
const int SCREEN_HEIGHT_ = 1080;
const String SCREEN_TITLE_ = "Timber!";
const String PATH_BACKGROUND_IMAGE_ = "graphics/background.png";
const String PATH_TREE_IMAGE_ = "graphics/tree.png";
const String PATH_BEE_IMAGE_ = "graphics/bee.png";
const String PATH_CLOUD_IMAGE_ = "graphics/cloud.png";
const Vector2<float> TREE_POSITION_ = { 810,0 };
const Vector2<float> CLOUD1_POSITION_ = { 0,0 };
const Vector2<float> CLOUD2_POSITION_ = { 0,250 };
const Vector2<float> CLOUD3_POSITION_ = { 0,500 };

Vector2<float> bee_position_ = { 2000,0 };


Clock clock_;
Time delta_time_;

Texture texture_background_;
Texture texture_tree_;
Texture texture_bee_;
Texture texture_cloud_;
Sprite sprite_clouds_[3];
Sprite sprite_background_;
Sprite sprite_tree_;
Sprite sprite_bee_;

bool bee_active_ = false;
bool cloud_1_active_, cloud_2_active_, cloud_3_active_;

float bee_speed_ = 0.0f;
float cloud_1_speed_, cloud_2_speed_, cloud_3_speed_;

///returns a random number between 0-199 then adds 200 for an end result of 200-399
int GetBeeSpeed()
{
	return rand() % 200 + 200;
}

///returns 0-499 then adds 500 for end result 500-999;
int GetBeeHeight()
{
	return rand() % 500 + 500;
}

int main()
{
	//Create the window
	VideoMode vm(SCREEN_WIDTH_, SCREEN_HEIGHT_);
	RenderWindow window(vm, SCREEN_TITLE_, Style::Fullscreen);

	
	cloud_1_active_ = cloud_2_active_ = cloud_3_active_ = false;
	cloud_1_speed_ = cloud_2_speed_ = cloud_3_speed_ = 0.0f;

	
	if(!texture_background_.loadFromFile(PATH_BACKGROUND_IMAGE_))
	{
		std::cout << "Error: Could not find Background texture";
	}
	sprite_background_.setTexture(texture_background_);
	sprite_background_.setPosition(0, 0);

	if (!texture_tree_.loadFromFile(PATH_TREE_IMAGE_))
	{
		std::cout << "Error: Could not find Tree texture";
	}
	sprite_tree_.setTexture(texture_tree_);
	sprite_tree_.setPosition(TREE_POSITION_);

	if(!texture_bee_.loadFromFile(PATH_BEE_IMAGE_))
	{
		std::cout << "Error: Could not find bee texture";
	}
	sprite_bee_.setTexture(texture_bee_);

	if(!texture_cloud_.loadFromFile(PATH_CLOUD_IMAGE_))
	{
		std::cout << "Error: Could not find cloud texture";
	}
	sprite_clouds_[0].setTexture(texture_cloud_);
	sprite_clouds_[0].setPosition(CLOUD1_POSITION_);
	sprite_clouds_[1].setTexture(texture_cloud_);
	sprite_clouds_[1].setPosition(CLOUD2_POSITION_);
	sprite_clouds_[2].setTexture(texture_cloud_);
	sprite_clouds_[2].setPosition(CLOUD3_POSITION_);

	while(window.isOpen())
	{

		delta_time_ = clock_.restart();

		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//Init Bee
		if(!bee_active_)
		{
			//Seed the random number
			srand((int)time(0));

			bee_speed_ = GetBeeSpeed(); 

			//Seed again
			srand((int)time(0) * 10);

			float height = GetBeeHeight();

			bee_position_.y = height;

			sprite_bee_.setPosition(bee_position_);
			bee_active_ = true;
		}



	//Double Buffering

		//clear the display
		window.clear();

		//Draw everything
		window.draw(sprite_background_);
		window.draw(sprite_tree_);
		window.draw(sprite_bee_);
		for (auto sprite_cloud : sprite_clouds_)
		{
			window.draw(sprite_cloud);
		}

		//Display
		window.display();
	}
	return 0;
}
