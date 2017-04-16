#include "ball.h"
#include "paddle.h"


Ball::Ball(int xPos, int yPos)
{
	mXPos = xPos;
	mYPos = yPos;

	mXVel = -BALL_X_VELOCITY;
	mYVel = BALL_Y_VELOCITY;

	mCollider.w = BALL_WIDTH;
	mCollider.h = BALL_HEIGHT;
}

void Ball::move(SDL_Rect& paddleCollider, SDL_Rect& opponentPaddleCollider, int& pointsR, int& pointsL, Mix_Chunk*& paddleHit, Mix_Chunk*& wallHit)
{
	int collisionType = 0;
	if (mXPos <= SCREEN_WIDTH / 2)
	{
		collisionType = checkCollision(mCollider, paddleCollider, mYVel);
	}
	else
	{
		collisionType = checkCollision(mCollider, opponentPaddleCollider, mYVel);
	}

	if (collisionType == 1)
	{
		if (mYVel > 0)
		{
			mYVel += 1;
		}
		if (mYVel < 0)
		{
			mYVel -= 1;
		}
		mXVel *= -1;

		Mix_PlayChannel(-1, paddleHit, 0);
	}
	else if (collisionType == 2)
	{
		mXVel *= -1;
		mYVel *= -1;

		Mix_PlayChannel(-1, paddleHit, 0);
	}

	if (mXPos + BALL_WIDTH > SCREEN_WIDTH)
	{
		mXPos = SCREEN_WIDTH / 2;
		mYPos = (SCREEN_HEIGHT / 2) - (BALL_HEIGHT / 2);

		mYVel = BALL_Y_VELOCITY;

		pointsL++;
	}
	if (mXPos < 0)
	{
		mXPos = SCREEN_WIDTH / 2;
		mYPos = (SCREEN_HEIGHT / 2) - (BALL_HEIGHT / 2);

		mYVel = -BALL_Y_VELOCITY;

		pointsR++;
	}
	if (mYPos < 0 || mYPos + BALL_HEIGHT > SCREEN_HEIGHT)
	{
		mYVel *= -1;
		Mix_PlayChannel(-1, wallHit, 0);
	}

	mXPos += mXVel;
	mCollider.x = mXPos;
	mYPos += mYVel;
	mCollider.y = mYPos;
}

void Ball::render(LTexture& ballTexture, SDL_Renderer*& renderer)
{
	ballTexture.render(mXPos, mYPos, renderer);
}

SDL_Rect& Ball::getMCollider()
{
	return mCollider;
}

int Ball::getYVel()
{
	return mYVel;
}

int Ball::getYPos()
{
	return mYPos;
}
