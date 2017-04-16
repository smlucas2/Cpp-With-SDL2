#include "opponent.h"

Opponent::Opponent(Paddle& paddle)
{
	mPaddle = &paddle;
}

void Opponent::move(Ball& ball)
{
	trackBall(ball);
	mPaddle->move();
}

void Opponent::trackBall(Ball& ball)
{
	if (ball.getYPos() + 5 > mPaddle->getMYPos() + 30) 
	{
		if (ball.getYVel() > 0)
		{
			if (ball.getYVel() < Paddle::PADDLE_VEL)
			{
				mPaddle->setMYVel(ball.getYVel());
			}
			else
			{
				mPaddle->setMYVel(Paddle::PADDLE_VEL);
			}
		}
		if (ball.getYVel() < 0)
		{
			if (ball.getYVel() > -Paddle::PADDLE_VEL)
			{
				mPaddle->setMYVel(-ball.getYVel());
			}
			else
			{
				mPaddle->setMYVel(Paddle::PADDLE_VEL);
			}
		}
	}
	else if (ball.getYPos() + 5 < mPaddle->getMYPos() + 30)
	{
		if (ball.getYVel() > 0)
		{
			if (ball.getYVel() < Paddle::PADDLE_VEL)
			{
				mPaddle->setMYVel(-ball.getYVel());
			}
			else
			{
				mPaddle->setMYVel(-Paddle::PADDLE_VEL);
			}
		}
		if (ball.getYVel() < 0)
		{
			if (ball.getYVel() > -Paddle::PADDLE_VEL)
			{
				mPaddle->setMYVel(ball.getYVel());
			}
			else
			{
				mPaddle->setMYVel(-Paddle::PADDLE_VEL);
			}
		}
	}
	else
	{
		mPaddle->setMYVel(0);
	}
}

void Opponent::render(LTexture& paddleTexture, SDL_Renderer*& renderer)
{
	mPaddle->render(paddleTexture, renderer);
}

Paddle* Opponent::getPaddle()
{
	return mPaddle;
}
