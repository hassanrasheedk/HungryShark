#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
using namespace std;
using namespace sf;

class Highscore {//high score class for setting and getting new and previous highscores respectively
	int highscore;
public:
	int gethighscore();
	void sethighscore(int score);
};

class EaterShark {//main shark's class

	Texture sharkTexture;
	float xpos, ypos;
	int health;
public:
	void setTexSprNrm();
	void setTexSprEat();
	void setTexSprDead();
	Sprite sharkSprite;
	EaterShark();
	float returnxpos();
	float returnypos();
	void moveup(float speed);
	void movedown(float speed);
	void decreaseHealth(int healthImpact);
	int returnHealth();
};

class Fish {//fish class, an abstract class for fish derived classes
public:
	int xpos, ypos;
	virtual void fishMove(float speed) = 0;
	int healthDecrease();
	Sprite fishSprite;
	Texture fishTexture;
protected:
	int healthImpact;
};

class Main {//main class, contains some major aspects of the game such as speed, score etc
	float speed;
public:
	int score;
	Main();
	void increaseSpeed();
	int returnScore();
	void scoreIncrement(int healthImpact);
	float getSpeed();
};

class greenFish :public Fish {//slowest fish
public:
	greenFish();
	virtual void fishMove(float speed);
};

class yellowFish :public Fish {//fish with medium speed
public:
	yellowFish();
	virtual void fishMove(float speed);
};

class redFish :public Fish {//fastest and largest fish
public:
	redFish();
	virtual void fishMove(float speed);
};
int mainGame();//main game function
