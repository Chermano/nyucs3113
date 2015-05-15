#pragma once

#include "ClassDemoApp.h"

class SpriteSheet {

public:
	//SpriteSheet();
	void LoadTexture(const char *image_path);
	SpriteSheet(float u, float v, float width, float height);
	void Draw(float scale, float xpos, float ypos);

private:
	float scale;
	GLuint textureID;
	float u;
	float v;
	float width;
	float height;
};