#include "ClassDemoApp.h"
#include "SpaceInvaders.h"

ClassDemoApp::ClassDemoApp() {
	Init();
	done = false;
	isOn = false;
	spaceKey = false;
	leftKey = false;
	rightKey = false;
	lastCheck = 0;
	state = GAME_SCREEN;

	//newSIGame();
}

ClassDemoApp::~ClassDemoApp() {
	SDL_Quit();
}

void ClassDemoApp::Init() {
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);
}

void ClassDemoApp::Render(int time) {
	// render stuff    
	SpaceInvaders newSIGame;

	glClear(GL_COLOR_BUFFER_BIT);

	switch (state){
	case TITLE_SCREEN:
		newSIGame.displayTitle();
		if ((time - lastCheck) >= 1000){
			isOn = !isOn;
			lastCheck = time;
		}
		if (isOn)
			newSIGame.displaySelect();
		break;
	case GAME_SCREEN:
		newSIGame.runGame(spaceKey, leftKey, rightKey);
		break;
	case GAME_OVER:
		newSIGame.displayGameOver();
		break;
	}

	SDL_GL_SwapWindow(displayWindow);
}

void ClassDemoApp::Update(int time){
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (state == TITLE_SCREEN){
			if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_P) {
				state = GAME_OVER;
			}
		}
		else if (state == GAME_SCREEN){
			if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				spaceKey = true;
			}
			else
				spaceKey = false;
		}
	}
}

bool ClassDemoApp::UpdateAndRender() {
	int ticks = SDL_GetTicks();

	Update(ticks);
	Render(ticks);
	return done;
}

GLuint ClassDemoApp::LoadTexture(const char *image_path) {
	SDL_Surface *surface = IMG_Load(image_path);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	SDL_FreeSurface(surface);

	return textureID;
}

void ClassDemoApp::DrawSprite(GLint texture, float x, float y, float rotation, float width, float height) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	glRotatef(rotation, 0.0, 0.0, 1.0);

	GLfloat quad[] = { -1 * width, 1 * height, -1 * width, -1 * height, 1 * width, -1 * height, 1 * width, 1 * height };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
}