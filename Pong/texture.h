#pragma once
#include "constants.h"

class LTexture
{
public:
	LTexture();
	~LTexture();
	bool loadFromFile(std::string path, SDL_Renderer*& renderer);
	bool loadFromRenderedText(std::string textureText, SDL_Color& textColor, SDL_Renderer*& renderer);
	void free();
	void render(int x, int y, SDL_Renderer*& renderer, SDL_Rect* clip = NULL);
	int getWidth();
	int getHeight();
	bool setFont(const char* path, int size);
private:
	SDL_Texture* mTexture;
	TTF_Font* mFont = NULL;
	int mWidth;
	int mHeight;
};

