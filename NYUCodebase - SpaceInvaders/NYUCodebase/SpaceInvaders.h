#pragma once

#include "ClassDemoApp.h"
#include "SpriteSheet.h"

#include <vector>

class Bullet;

class Character{

public:
	Character(float newU, float newV, float newWidth, float newHeight, float newX, float newY, std::vector <Bullet> newVolley);
	void collision();
	void fire();
	void playerFire();

	//get functions
	bool killed();
	float getU();
	float getV();
	float getWidth();
	float getHeight();
	float getX();
	float getY();

private:
	float thisU;
	float thisV;
	float thisWidth;
	float thisHeight;

	float xPos;
	float yPos;

	bool isDead;

	std::vector <Bullet> volley;
};


class SpaceInvaders{

public:
	SpaceInvaders();
	void displayTitle();
	void displaySelect();
	void displayGameOver();
	void runGame(bool space, bool left, bool right);
	void drawScore();
	void spacePressed();
	void leftPressed();
	void rightPressed();

private:
	int score;
};

