#include "texture.h"

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer*& renderer)
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		SDL_Log("Could not create surface! SDL_image Error: %s\n", SDL_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL)
		{
			SDL_Log("Could not make texture! SDL_image Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color& textColor, SDL_Renderer*& renderer)
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL)
		{
			
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}

	return mTexture != NULL;
}

void LTexture::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render(int x, int y, SDL_Renderer*& renderer, SDL_Rect* clip)
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if (clip != NULL)
	{
		renderQuad.h = clip->h;
		renderQuad.w = clip->w;
	}

	SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool LTexture::setFont(const char* path, int size)
{
	mFont = TTF_OpenFont(path, size);

	if (mFont == NULL)
	{
		return false;
	}

	return true;
}
