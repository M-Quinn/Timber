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
const String PATH_BRANCH_IMAGE_ = "graphics/branch.png";
const String PATH_PLAYER_IMAGE_ = "graphics/player.png";
const String PATH_RIP_IMAGE_ = "graphics/rip.png";
const String PATH_AXE_IMAGE_ = "graphics/axe.png";
const String PATH_LOG_IMAGE_ = "graphics/log.png";
const Vector2<float> TREE_POSITION_ = { 810,0 };
const Vector2<float> CLOUD1_POSITION_ = { 0,0 };
const Vector2<float> CLOUD2_POSITION_ = { 0,250 };
const Vector2<float> CLOUD3_POSITION_ = { 0,500 };
const Vector2f PLAYER_POSITION_LEFT_ = { 580, 720 };
const Vector2f PLAYER_POSITION_RIGHT_ = { 1200, 720 };
const Vector2f RIP_POSITION_ = { 600, 860 };
const Vector2f RIP_START_POSITION_ = { 675, 2000 };
const Vector2f AXE_START_POSITION = { 700, 830 };
const Vector2f LOG_POSITION = { 810, 720 };
const float AXE_POSITION_LEFT_ = 700;
const float AXE_POSITION_RIGHT_ = 1075;
const int NUM_BRANCHES_ = 6;

Vector2<float> bee_position_ = { 2000,0 };
Vector2f LOG_SPEED = { 1000, -1500 };


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
Texture texture_branch_;
Texture texture_player_;
Texture texture_rip_;
Texture texture_axe_;
Texture texture_log_;

Sprite sprite_clouds_[3];
Sprite sprite_background_;
Sprite sprite_tree_;
Sprite sprite_bee_;
Sprite branches_[NUM_BRANCHES_];
Sprite sprite_player_;
Sprite sprite_rip_;
Sprite sprite_axe_;
Sprite sprite_log_;

enum class Side
{
	LEFT, 
	RIGHT, 
	NONE
};

Side branch_positions_[NUM_BRANCHES_];
Side player_side_ = Side::LEFT;

bool bee_active_ = false;
bool acive_clouds_[3] = { false, false, false };
bool paused_ = true;
bool log_acive_ = false;
bool accept_input_ = false;

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
void HandleScoreIncrease();



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

	if (!texture_branch_.loadFromFile(PATH_BRANCH_IMAGE_)) 
	{
		std::cout << "Error: Could not find branch texture";
	}

	for (int i = 0; i < std::size(branches_); i++)
	{
		branches_[i].setTexture(texture_branch_);
		branches_[i].setPosition(-2000, -2000);
		branches_[i].setOrigin(220, 20);
	}

	if (!texture_player_.loadFromFile(PATH_PLAYER_IMAGE_)) 
	{
		std::cout << "Error: Could not find player texture";
	}
	else 
	{
		sprite_player_.setTexture(texture_player_);
		sprite_player_.setPosition(PLAYER_POSITION_LEFT_);
	}

	if (!texture_rip_.loadFromFile(PATH_RIP_IMAGE_))
	{
		std::cout << "Error: Could not find rip texture";
	}
	else
	{
		sprite_rip_.setTexture(texture_rip_);
		sprite_rip_.setPosition(RIP_POSITION_);
	}

	if (!texture_axe_.loadFromFile(PATH_AXE_IMAGE_))
	{
		std::cout << "Error: Could not find axe texture";
	}
	else
	{
		sprite_axe_.setTexture(texture_axe_);
		sprite_axe_.setPosition(AXE_START_POSITION);
	}

	if (!texture_log_.loadFromFile(PATH_LOG_IMAGE_))
	{
		std::cout << "Error: Could not find Log texture";
	}
	else
	{
		sprite_log_.setTexture(texture_log_);
		sprite_log_.setPosition(LOG_POSITION);
	}





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

		//Reads releases then allows key presses again
		Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == Event::KeyReleased && !paused_) 
			{
				accept_input_ = true;
				sprite_axe_.setPosition(2000, sprite_axe_.getPosition().y);
			}
		}

		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter)) 
		{
			paused_ = false;
			accept_input_ = true;
			score_ = 0;
			time_remaining_ = 6.0f;

			for (int i = 0; i < std::size(branches_); i++)
			{
				branch_positions_[i] = Side::NONE;
			}

			sprite_rip_.setPosition(RIP_START_POSITION_);
			sprite_player_.setPosition(PLAYER_POSITION_LEFT_);
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

		if (accept_input_) 
		{
			if (Keyboard::isKeyPressed(Keyboard::Right)) 
			{
				player_side_ = Side::RIGHT;

				HandleScoreIncrease();

				sprite_axe_.setPosition(
					AXE_POSITION_RIGHT_,
					sprite_axe_.getPosition().y
				);

				sprite_player_.setPosition(PLAYER_POSITION_RIGHT_);

				UpdateBranches(score_);

				sprite_log_.setPosition(810, 720);
				LOG_SPEED.x = -5000;
				log_acive_ = true;
				accept_input_ = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				player_side_ = Side::LEFT;

				HandleScoreIncrease();

				sprite_axe_.setPosition(
					AXE_POSITION_LEFT_,
					sprite_axe_.getPosition().y
				);

				sprite_player_.setPosition(PLAYER_POSITION_LEFT_);

				UpdateBranches(score_);

				sprite_log_.setPosition(810, 720);
				LOG_SPEED.x = 5000;
				log_acive_ = true;
				accept_input_ = false;
			}
		}

		if (!paused_) 
		{
			time_remaining_ -= delta_time_.asSeconds();
			time_bar_shape_.setSize(Vector2f(
				time_bar_width_per_second_ * time_remaining_,
				time_bar_height_));

			for (int i = 0; i < std::size(branches_); i++) {
				UpdateBranches(i + 1);
			}

			//Update Branches
			for (int i = 0; i < std::size(branches_); i++)
			{
				float height = i * 150;

				switch(branch_positions_[i]) {
				case Side::LEFT:
					branches_[i].setPosition(610, height);
					branches_[i].setRotation(180);
					break;
				case Side::RIGHT:
					branches_[i].setPosition(1330, height);
					branches_[i].setRotation(0);
					break;
				case Side::NONE:
					branches_[i].setPosition(3000, height);
					break;
				}
			}

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
		window.draw(sprite_player_);
		window.draw(sprite_log_);
		window.draw(sprite_axe_);
		window.draw(sprite_rip_);

		for (auto sprite_cloud : sprite_clouds_)
			window.draw(sprite_cloud);

		for (auto branch : branches_)
			window.draw(branch);

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

void UpdateBranches(int seed)
{
	for (int i = std::size(branches_); i > 0; i--)
	{
		branch_positions_[i] = branch_positions_[i - 1];
	}
	//Seed the random number
	srand((int)time(0) + seed);
	int r = rand() % 5;
	
	switch (r) 
	{
	case 0:
		branch_positions_[0] = Side::LEFT;
		break;
	case 1:
		branch_positions_[0] = Side::RIGHT;
		break;
	default:
		branch_positions_[0] = Side::NONE;
		break;
	}
}

void HandleScoreIncrease() 
{
	score_++;

	//Score should never be 0 but will check anyway
	if (score_ <= 0)
	{
		std::cout << "Error: score was 0 or below resulting in a division by 0";
		score_ = 1;
	}

	time_remaining_ += (2 / score_) + 0.15;
}
