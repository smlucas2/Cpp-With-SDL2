#pragma once
#include "constants.h"
#include "ball.h"
#include "paddle.h"

class Opponent
{
public:
	Opponent(Paddle& paddle);
	void move(Ball& ball);
	void render(LTexture& paddleTexture, SDL_Renderer*& renderer);
	void trackBall(Ball& ball);
	Paddle* getPaddle();
private:
	Paddle* mPaddle;
};
