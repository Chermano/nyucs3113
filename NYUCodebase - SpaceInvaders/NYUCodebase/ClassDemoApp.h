#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

class SpaceInvaders;

class ClassDemoApp {

public:

	ClassDemoApp();
	~ClassDemoApp();

	void Init();
	bool UpdateAndRender();
	void Render(int time);
	void Update(int time);

	enum GameState { TITLE_SCREEN, GAME_SCREEN, GAME_OVER };

	GLuint LoadTexture(const char *image_path);
	void DrawSprite(GLint texture, float x, float y, float rotation, float width, float height);

private:

	//SpaceInvaders newSIGame;

	bool spaceKey;
	bool leftKey;
	bool rightKey;

	bool done;
	bool isOn;
	int lastCheck;
	SDL_Window* displayWindow;
	GameState state;
};