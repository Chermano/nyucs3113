#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "SpriteSheet.h"

class ClassDemoApp {

public:

	ClassDemoApp();
	~ClassDemoApp();

	void Init();
	bool UpdateAndRender();
	void Render(int time);
	void Update(int time);

	GLuint LoadTexture(const char *image_path);
	void DrawSprite(GLint texture, float x, float y, float rotation, float width, float height);

private:

	bool done;
	int lastCheck;
	SDL_Window* displayWindow;
	float x;
	float y;
};