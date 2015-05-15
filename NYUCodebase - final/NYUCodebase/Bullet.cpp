#include "Bullet.h"
#include "SpriteSheet.h"


Bullet::Bullet(float newU, float newV, float newW, float newH, const char *newName){
	bulletU = newU;
	bulletV = newV;
	bulletW = newW;
	bulletH = newH;

	imageName = newName;

	x = 0;
	y = 0;
	angle = 0;

	display = false;
}

Bullet::Bullet(){
	bulletU = 1;
	bulletV = 1;
	bulletW = 1;
	bulletH = 1;

	imageName = "EarthLogo.png";

	x = 0;
	y = 0;
	angle = 0;
	drawAtTime = 0;

	display = false;

	//shot(bulletU, bulletV, bulletW, bulletH);
	//shot.LoadTexture(imageName);
}

bool Bullet::shouldDisplay(){
	return display;
}

void Bullet::changeDisplay(bool newDisplay){
	display = newDisplay;
}

void Bullet::changeDrawTime(float newTime){
	drawAtTime = newTime;
}

void Bullet::lineFire(){
	SpriteSheet shot(bulletU, bulletV, bulletW, bulletH);
	shot.LoadTexture(imageName);

	float distance = (SDL_GetTicks() - drawAtTime)/2000.0;

	if (distance > 1)
		display = false;

	shot.Draw(.05f, 0 + x, .75 + (16.0 / 72.0) / 2 + y - distance);
}

//void Bullet::shootSpiral(float distance, float angleOffset) {
//	for (int i = 0; i < numBullets; i++) {
//		float x = distance * cos(radians(angleOffset + i * 360 / numBullets));
//		float y = distance * sin(radians(angleOffset + i * 360 / numBullets));
//
//		bullet = new CircleBullet(x + xOffset, y + yOffset);
//		bullet.fire();
//	}
//}

//void Bullet::normalFire(int numSteps){
//	SpriteSheet shot(bulletU, bulletV, bulletW, bulletH);
//	shot.LoadTexture(imageName);
//
//	int ms = SDL_GetTicks();
//
//	static int count = 0;
//	static int lastDisp = 0;
//
//	if (display){
//		shot.Draw(.25f, 0, -.75 + (16.0 / 72.0) / 2 + .1*count);
//
//		if ((ms - lastDisp) >= 1000){
//			if (count < numSteps)
//				count++;
//			lastDisp = ms;
//		}
//
//		if (count >= numSteps)
//			display = false;
//	}
//}