#include "ClassDemoApp.h"

ClassDemoApp::ClassDemoApp() {
	Init();
	done = false;

	bulletIndex = 0;

	lastCheck = 0;
	isOn = false;
	start = false;

	state = GAME_SCREEN;

	music = Mix_LoadMUS("DJ Sona Kinetic (The Crystal Method x Dada Life).mp3");
	//music = Mix_LoadMUS("DJ Sona Concussive (Bassnectar x Renholder).mp3");

	goLeft = -1;
	move = false;
	shipX = 0;
	shipPos = 0;
	}

ClassDemoApp::~ClassDemoApp() {
	Mix_FreeMusic(music);
	SDL_Quit();
}

void ClassDemoApp::Init() {
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096);

}

void ClassDemoApp::Render(int time) {
	// render stuff    

	glClear(GL_COLOR_BUFFER_BIT);

	/*switch (state){
	case TITLE_SCREEN:
		displayTitle();
		break;
	case GAME_SCREEN:
		playGame(time);
		break;
	case PAUSE:
		pauseGame();
		break;
	}*/

	SpriteSheet background(989 / 3259.0, 0 / 2444.0, 1633 / 3259.0, 1505 / 2444.0);
	background.LoadTexture("background.png");
	background.Draw(2.0f, 0, 0);

	if (start){
		if ((time - lastCheck) >= 468){
			shootBullet(time);
			lastCheck = time;
		}
	}

	//draw ship
	if (move)
		shipX = .25*goLeft;
	else
		shipX = 0;

	if (shipPos < shipX)
		shipPos += .05;
	else if (shipPos > shipX)
		shipPos -= .05;

	SpriteSheet ship(247 / 1024.0, 84 / 1024.0, 99 / 1024.0, 75 / 1024.0);
	ship.LoadTexture("sheet.png");
	ship.Draw(1.0f, shipPos, -.75);

	shootAllBullets();

	SDL_GL_SwapWindow(displayWindow);
}

void ClassDemoApp::Update(int time){
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
			done = true;
		}
		else if (event.type == SDL_KEYDOWN){
			/*if (state == TITLE_SCREEN && event.key.keysym.scancode == SDL_SCANCODE_G) {
				state = GAME_SCREEN;
			}
			if (state == GAME_SCREEN && event.key.keysym.scancode == SDL_SCANCODE_P) {
					state = PAUSE;
			}
			if (state == PAUSE && event.key.keysym.scancode == SDL_SCANCODE_P) {
				state = GAME_SCREEN;
			}
			if (state == GAME_SCREEN){
				if (event.key.keysym.scancode == SDL_SCANCODE_M) {
					Mix_PlayMusic(music, -1);
					//start = true; //if this is ever uncommented, the computer dies after ~30 seconds (not enough memory?)
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
					//shootBullet(time); //manually shoot
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
					move = true;
					//goLeft *= -1;
					goLeft = 1;
				}
			}*/
			//if (event.key.keysym.scancode == SDL_SCANCODE_M) {
			//	Mix_PlayMusic(music, -1);
			//	//start = true; //if this is ever uncommented, the computer dies after ~30 seconds (not enough memory?)
			//}
			//if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
			//	shootBullet(time); //manually shoot
			//}
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
				move = true;
				//goLeft *= -1;
				goLeft = 1;
			}
		}
		else if (event.type == SDL_KEYUP)
			move = false;
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

void ClassDemoApp::shootBullet(int currentTime) {
	allBullets[bulletIndex].changeDisplay(true);
	allBullets[bulletIndex].changeDrawTime(currentTime);

	bulletIndex++;
	if (bulletIndex > MAX_BULLETS - 1) {
		bulletIndex = 0;
	}
}

void ClassDemoApp::shootAllBullets(){
	for (int i = 0; i < MAX_BULLETS; i++)
		if (allBullets[i].shouldDisplay())
			allBullets[i].lineFire();
}

void ClassDemoApp::playGame(int currentTime){
	SpriteSheet background(989 / 3259.0, 0 / 2444.0, 1633 / 3259.0, 1505 / 2444.0);
	background.LoadTexture("background.png");
	background.Draw(2.0f, 0, 0);

	if (start){
		if ((currentTime - lastCheck) >= 468){
			shootBullet(currentTime);
			lastCheck = currentTime;
		}
	}

	//draw block
	if (move)
		shipX = .25*goLeft;
	else
		shipX = 0;

	if (shipPos < shipX)
		shipPos += .05;
	else if (shipPos > shipX)
		shipPos -= .05;

	SpriteSheet ship(247 / 1024.0, 84 / 1024.0, 99 / 1024.0, 75 / 1024.0);
	ship.LoadTexture("sheet.png");
	ship.Draw(1.0f, shipPos, -.75);

	shootAllBullets();
}

void ClassDemoApp::displayTitle(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	SpriteSheet title(10 / 764.0, 122 / 408.0, 361 / 764.0, 271 / 408.0);
	title.LoadTexture("assets.png");
	title.Draw(1.0f, 0, .25);

	SpriteSheet play(314 / 764.0, 14 / 408.0, 450 / 764.0, 67 / 408.0);
	play.LoadTexture("assets.png");
	play.Draw(1.0f, 0, -.6);
}

void ClassDemoApp::pauseGame(){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	SpriteSheet pause(14 / 764.0, 8 / 408.0, 285 / 764.0, 75 / 408.0);
	pause.LoadTexture("assets.png");
	pause.Draw(1.0f, 0, 0);
}