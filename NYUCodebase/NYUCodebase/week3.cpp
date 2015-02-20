
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <math.h>

SDL_Window* displayWindow;

GLuint LoadTexture(const char *image_path) {
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

void DrawSprite(GLint texture, float x, float y, float rotation, float width, float height) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	glRotatef(rotation, 0.0, 0.0, 1.0);

	GLfloat quad[] = { -1 * width, 1 * height, -1 * width, -1 * height, 1 * width, -1 * height, 1 * width, 1 * height};
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

bool collisionCheckLeft(float paddleXPos, float paddleYPos, float currBallX, float currBallY){
	float disFromCenterPaddleX = .05;
	float disFromCenterPaddleY = .25;
	float ballRadii = .05;

	//left paddle check
	if ((paddleXPos + disFromCenterPaddleX) > (currBallX - ballRadii) &&
		(paddleYPos + disFromCenterPaddleY) > (currBallY - ballRadii) && (paddleYPos - disFromCenterPaddleY) < (currBallY - ballRadii))
		return true;

	return false;

}

bool collisionCheckRight(float paddleXPos, float paddleYPos, float currBallX, float currBallY){
	float disFromCenterPaddleX = .05;
	float disFromCenterPaddleY = .25;
	float ballRadii = .05;

	//right paddle check
	if ((paddleXPos - disFromCenterPaddleX) < (currBallX + ballRadii) &&
		(paddleYPos + disFromCenterPaddleY) > (currBallY - ballRadii) && (paddleYPos - disFromCenterPaddleY) < (currBallY - ballRadii))
		return true;

	return false;

}

bool hitTopOrBot(float currBallY){
	return (currBallY <= -1 || currBallY >= 1);
}

bool outOfBounds(float currBallX){
	return (currBallX <= -1 || currBallX >= 1);
}

int main(int argc, char *argv[])
{
	int windowW = 600;
	int windowH = 600;

	float lastFrameTicks = 0.0f;

	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowW, windowH, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	bool done = false;
	
	SDL_Event event;

	//new code
	GLuint pic1 = LoadTexture("FTLogo.png");
	GLuint pic2 = LoadTexture("SoulLogo.png");
	GLuint pic3 = LoadTexture("EarthLogo.png"); 

	float elapsed = 0;
	float player1X = -0.85f;
	float player2X = 0.85f;
	float player1Y = 0;
	float player2Y = 0;
	float ballX = 0;
	float ballY = 0;
	float ballAngle = 0;
	float ballSpeed = .4;
	bool moveBall = false;

	while (!done) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
				done = true;
			}
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.scancode == SDL_SCANCODE_W) { //player 1 up
					player1Y += .02f;
				}     
				if (event.key.keysym.scancode == SDL_SCANCODE_S) { //player 1 down
					player1Y -= .02f;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_UP) { //player 2 up
					player2Y += .02f;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) { //player 2 dpwn
					player2Y -= .02f;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_R) { //manual reset
					player1Y = 0;
					player2Y = 0;
					ballX = 0;
					ballY = 0;
					moveBall = false;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) { //starts the game
					if (!moveBall){
						moveBall = true;
						ballAngle = 300;
					}
				}
			}
		}

		//new code
		glClear(GL_COLOR_BUFFER_BIT);

		float ticks = (float)SDL_GetTicks() / 1000.0f;
		elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;

		if (moveBall){
			ballX += elapsed * ballSpeed * cos(ballAngle * 3.14f / 180);
			ballY += elapsed * ballSpeed * sin(ballAngle * 3.14f / 180);
		}

		if (hitTopOrBot(ballY) || 
			collisionCheckLeft(player1X, player1Y, ballX, ballY) || 
			collisionCheckRight(player2X, player2Y, ballX, ballY)){
			ballAngle += 114;
			ballSpeed += .05;
		}

		if (outOfBounds(ballX)){
			player1Y = 0;
			player2Y = 0;
			ballX = 0;
			ballY = 0;
			moveBall = false;
		}

		glLoadIdentity();

		GLfloat quad[] = { -0.05f + player1X, 0.25f + player1Y, -0.05f + player1X, -0.25f + player1Y, 0.05f + player1X, -0.25f + player1Y, 0.05f + player1X, 0.25f + player1Y };

		glVertexPointer(2, GL_FLOAT, 0, quad);
		glEnableClientState(GL_VERTEX_ARRAY);

		glDrawArrays(GL_QUADS, 0, 4);

		glLoadIdentity();

		GLfloat quad2[] = { -0.05f + player2X, 0.25f + player2Y, -0.05f + player2X, -0.25f + player2Y, 0.05f + player2X, -0.25f + player2Y, 0.05f + player2X, 0.25f + player2Y };

		glVertexPointer(2, GL_FLOAT, 0, quad2);
		glEnableClientState(GL_VERTEX_ARRAY);

		glDrawArrays(GL_QUADS, 0, 4);

		DrawSprite(pic3, ballX, ballY, 0, .4f / 8, .4f / 8);

		//end new code

		SDL_GL_SwapWindow(displayWindow);
	}





	SDL_Quit();
	return 0;
}