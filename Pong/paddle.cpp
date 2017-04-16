#include "paddle.h"

Paddle::Paddle(int xPos, int yPos)
{
	mXPos = xPos;
	mYPos = yPos;

	mYVel = 0;;

	mCollider.x = mXPos;
	mCollider.y = mYPos;
	mCollider.w = PADDLE_WIDTH;
	mCollider.h = PADDLE_HEIGHT;
}

void Paddle::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			mYVel -= PADDLE_VEL;
			break;
		case SDLK_DOWN:
			mYVel += PADDLE_VEL;
			break;
		}
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			mYVel += PADDLE_VEL;
			break;
		case SDLK_DOWN:
			mYVel -= PADDLE_VEL;
			break;
		}
	}
}

void Paddle::move()
{
	mYPos += mYVel;
	mCollider.y = mYPos;

	if (mYPos < 0 || mYPos + PADDLE_HEIGHT > SCREEN_HEIGHT)
	{
		mYPos -= mYVel;
		mCollider.y = mYPos;
	}
}

void Paddle::render(LTexture& paddleTexture, SDL_Renderer*& renderer)
{
	paddleTexture.render(mXPos, mYPos, renderer);
}

SDL_Rect& Paddle::getMCollider()
{
	return mCollider;
}

int Paddle::getMYVel() 
{
	return mYVel;
}

void Paddle::setMYVel(int vel)
{
	mYVel = vel;
}

int Paddle::getMYPos()
{
	return mYPos;
}
