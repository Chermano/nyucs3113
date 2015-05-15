#include "SpaceInvaders.h"
#include "Bullet.h"


SpaceInvaders::SpaceInvaders(){ score = 12; }

void SpaceInvaders::displayTitle(){

	SpriteSheet title(16.0 / 434.0, 44.0 / 348.0, 236.0 / 434.0, 172.0 / 348.0);
	title.LoadTexture("invaders.png");
	title.Draw(1.0f, 0, .25);

}

void SpaceInvaders::displaySelect(){

	SpriteSheet start(9.0 / 434.0, 216.0 / 348.0, 323.0 / 434.0, 38.0 / 348.0);
	start.LoadTexture("invaders.png");
	start.Draw(1.0f, 0, -.5);
}

void SpaceInvaders::displayGameOver(){

	SpriteSheet gameOver(480.0 / 480.0, 480.0 / 480.0, 480.0 / 480.0, 480.0 / 480.0);
	gameOver.LoadTexture("game_over.png");
	gameOver.Draw(1.0f, 0, 0);
}

void SpaceInvaders::spacePressed(){}
void SpaceInvaders::leftPressed(){}
void SpaceInvaders::rightPressed(){}

void SpaceInvaders::runGame(bool space, bool left, bool right){

	std::vector < Character > Line1invaders;
	std::vector < Character > Line2invaders;
	std::vector < Character > Line3invaders;

	std::vector <Bullet> alienBullets;
	std::vector <Bullet> playerBullets;

	Bullet alienShot(0.0 / 138.0, 60.0 / 72.0, 6.0 / 138.0, 12.0 / 72.0, "gameAssets.png");
	Bullet charShot(98.0 / 138.0, 31.0 / 72.0, 3.0 / 138.0, 6.0 / 72.0, "gameAssets.png");

	for (int temp = 0; temp < 3; temp++){
		playerBullets.push_back(charShot);
	}
	

	//creates the enemy aliens (3 rows of 10) and stores them in a vector
	for (int i = 0; i < 10; i++){
		Character tempInvader1(0.0 / 138.0, 28.0 / 72.0, 16.0 / 138.0, 16.0 / 72.0, -.5 + i*.1, .5, alienBullets);
		Character tempInvader2(16.0 / 138.0, 28.0 / 72.0, 22.0 / 138.0, 16.0 / 72.0, -.5 + i*.1, .3, alienBullets);
		Character tempInvader3(38.0 / 138.0, 28.0 / 72.0, 24.0 / 138.0, 16.0 / 72.0, -.5 + i*.1, .1, alienBullets);
		
		Line1invaders.push_back(tempInvader1);
		Line2invaders.push_back(tempInvader2);
		Line3invaders.push_back(tempInvader3);
	}

	//-------draw functions---------

	drawScore();

	//displays the aliens
	for (int j = 0; j < 10; j++){
		if (!Line1invaders[j].killed()){
			SpriteSheet enemy1(Line1invaders[j].getU(), Line1invaders[j].getV(), Line1invaders[j].getWidth(), Line1invaders[j].getHeight());
			enemy1.LoadTexture("gameAssets.png");
			enemy1.Draw(.25f, Line1invaders[j].getX(), Line1invaders[j].getY());
		}

		if (!Line2invaders[j].killed()){
			SpriteSheet enemy2(Line2invaders[j].getU(), Line2invaders[j].getV(), Line2invaders[j].getWidth(), Line2invaders[j].getHeight());
			enemy2.LoadTexture("gameAssets.png");
			enemy2.Draw(.25f, Line2invaders[j].getX(), Line2invaders[j].getY());
		}

		if (!Line3invaders[j].killed()){
			SpriteSheet enemy3(Line3invaders[j].getU(), Line3invaders[j].getV(), Line3invaders[j].getWidth(), Line3invaders[j].getHeight());
			enemy3.LoadTexture("gameAssets.png");
			enemy3.Draw(.25f, Line3invaders[j].getX(), Line3invaders[j].getY());
		}
		
	}

	if (space){
		for (int size = 0; size < playerBullets.size(); ){
			if (!playerBullets[size].shouldDisplay()){
				playerBullets[size].changeDisplay(true);
				size = 4; // or break;
			}
			else
				size++;
		}
	}

	Character player1(86.0 / 138.0, 28.0 / 72.0, 26.0 / 138.0, 16.0 / 72.0, 0, -.75, playerBullets);
	if (!player1.killed()){
		SpriteSheet thePlayer(player1.getU(), player1.getV(), player1.getWidth(), player1.getHeight());
		thePlayer.LoadTexture("gameAssets.png");
		thePlayer.Draw(.25f, player1.getX(), player1.getY());
	}

	player1.fire();

}

void SpaceInvaders::drawScore(){
	int onesDigit = score % 10;
	int tensDigit = score / 10;

	std::vector <SpriteSheet> numbers;
	//0
	SpriteSheet zero(1.0 / 434.0, 5.0 / 348.0, 19.0 / 434.0, 19.0 / 348.0);
	numbers.push_back(zero);
	//1
	SpriteSheet one(37.0 / 434.0, 4.0 / 348.0, 11.0 / 434.0, 20.0 / 348.0);
	numbers.push_back(one);
	//2
	SpriteSheet two(66.0 / 434.0, 5.0 / 348.0, 17.0 / 434.0, 19.0 / 348.0);
	numbers.push_back(two);
	//3
	SpriteSheet three(99.0 / 434.0, 5.0 / 348.0, 16.0 / 434.0, 19.0 / 348.0);
	numbers.push_back(three);
	//4
	SpriteSheet four(130.0 / 434.0, 5.0 / 348.0, 17.0 / 434.0, 19.0 / 348.0);
	numbers.push_back(four);
	//5
	SpriteSheet five(163.0 / 434.0, 5.0 / 348.0, 15.0 / 434.0, 19.0 / 348.0);
	numbers.push_back(five);
	//6
	SpriteSheet six(195.0 / 434.0, 5.0 / 348.0, 16.0 / 434.0, 19.0 / 348.0);
	numbers.push_back(six);
	//7
	SpriteSheet seven(227.0 / 434.0, 5.0 / 348.0, 15.0 / 434.0, 19.0 / 348.0);
	numbers.push_back(seven);
	//8
	SpriteSheet eight(259.0 / 434.0, 5.0 / 348.0, 16.0 / 434.0, 19.0 / 348.0);
	numbers.push_back(eight);
	//9
	SpriteSheet nine(290.0 / 434.0, 5.0 / 348.0, 16.0 / 434.0, 19.0 / 348.0);
	numbers.push_back(nine);

	SpriteSheet scoreDisplay(0.0 / 138.0, 0.0 / 72.0, 138.0 / 138.0, 28.0 / 72.0);
	scoreDisplay.LoadTexture("gameAssets.png");
	scoreDisplay.Draw(.25f, 0, .75);

	numbers[onesDigit].LoadTexture("invaders.png");
	numbers[onesDigit].Draw(1.0f, .6, .75);

	numbers[tensDigit].LoadTexture("invaders.png");
	numbers[tensDigit].Draw(1.0f, .5, .75);
}

Character::Character(float newU, float newV, float newWidth, float newHeight, float newX, float newY, std::vector <Bullet> allBullets){
	thisU = newU;
	thisV = newV;
	thisWidth = newWidth;
	thisHeight = newHeight;

	xPos = newX;
	yPos = newY;

	isDead = false;

	volley = allBullets;
}
void Character::collision(){}
void Character::fire(){
	for (int i = 0; i < volley.size(); i++){
		volley[i].normalFire(10);
	}
}

//not using
void Character::playerFire(){
	SpriteSheet shot(98.0 / 138.0, 31.0 / 72.0, 3.0 / 138.0, 6.0 / 72.0);
	shot.LoadTexture("gameAssets.png");

	int currentMS = SDL_GetTicks();
	int lastTime = 0;
	int frameCounter = 0;

	shot.Draw(.25f, xPos, yPos + thisHeight / 2 + .05*frameCounter);

	/*while (frameCounter < 10){

		shot.Draw(.25f, xPos, yPos + thisHeight / 2 + .05*frameCounter);

		if (currentMS - lastTime >= 1000){
			frameCounter++;
			lastTime = currentMS;
		}
	}*/
}

bool Character::killed(){ return isDead; }

float Character::getU(){ return thisU; }
float Character::getV(){ return thisV; }
float Character::getWidth(){ return thisWidth; }
float Character::getHeight(){ return thisHeight; }
float Character::getX(){ return xPos; }
float Character::getY(){ return yPos; }