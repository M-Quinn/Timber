#include <iostream>
#include<SFML/Graphics.hpp>
#include<sstream>
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
const int NUM_BRANCHES_ = 6;

Vector2<float> bee_position_ = { 2000,0 };


Clock clock_;
Time delta_time_;
Time game_time_total_;
float time_remaining_ = 6.0f;
float time_bar_width_per_second_;
RectangleShape time_bar_shape_;
float time_bar_start_width_ = 400;
float time_bar_height_ = 80;


Texture texture_background_;
Texture texture_tree_;
Texture texture_bee_;
Texture texture_cloud_;
Sprite sprite_clouds_[3];
Sprite sprite_background_;
Sprite sprite_tree_;
Sprite sprite_bee_;
Sprite brances_[NUM_BRANCHES_];

enum class Side
{
	LEFT, 
	RIGHT, 
	NONE
};

Side branchPositions[NUM_BRANCHES_];

bool bee_active_ = false;
bool acive_clouds_[3] = { false, false, false };
bool paused_ = true;

float bee_speed_ = 0.0f;
float speed_clouds[3] = { 0.0f,0.0f,0.0f };

int score_ = 0;
Text message_text_;
Text score_text_;
Font font_;

//Function Prototypes
int GetBeeSpeed();
int GetBeeHeight();
float GetCloudHeight(int i);
void UpdateBranches(int seed);



int main()
{
	//Create the window
	VideoMode vm(SCREEN_WIDTH_, SCREEN_HEIGHT_);
	RenderWindow window(vm, SCREEN_TITLE_, Style::Fullscreen);

	//handle time bar
	time_bar_shape_.setSize(Vector2f(
		time_bar_start_width_,
		time_bar_height_));
	time_bar_shape_.setFillColor(Color::Red);
	time_bar_shape_.setPosition((1920 / 2) - time_bar_start_width_ / 2, 980);
	time_bar_width_per_second_ = time_bar_start_width_ / time_remaining_;
	
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

	if (!font_.loadFromFile("fonts/KOMIKAP_.ttf")) 
	{
		std::cout << "Error: Could not find font";
	}

	message_text_.setFont(font_);
	score_text_.setFont(font_);

	message_text_.setCharacterSize(75);
	score_text_.setCharacterSize(100);

	message_text_.setFillColor(Color::White);
	score_text_.setFillColor(Color::White);

	message_text_.setString("Press Enter to start!");
	score_text_.setString("Score = 0");

	FloatRect textRect = message_text_.getLocalBounds();
	message_text_.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	message_text_.setPosition(1920 / 2.0f, 1080 / 2.0f);

	score_text_.setPosition(20, 20);





	while(window.isOpen())
	{

		delta_time_ = clock_.restart();

		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter)) 
		{
			paused_ = false;
			score_ = 0;
			time_remaining_ = 6.0f;
		}

		if (time_remaining_ <= 0.0f) 
		{
			paused_ = true;
			message_text_.setString("Out of time!");

			FloatRect textRect = message_text_.getLocalBounds();
			message_text_.setOrigin(
				textRect.left + textRect.width / 2.0f,
				textRect.top + textRect.height / 2.0f);

			message_text_.setPosition(1920 / 2.0f, 1080 / 2.0f);
		}

		if (!paused_) 
		{
			time_remaining_ -= delta_time_.asSeconds();
			time_bar_shape_.setSize(Vector2f(
				time_bar_width_per_second_ * time_remaining_,
				time_bar_height_));

			if (!bee_active_)
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
			else
			{
				auto cur_pos = sprite_bee_.getPosition();

				sprite_bee_.setPosition(
					cur_pos.x - bee_speed_ * delta_time_.asSeconds(),
					cur_pos.y);

				if (sprite_bee_.getPosition().x < -100)
				{
					bee_active_ = false;
				}
			}


			for (int i = 0; i < std::size(sprite_clouds_); i++)
			{
				if (!acive_clouds_[i])
				{
					srand((int)time(0) * ((i + 1) * 10));// multiply by 10,20,30...

					speed_clouds[i] = (rand() + 30) % 200;

					float height = GetCloudHeight(i);


					sprite_clouds_[i].setPosition(-200, height);

					acive_clouds_[i] = true;
				}
				else
				{
					auto cur_pos = sprite_clouds_[i].getPosition();

					sprite_clouds_[i].setPosition(
						cur_pos.x + speed_clouds[i] * delta_time_.asSeconds(),
						cur_pos.y);

					if (sprite_clouds_[i].getPosition().x > 1920)
					{
						acive_clouds_[i] = false;
					}
				}
			}

			//Update Score

			std::stringstream ss;
			ss << "Score = " << score_;
			score_text_.setString(ss.str());
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
		window.draw(time_bar_shape_);

		if (paused_)
			window.draw(message_text_);
		else
			window.draw(score_text_);

		//Display
		window.display();
	}
	return 0;
}




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

float GetCloudHeight(int i)
{
	float height;
	switch (i)
	{
	case 0:
		return height = rand() % 150;
	case 1:
		return height = (rand() % 300) - 150;
	case 2:
		return height = (rand() % 450) - 150;
	default:
		std::cout << "Error: cloud height given wrong position";
		return height = rand() % 150;
	}
}
