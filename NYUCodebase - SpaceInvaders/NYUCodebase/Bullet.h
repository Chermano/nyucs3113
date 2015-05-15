#pragma once

//class SpriteSheet;



class Bullet{

public:
	Bullet(float u, float v, float w, float h, const char *name);

	void normalFire(int numSteps);

	bool shouldDisplay();
	void changeDisplay(bool newDisplay);

private:
	float bulletU;
	float bulletV;
	float bulletW;
	float bulletH;

	const char *imageName;

	bool display;
};