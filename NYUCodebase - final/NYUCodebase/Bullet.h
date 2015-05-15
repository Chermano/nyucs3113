#pragma once

class SpriteSheet;



class Bullet{

public:
	Bullet(float u, float v, float w, float h, const char *name);
	Bullet();

	//void normalFire(int numSteps);
	void lineFire();

	bool shouldDisplay();
	void changeDisplay(bool newDisplay);

	void changeDrawTime(float newTime);

private:
	float bulletU;
	float bulletV;
	float bulletW;
	float bulletH;

	float x;
	float y;
	float angle;
	float drawAtTime;

	const char *imageName;

	bool display;

	//SpriteSheet shot;
};