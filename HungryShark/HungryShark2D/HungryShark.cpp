#include <SFML/Graphics.hpp>
#include <iostream>
#include "HungryShark.h"
#include <string>
#include <time.h>
#include <fstream>
using namespace std;
using namespace sf;
int Highscore::gethighscore() {//highscore is obtained from a file
	int highscore;
	ifstream file("highscore.txt");
	file >> highscore;
	return highscore;
}
void Highscore::sethighscore(int score) {//new highscore is input to the file
	ofstream file("highscore.txt");
	file << to_string(score);
}
EaterShark::EaterShark() {//shark constructor
	xpos = 0;
	ypos = 0;
	sharkTexture.loadFromFile("Shark1animation.png");
	sharkSprite.setTexture(sharkTexture);
	sharkSprite.setPosition(xpos, ypos);
	health = 100;
}

void EaterShark::setTexSprEat() {//shark when it eats a fish
	sharkTexture.loadFromFile("Shark2animation.png");
	sharkSprite.setTexture(sharkTexture);
}
void EaterShark::setTexSprNrm() {//shark's normal state
	sharkTexture.loadFromFile("Shark1animation.png");
	sharkSprite.setTexture(sharkTexture);
}

void EaterShark::setTexSprDead() {//shark when dead
	sharkTexture.loadFromFile("Shark3animation.png");
	sharkSprite.setTexture(sharkTexture);
}

float EaterShark::returnxpos() {//returns x coordinate
	return xpos;
}
float EaterShark::returnypos() {//returns y coordinate
	return ypos;
}

void EaterShark::movedown(float speed) {//moves the shark down
	if (ypos < 520) {
		ypos = ypos + speed + 5;
	}
	sharkSprite.setPosition(xpos, ypos);
}
void EaterShark::moveup(float speed) {//moves shark up
	if (ypos > 0) {
		ypos = ypos - speed - 5;
	}
	sharkSprite.setPosition(xpos, ypos);
}

void EaterShark::decreaseHealth(int healthImpact) {//decreases health
	health = health - healthImpact;
}

int EaterShark::returnHealth() {//returns health
	return health;
}

int Fish::healthDecrease() {//returns amount of health to decrease
	return healthImpact;
}


Main::Main() {//main constructor
	score = 0;
	speed = 2;
}
void Main::increaseSpeed() {//speed is increased
	speed = speed + 1;
}

int Main::returnScore() {//score is returned
	return score;
}

void Main::scoreIncrement(int healthImpact) {//score is increased according to the health impact of the fish
	score = score + healthImpact;
}

float Main::getSpeed() {//speed is returned
	return speed;
}


greenFish::greenFish() {//greenfish constructor
	fishTexture.loadFromFile("greenfish1.png");
	fishSprite.setTexture(fishTexture);
	xpos = 800;
	ypos = 10 + (rand() % 500);
	fishSprite.setPosition(xpos, ypos);
	healthImpact = 5;
}

void greenFish::fishMove(float speed) {//move function of fish, takes speed of the game as input
	xpos = xpos - (speed - 1);
	fishSprite.setPosition(xpos, ypos);
}

yellowFish::yellowFish() {//yellow fish constructor
	fishTexture.loadFromFile("yellowFish.png");
	fishSprite.setTexture(fishTexture);
	xpos = 800;
	ypos = 50 + (rand() % 500);
	fishSprite.setPosition(xpos, ypos);
	healthImpact = 10;
}

void yellowFish::fishMove(float speed) {//move function of fish, takes speed of the game as input
	xpos = xpos - (speed);
	fishSprite.setPosition(xpos, ypos);
}

redFish::redFish() {//redfish constructor
	fishTexture.loadFromFile("redfish1.png");
	fishSprite.setTexture(fishTexture);
	xpos = 800;
	ypos = 100 + (rand() % 250);
	fishSprite.setPosition(xpos, ypos);
	healthImpact = 15;
}

void redFish::fishMove(float speed) {//move function of fish, takes speed of the game as input
	xpos = xpos - (speed + 1);
	fishSprite.setPosition(xpos, ypos);
}

int mainGame() {//main function of the game
	srand(time(NULL));
	RenderWindow window(sf::VideoMode(800, 600), "Hungry Shark");//window is created
	window.setPosition(sf::Vector2i(300, 0));//position of window is set
	Font font2;//fonts are initialised
	Font font3;

	font2.loadFromFile("Quicksand.otf");//fonts are loaded from files
	Font font;
	if (!font.loadFromFile("Amatic.ttf"))
	{
		return EXIT_FAILURE;
	}
	Main main;//an instance of main class is created
	EaterShark shark1;//main shark is created
	yellowFish *yellowFishes[3];//arrays fishes are created
	for (int i = 0; i < 3; i++) {
		yellowFishes[i] = new yellowFish;
	}
	redFish *redFishes[3];
	for (int i = 0; i < 3; i++) {
		redFishes[i] = new redFish;
	}
	greenFish *greenFishes[3];
	for (int i = 0; i < 3; i++) {
		greenFishes[i] = new greenFish;
	}
	Fish *ptr=new redFish;  //polymorhism
	//redFish red2;
	//ptr = &red2;
	
	Highscore high;//an instance of highscore is created
	Text highscoretext, scoretext, healthtext;//texts are created
	Sprite background;//background sprite is created
	Sprite background1;
	Texture t3;//textures created
	Texture t2;
	int frameno = 1;//frameno initialised

	t2.loadFromFile("water.jpg");//textures loaded from files
	t3.loadFromFile("back1.jpg");
	background1.setTexture(t3);
	background.setTexture(t2);
	//texts to be displayed are set
	highscoretext.setCharacterSize(30);
	highscoretext.setFont(font);
	highscoretext.setPosition(330, 40);
	highscoretext.setColor(Color::White);
	highscoretext.setStyle(Text::Bold);
	healthtext.setCharacterSize(30);
	healthtext.setFont(font2);
	healthtext.setPosition(20, 10);
	healthtext.setColor(Color::Red);
	scoretext.setCharacterSize(30);
	scoretext.setFont(font);
	scoretext.setPosition(350, 10);
	scoretext.setColor(Color::White);
	scoretext.setStyle(Text::Bold);
	//start the game loop
	while (window.isOpen())
	{
		//process events
		Event event;
		while (window.pollEvent(event))
		{
			//close window: exit
			if (event.type == Event::Closed)
				window.close();
			//escape pressed: exit
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		window.clear();//clears window
		//menu text is loaded
		Text play;
		if (!font3.loadFromFile("Amatic.ttf")) {
			cout << "error";
		}
		play.setFont(font3);
		play.setColor(Color::Red);
		play.setStyle(Text::Bold);
		play.setString("->Press Enter To Play!\n\n\n->Press Escape To Exit!");
		play.setCharacterSize(40);
		play.setPosition(50, 300);
		window.draw(background1);
		window.draw(play);
		window.display();
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			while (window.isOpen())
			{
				//process events
				Event event;
				while (window.pollEvent(event))
				{
					//close window: exit
					if (event.type == Event::Closed)
						window.close();
					//escape pressed: exit
					if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
						window.close();
				}
				//clear screen
				window.clear();
				if (Keyboard::isKeyPressed(Keyboard::Up)) {//move the main shark up
					shark1.moveup(main.getSpeed());
				}
				if (Keyboard::isKeyPressed(Keyboard::Down)) {//move the main shark up
					shark1.movedown(main.getSpeed());
					//s.setPosition(x, y);
				}
				// moves the fishes
				for (int i = 0; i < 3; i++) {
					yellowFishes[i]->fishMove(main.getSpeed());
					greenFishes[i]->fishMove(main.getSpeed());
					redFishes[i]->fishMove(main.getSpeed());
				}
				ptr->fishMove(0.5);  //polymorphism
				//checks if any of the fishes collide with the shark
				for (int i = 0; i < 3; i++) {
					if (((greenFishes[i]->xpos) - (shark1.returnxpos()) < 74 && (greenFishes[i]->xpos) - (shark1.returnxpos()) > -54) && (greenFishes[i]->ypos) - (shark1.returnypos()) < 59 && (greenFishes[i]->ypos) - (shark1.returnypos()) > -59) {
						shark1.setTexSprEat();
						main.scoreIncrement(greenFishes[i]->healthDecrease());//score is increased
						delete greenFishes[i];//deleted if collision occurs
						greenFishes[i] = new greenFish;//new instance is created dynamically
					}
					if (((yellowFishes[i]->xpos) - (shark1.returnxpos()) < 74 && (yellowFishes[i]->xpos) - (shark1.returnxpos()) > -54) && (yellowFishes[i]->ypos) - (shark1.returnypos()) < 61 && (yellowFishes[i]->ypos) - (shark1.returnypos()) > -61) {
						shark1.setTexSprEat();
						main.scoreIncrement(yellowFishes[i]->healthDecrease());
						delete yellowFishes[i];
						yellowFishes[i] = new yellowFish;
					}
					if ((redFishes[i]->xpos) - (shark1.returnxpos()) < 92 && (redFishes[i]->xpos) - (shark1.returnxpos()) > -54 && (redFishes[i]->ypos) - (shark1.returnypos()) < 59 && (redFishes[i]->ypos) - (shark1.returnypos()) > -59) {
						shark1.setTexSprEat();
						main.scoreIncrement(redFishes[i]->healthDecrease());
						delete redFishes[i];
						redFishes[i] = new redFish;
					}
				}
				if (((ptr->xpos) - (shark1.returnxpos()) < 74 && (ptr->xpos) - (shark1.returnxpos()) > -54) && (ptr->ypos) - (shark1.returnypos()) < 59 && (ptr->ypos) - (shark1.returnypos()) > -59) {
					shark1.setTexSprEat();                                //polymorphism
					main.scoreIncrement(ptr->healthDecrease());
					delete ptr;
					ptr = new redFish;

				}
				//checks if any of the fishes collide with shark's end of the window
				for (int i = 0; i < 3; i++) {
					if (redFishes[i]->xpos < 0) {
						shark1.decreaseHealth(redFishes[i]->healthDecrease());//health of the shark decreases
						delete redFishes[i];
						redFishes[i] = new redFish;
					}
					if (yellowFishes[i]->xpos < 0) {
						shark1.decreaseHealth(yellowFishes[i]->healthDecrease());
						delete yellowFishes[i];
						yellowFishes[i] = new yellowFish;
					}
					if (greenFishes[i]->xpos < 0) {
						shark1.decreaseHealth(greenFishes[i]->healthDecrease());
						delete greenFishes[i];
						greenFishes[i] = new greenFish;
					}
					if (ptr->xpos < 0) {                                  //polymorphism
						shark1.decreaseHealth(ptr->healthDecrease());
						delete ptr;
						ptr = new redFish;
					}

				}
				//strings are set in the text
				healthtext.setString("HP " + to_string(shark1.returnHealth()));
				scoretext.setString("Score " + to_string(main.score));
				highscoretext.setString("Highscore " + to_string(high.gethighscore()));
				window.setFramerateLimit(100);
				//objects are drawn to the screen
				window.draw(background);
				window.draw(shark1.sharkSprite);
				for (int i = 0; i < 3; i++) {
					window.draw(yellowFishes[i]->fishSprite);
					window.draw(redFishes[i]->fishSprite);
					window.draw(greenFishes[i]->fishSprite);
				}
				window.draw(ptr->fishSprite);
				if (frameno % 5 == 0) {
					shark1.setTexSprNrm();
				}
				window.draw(healthtext);
				window.draw(scoretext);
				window.draw(highscoretext);
				window.display();
				frameno++;
				if (shark1.returnHealth() <= 0)
					break;
			}
			//if new highscore is made
			if (main.score > high.gethighscore()) {
				highscoretext.setString("Congratulations!You've made new Highscore!\n");
				high.sethighscore(main.score);
				highscoretext.setPosition(200, window.getSize().y / 2 - 50);
				scoretext.setPosition(360, window.getSize().y / 2 - 10);
				shark1.setTexSprDead();
				window.clear();
				window.draw(background);
				window.draw(highscoretext);
				window.draw(scoretext);
				window.draw(shark1.sharkSprite);
				window.display();
				getchar();
				window.close();
			}
			else {//if highscore is not broken
				scoretext.setString("Your Score is " + to_string(main.score));
				scoretext.setPosition(window.getSize().x / 2 - 60, window.getSize().y / 2 - 50);
				highscoretext.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2 - 10);
				shark1.setTexSprDead();
				window.clear();
				window.draw(background);
				window.draw(scoretext);
				window.draw(highscoretext);
				window.draw(shark1.sharkSprite);
				window.display();
				getchar();
				window.close();
			}
		}
		if (frameno % 1200 == 0) {//speed of the game increases every 30 seconds
			main.increaseSpeed();
		}
	}
	return 0;
}