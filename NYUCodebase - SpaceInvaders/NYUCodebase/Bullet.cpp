#include "Bullet.h"
#include "SpriteSheet.h"


Bullet::Bullet(float newU, float newV, float newW, float newH, const char *newName){
	bulletU = newU;
	bulletV = newV;
	bulletW = newW;
	bulletH = newH;

	imageName = newName;

	display = false;
}

bool Bullet::shouldDisplay(){
	return display;
}

void Bullet::changeDisplay(bool newDisplay){
	display = newDisplay;
}

void Bullet::normalFire(int numSteps){
	SpriteSheet shot(bulletU, bulletV, bulletW, bulletH);
	shot.LoadTexture(imageName);

	int ms = SDL_GetTicks();

	static int count = 0;
	static int lastDisp = 0;

	if (display){
		shot.Draw(.25f, 0, -.75 + (16.0 / 72.0) / 2 + .1*count);

		if ((ms - lastDisp) >= 1000){
			if (count < numSteps)
				count++;
			lastDisp = ms;
		}

		if (count >= numSteps)
			display = false;
	}
}