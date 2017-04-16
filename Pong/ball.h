#pragma once
#include "constants.h"
#include "texture.h"
#include "paddle.h"

int checkCollision(SDL_Rect& ball, SDL_Rect& paddle, int& YVel);

class Ball
{
public:
	static const int BALL_WIDTH = 10;
	static const int BALL_HEIGHT = 10;
	static const int BALL_X_VELOCITY = 8;
	static const int BALL_Y_VELOCITY = 5;
	Ball(int xPos, int yPos);
	void move(SDL_Rect& paddleTop, SDL_Rect& opponentPaddleCollider, int& pointsR, int& pointsL, Mix_Chunk*& paddleHit, Mix_Chunk*& wallHit);
	void render(LTexture& ballTexture, SDL_Renderer*& renderer);
	SDL_Rect& getMCollider();
	int getYVel();
	int getYPos();
private:
	int mXPos, mYPos;
	int mXVel, mYVel;
	SDL_Rect mCollider;
};
