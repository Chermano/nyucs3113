#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "SpriteSheet.h"
#include "Bullet.h"

#define MAX_BULLETS 20

class ClassDemoApp {

public:

	ClassDemoApp();
	~ClassDemoApp();

	void Init();
	bool UpdateAndRender();
	void Render(int time);
	void Update(int time);
	void shootBullet(int currentTime);
	void shootAllBullets();

	void displayTitle();
	void playGame(int currentTime);
	void pauseGame();

	enum GameState { TITLE_SCREEN, GAME_SCREEN, PAUSE };

	GLuint LoadTexture(const char *image_path);
	void DrawSprite(GLint texture, float x, float y, float rotation, float width, float height);

private:
	bool done;
	SDL_Window* displayWindow;
	Mix_Music *music;

	int lastCheck;
	bool isOn;
	bool start;

	GameState state;

	Bullet allBullets[MAX_BULLETS];
	int bulletIndex;

	int goLeft;
	bool move;
	float shipX;
	float shipPos;
};