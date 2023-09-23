#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

//THIS IS WRITTEN USING OLC GPE, CHECK OUT onelonecoder.com
//Or else
class Snake : public olc::PixelGameEngine {
public:
	Snake() {
		sAppName = "Snake";
	}

	enum direction { STOP, LEFT, RIGHT, DOWN, UP };
	direction dir;
	//Game variables
	int score;
	//Snake variables
	float SnakeXPos, SnakeYPos;
	float tailUpdateTimer = 0;
	int tailX[1000], tailY[1000], tailLength = 0;
	float x, y;
	//Target variables
	int fruit1X, fruit1Y, fruit2X, fruit2Y;
	bool fruit1 = false, fruit2 = false;
	bool GameOver;

	void SnakeDead(int score) {
		if (GameOver == true) {
			std::string scoreString = std::to_string(score);
			Clear(olc::BLACK);
			DrawString(ScreenWidth() - ((ScreenWidth() / 2) + (ScreenWidth() / 2.8)), ScreenHeight() - 90, "Game Over", olc::RED, 1);
			DrawString(ScreenWidth() / 2 - 20, ScreenHeight() - 70, "Score:", olc::GREEN, 1);
			DrawString(ScreenWidth() / 2, ScreenHeight() - 60, scoreString, olc::GREEN, 1);
			DrawString(ScreenWidth() - 100, ScreenHeight() - 40, "Press 'SPACE'", olc::BLUE, 1);
			DrawString(ScreenWidth() / 2 - 30, ScreenHeight() - 30, "To Retry", olc::BLUE, 1);
			dir = STOP;
		}
	}
	void DeadSnakeInput() {
		if (GetKey(olc::Key::UP).bPressed && dir != DOWN) {
			dir = STOP;
		}
		if (GetKey(olc::Key::DOWN).bPressed && dir != UP) {
			dir = STOP;
		}
		if (GetKey(olc::Key::LEFT).bPressed && dir != RIGHT) {
			dir = STOP;
		}
		if (GetKey(olc::Key::RIGHT).bPressed && dir != LEFT) {
			dir = STOP;
		}
		if (GetKey(olc::Key::SPACE).bPressed) {
			GameOver = false;
			tailLength = 0;
			score = 0;
			srand(time(NULL));
			dir = STOP;
			//Snake X coord gen
			SnakeXPos = rand() & ScreenWidth();
			if (SnakeXPos <= 3 || SnakeXPos >= ScreenWidth() - 3) {
				SnakeXPos = rand() & ScreenWidth();
			}
			if (SnakeXPos <= 3 || SnakeXPos >= ScreenHeight() - 3) {
				SnakeXPos = rand() & ScreenHeight();
			}
			//Snake Y coord gen
			SnakeYPos = rand() & ScreenWidth();
			if (SnakeYPos <= 3 || SnakeYPos >= ScreenWidth() - 3) {
				SnakeYPos = rand() & ScreenWidth();
			}
			if (SnakeYPos <= 3 || SnakeYPos >= ScreenHeight() - 3) {
				SnakeYPos = rand() & ScreenHeight();
			}
		}
	}
	void BorderCollisionCheck() {
		if (SnakeXPos <= 3) {
			GameOver = true;
		}
		if (SnakeXPos >= ScreenWidth() - 3) {
			GameOver = true;
		}
		if (SnakeYPos <= 3) {
			GameOver = true;
		}
		if (SnakeYPos >= ScreenHeight() - 3) {
			GameOver = true;
		}
	}
	void userInput(float speed) {
		if (GetKey(olc::Key::UP).bPressed && dir != DOWN) {
			dir = UP;
		}
		if (GetKey(olc::Key::DOWN).bPressed && dir != UP) {
			dir = DOWN;
		}
		if (GetKey(olc::Key::LEFT).bPressed && dir != RIGHT) {
			dir = LEFT;
		}
		if (GetKey(olc::Key::RIGHT).bPressed && dir != LEFT) {
			dir = RIGHT;
		}

		//Move Snake
		switch (dir) {
		case LEFT:
			SnakeXPos -= speed;
			break;
		case RIGHT:
			SnakeXPos += speed;
			break;
		case DOWN:
			SnakeYPos += speed;
			break;
		case UP:
			SnakeYPos -= speed;
			break;
		}
	}
	void FruitCoordGen() {
		//Fruit1
		if (fruit1 == false) {
			fruit1X = rand() & ScreenWidth();
			fruit1Y = rand() & ScreenHeight();
			fruit1 = true;
		}
		if (fruit1X <= 2 || fruit1X >= ScreenWidth() - 2) {
			fruit1X = rand() & ScreenWidth();
		}
		if (fruit1Y <= 2 || fruit1Y >= ScreenHeight() - 2) {
			fruit1Y = rand() & ScreenHeight();
		}
		//Fruit2
		//if (fruit2 == false) {
			//fruit2X = rand() & ScreenWidth();
			//fruit2Y = rand() & ScreenHeight();
			//fruit2 = true;
		//}
		//if (fruit2X <= 2 || fruit2X >= ScreenWidth() - 2) {
			//fruit1X = rand() & ScreenWidth();
		//}
		//if (fruit2Y <= 2 || fruit2Y >= ScreenHeight() - 2) {
			//fruit1Y = rand() & ScreenHeight();
		//}
		//if (fruit1X == fruit2X) {
			//fruit1X = rand() & ScreenWidth();
		//}
		//if (fruit1Y == fruit2Y) {
			//fruit1Y = rand() & ScreenWidth();
		//}
	}

private:

public:
	bool OnUserUpdate(float fElapsedTime) override {
		if (GameOver == false) {
			float speed = 20 * fElapsedTime;
			Clear(olc::BLACK);
			//Draw top border
			DrawLine(2, 2, ScreenWidth() - 2, 2, olc::WHITE);
			//Draw left border
			DrawLine(2, 2, 2, ScreenHeight() - 2, olc::WHITE);
			//Draw right border
			DrawLine(ScreenWidth() - 2, 2, ScreenWidth() - 2, ScreenHeight() - 2, olc::WHITE);
			//Draw bottom border
			DrawLine(2, ScreenHeight() - 2, ScreenWidth() - 2, ScreenHeight() - 2, olc::WHITE);

			olc::vi2d SnakeHead(SnakeXPos, SnakeYPos);
			olc::vi2d SnakeHeadSize(2, 2);

			olc::vi2d Fruit(fruit1X, fruit1Y);
			olc::vu2d FruitSize(2, 2);

			//Snake and fruit collision
			if (SnakeHead.x < Fruit.x + FruitSize.x &&
				SnakeHead.x + SnakeHeadSize.x > Fruit.x &&
				SnakeHead.y < Fruit.y + FruitSize.y &&
				SnakeHead.y + SnakeHeadSize.y > Fruit.y) {
				fruit1 = false;
				score++;
				tailLength++;
			}

			//Draw fruit
			DrawRect(fruit1X, fruit1Y, 1, 1, olc::RED);

			//Fruit coord gen
			FruitCoordGen();

			//Border collision
			BorderCollisionCheck();

			tailUpdateTimer -= fElapsedTime; //Decrement the tail timer by the game elapsed time.
			if (tailUpdateTimer <= 0) {
				//In order to create a tail following trail, start from the back-most tail and work your way up to the front, setting the previous tail's position to the current tail index's position.
				for (int i = tailLength - 1; i > 0; i--) {
					tailX[i] = tailX[i - 1];
					tailY[i] = tailY[i - 1];
				}
				//Now set the front-most tail to the current snake head's position.
				tailX[0] = SnakeXPos;
				tailY[0] = SnakeYPos;
				tailUpdateTimer = 0.05; //Every 0.05 seconds we will re-update the tail positions instead of doing it by frame-based timing.
			}

			//Draw Snake tail
			if (tailLength >= 1) {
				for (int i = 0; i < tailLength; i++) {
					DrawRect(tailX[i], tailY[i], 1, 1, olc::GREEN);
				}
			}

			//Snake position gets adjusted here.
			userInput(speed);

			//Draw the Snake at its new position.
			DrawRect(SnakeXPos, SnakeYPos, 1, 1, olc::DARK_GREEN);

			return true;
		}
		else if (GameOver == true) {
			SnakeDead(score);
			DeadSnakeInput();
			return true;
		}
	}

	bool OnUserCreate() override {
		srand(time(NULL));
		dir = STOP;
		//Snake X coord gen
		SnakeXPos = rand() & ScreenWidth();
		if (SnakeXPos <= 3 || SnakeXPos >= ScreenWidth() - 3) {
			SnakeXPos = rand() & ScreenWidth();
		}
		if (SnakeXPos <= 3 || SnakeXPos >= ScreenHeight() - 3) {
			SnakeXPos = rand() & ScreenHeight();
		}
		//Snake Y coord gen
		SnakeYPos = rand() & ScreenWidth();
		if (SnakeYPos <= 3 || SnakeYPos >= ScreenWidth() - 3) {
			SnakeYPos = rand() & ScreenWidth();
		}
		if (SnakeYPos <= 3 || SnakeYPos >= ScreenHeight() - 3) {
			SnakeYPos = rand() & ScreenHeight();
		}
		return true;
	}
};

int main() {
	Snake demo;
	if (demo.Construct(100, 100, 10, 10))
		demo.Start();
	return 0;
}