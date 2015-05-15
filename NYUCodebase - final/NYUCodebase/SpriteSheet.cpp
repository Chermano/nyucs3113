#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(float u, float v, float width, float height) {
	this->u = u;
	this->v = v;
	this->width = width;
	this->height = height;
}

void SpriteSheet::LoadTexture(const char *image_path) {
	SDL_Surface *surface = IMG_Load(image_path);

	GLuint newTextureID;
	glGenTextures(1, &newTextureID);
	glBindTexture(GL_TEXTURE_2D, newTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SDL_FreeSurface(surface);

	textureID = newTextureID;
}

void SpriteSheet::Draw(float scale, float xpos, float ypos) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 1.0);

	GLfloat quad[] = { -width * scale + xpos, height * scale + ypos, -width * scale + xpos, -height * scale + ypos,
						width * scale + xpos, -height * scale + ypos, width * scale + xpos, height * scale + ypos };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = { u, v, u, v + height, u + width, v + height, u + width, v }; 
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
}