#pragma once
#include "constants.h"
#include "texture.h"

class Paddle
{
public:
	static const int PADDLE_WIDTH = 10;
	static const int PADDLE_HEIGHT = 60;
	static const int PADDLE_VEL = 4;
	Paddle(int xPos, int yPos);
	void handleEvent(SDL_Event& e);
	void move();
	void render(LTexture& paddleTexture, SDL_Renderer*& renderer);
	SDL_Rect& getMCollider();
	int getMYVel();
	void setMYVel(int vel);
	int getMYPos();
private:
	int mXPos, mYPos;
	int mYVel;
	SDL_Rect mCollider;
};
