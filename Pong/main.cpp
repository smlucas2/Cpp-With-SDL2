#include "constants.h"
#include "texture.h"
#include "ball.h"
#include "paddle.h"
#include "opponent.h"

bool init(SDL_Window** window, SDL_Renderer** renderer);
bool loadTextures(LTexture& scoreR, LTexture& scoreL, LTexture& paddle, LTexture& ball, LTexture& backgroundTexture, SDL_Renderer*& renderer);
bool loadSounds(Mix_Chunk** paddleHit, Mix_Chunk** wallHit, SDL_Renderer*& renderer);
int checkCollision(SDL_Rect& ball, SDL_Rect& paddle, int& YVel);
void close(SDL_Window** window, SDL_Renderer** renderer);

int main(int args, char* argc[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if (!init(&window, &renderer))
	{
		SDL_Log("Failed to initialized.\n");
	}
	else
	{
		LTexture paddleTexture;
		LTexture ballTexture;
		LTexture backgroundTexture;
		LTexture scoreTextureR;
		LTexture scoreTextureL;

		Mix_Chunk* paddleHit = NULL;
		Mix_Chunk* wallHit = NULL;

		if (!loadTextures(scoreTextureR, scoreTextureL, paddleTexture, ballTexture, backgroundTexture, renderer)
			|| !loadSounds(&paddleHit, &wallHit, renderer) )
		{
			SDL_Log("Failed to load media.\n");
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			Ball ball(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - (Ball::BALL_HEIGHT / 2));

			Paddle paddle( (Paddle::PADDLE_WIDTH * 2), (SCREEN_HEIGHT / 2) - (Paddle::PADDLE_HEIGHT / 2) );
			Paddle opponentPaddle( (SCREEN_WIDTH - (Paddle::PADDLE_WIDTH * 3) ), (SCREEN_HEIGHT / 2) - (Paddle::PADDLE_HEIGHT / 2) );

			Opponent opponent(opponentPaddle);

			SDL_Color textColor = {0xFF, 0xFF, 0xFF};

			std::stringstream scoreL;
			std::stringstream scoreR;

			int pointsL = 0;
			int pointsR = 0;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					paddle.handleEvent(e);
				}

				scoreR.str("");
				scoreR << pointsR;
				if (!scoreTextureR.loadFromRenderedText(scoreR.str().c_str(), textColor, renderer))
				{
					SDL_Log("Could not render font! SDL_ttf Error: %s\n", TTF_GetError());
				}

				scoreL.str("");
				scoreL << pointsL;
				if (!scoreTextureL.loadFromRenderedText(scoreL.str().c_str(), textColor, renderer))
				{
					SDL_Log("Could not render font! SDL_ttf Error: %s\n", TTF_GetError());
				}

				paddle.move();
				opponent.move(ball);
				ball.move(paddle.getMCollider(), opponent.getPaddle()->getMCollider(), pointsR, pointsL, paddleHit, wallHit);

				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(renderer);

				backgroundTexture.render(0, 0, renderer);

				ball.render(ballTexture, renderer);
				paddle.render(paddleTexture, renderer);
				opponent.render(paddleTexture, renderer);

				scoreTextureR.render((SCREEN_WIDTH / 2) - scoreTextureR.getWidth() / 2 + 60, scoreTextureR.getHeight() - 20, renderer);
				scoreTextureL.render((SCREEN_WIDTH / 2) - scoreTextureL.getWidth() / 2 - 60, scoreTextureL.getHeight() - 20, renderer);

				SDL_RenderPresent(renderer);
			}
		}
		paddleTexture.free();
		ballTexture.free();
		backgroundTexture.free();
		scoreTextureL.free();
		scoreTextureR.free();

		Mix_FreeChunk(paddleHit);
		paddleHit = NULL;
		Mix_FreeChunk(wallHit);
		wallHit = NULL;
	}

	close(&window, &renderer);

	return 0;
}

bool init(SDL_Window** window, SDL_Renderer** renderer)
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		success = false;
	}
	else
	{
		*window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (*window == NULL)
		{
			SDL_Log("Could not make window! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (*renderer == NULL)
			{
				SDL_Log("Could not make renderer! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					SDL_Log("SDL_ttf could not initialize! SDL_tff Error: %s\n", TTF_GetError());
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					SDL_Log("SDL_mixer could not initialize! SDL_image Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}


bool loadTextures(LTexture& scoreR, LTexture& scoreL, LTexture& paddleTexture, LTexture& ballTexture, LTexture& backgroundTexture, SDL_Renderer*& renderer)
{
	bool success = true;

	if (!scoreR.setFont("C:/Users/sean/Desktop/Cpp Coding/Pong/Pong/Sans.ttf", 56))
	{
		SDL_Log("Could not load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	if (!scoreL.setFont("C:/Users/sean/Desktop/Cpp Coding/Pong/Pong/Sans.ttf", 56))
	{
		SDL_Log("Could not load font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	if (!backgroundTexture.loadFromFile("C:/Users/sean/Desktop/Cpp Coding/Pong/Pong/background.png", renderer))
	{
		SDL_Log("Could not load texture! SDL_image Error: %s\n", IMG_GetError());
		success = false;
	}
	if (!paddleTexture.loadFromFile("C:/Users/sean/Desktop/Cpp Coding/Pong/Pong/paddle.png", renderer))
	{
		SDL_Log("Could not load texture! SDL_image Error: %s\n", IMG_GetError());
		success = false;
	}
	if (!ballTexture.loadFromFile("C:/Users/sean/Desktop/Cpp Coding/Pong/Pong/ball.png", renderer))
	{
		SDL_Log("Could not load texture! SDL_image Error: %s\n", IMG_GetError());
		success = false;
	}

	return success;
}

bool loadSounds(Mix_Chunk** paddleHit, Mix_Chunk** wallHit, SDL_Renderer*& renderer)
{
	bool success = true;

	*paddleHit = Mix_LoadWAV("C:/Users/sean/Desktop/Cpp Coding/Pong/Pong/hitPaddle.wav");
	if (paddleHit == NULL)
	{
		SDL_Log("Could not load sound! SDL_image Error: %s\n", Mix_GetError());
		success = false;
	}
	*wallHit = Mix_LoadWAV("C:/Users/sean/Desktop/Cpp Coding/Pong/Pong/hitWall.wav");
	if (wallHit == NULL)
	{
		SDL_Log("Could not load sound! SDL_image Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

int checkCollision(SDL_Rect& ball, SDL_Rect& paddle, int& yVel)
{
	int ballBottom = ball.y + ball.h;
	int ballTop = ball.y;
	int ballLeft = ball.x;
	int ballRight = ball.x + ball.w;

	int paddleBottom = paddle.y + paddle.h;
	int paddleTop = paddle.y;
	int paddleLeft = paddle.x;
	int paddleRight = paddle.x + paddle.w;

	bool side = false;
	bool top = false;
	bool bottom = false;

	if ( (ballLeft < paddleRight && ballLeft > paddleLeft && ballTop > paddleTop - ball.h && ballBottom < paddleBottom + ball.h)
		|| (ballRight > paddleLeft && ballRight < paddleRight && ballTop > paddleTop - ball.h && ballBottom < paddleBottom + ball.h) )
	{
		side = true;
	}
	if (yVel > 0 && ballBottom > paddleTop && ballBottom < paddleTop + 10 && 
		( (ballRight > paddleLeft && ballRight < paddleRight) || (ballLeft < paddleRight && ballLeft > paddleLeft) ) )
	{
		top = true;
	}
	if (yVel < 0 && ballTop < paddleBottom && ballTop > paddleBottom - 10 &&
		((ballRight > paddleLeft && ballRight < paddleRight) || (ballLeft < paddleRight && ballLeft > paddleLeft)))
	{
		bottom = true;
	}

	if (top || bottom) {
		return 2;
	}
	else if (side)
	{
		return 1;
	}
	else {
		return 0;
	}
}

void close(SDL_Window** window, SDL_Renderer** renderer)
{
	SDL_DestroyRenderer(*renderer);
	SDL_DestroyWindow(*window);
	window = NULL;
	renderer = NULL;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
