#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using namespace std;
//using namespace sf;


#define RA(min,max)	( (min) + rand() % ( (max) - (min) + 1) )//Taken from the final exam for OOP (was going to make it myself but since it was already made i used it)

//Player Class

class Player {
private:
	float moveSpeed;
	sf::RectangleShape p;

public:

	void createPlayer(float posX, float posY, sf::Color color) {
		this->moveSpeed = 10.f;
		this->p.setFillColor(color);
		this->p.setSize(sf::Vector2f(5.f, 140.f));
		this->p.setPosition(posX, posY);
	}

	virtual ~Player() {

	}

	//test printing player
	void printPlayer(sf::RenderWindow* win) {
		win->draw(this->p);
	}

	//Movement input with collision check
	virtual void checkInput() {

	}

	float getMoveSpeed() {
		return this->moveSpeed;
	}

	auto getPlayer() {
		return this->p.getGlobalBounds();
	}

	auto thisPlayer() {
		return this->p;
	}

	void movePlayer(float one, float two) {
		this->p.move(one, two);
	}

};

//////////////

//Ball Class
class Ball {
private:
	float moveSpeedX;
	float moveSpeedY;
	sf::CircleShape ball;
	Player player;

	sf::SoundBuffer buffer1;
	sf::Sound sound1;
	sf::SoundBuffer buffer2;
	sf::Sound sound2;

public:

	sf::Color getRandomColor()
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, 255);

		vector<sf::Color> colorVector;
		for (int i = 0; i < 16; ++i)
		{
			int r = dis(gen);
			int g = dis(gen);
			int b = dis(gen);
			colorVector.push_back(sf::Color(r, g, b));
		}

		uniform_int_distribution<> colorIndex(0, colorVector.size() - 1);
		int randomIndex = colorIndex(gen);

		return colorVector[randomIndex];
	}

	void createBall(float moveSpeedX, float moveSpeedY) {
		ball.move(moveSpeedX, moveSpeedY);

	}

	virtual ~Ball();

	void printBall(sf::RenderWindow* win) {
		win->draw(this->ball);
	}

	Ball() {	
		try {
			if (buffer1.loadFromFile("Sound/pong.wav")) {
				sound1.setBuffer(buffer1);
				cout << "Sound loaded" << endl;
			}
			else {
				throw 404;
			}
		}
		catch (...) {
			cout << "Could not load sound.\n";
		}

		try {
			if (buffer2.loadFromFile("Sound/score.wav")) {
				sound2.setBuffer(buffer2);
				cout << "Sound loaded" << endl;
			}
			else {
				throw 404;
			}
		}
		catch (...) {
			cout << "Could not load sound.\n";
		}

		this->ball.setRadius(26);
		this->ball.setOutlineColor(getRandomColor());
		this->ball.setOutlineThickness(0); //was -3
		this->ball.setPosition(625.f, 590.f);

		moveSpeedY = RA(-7, 7);
		moveSpeedX = (rand() % 3) + 6;
		this->createBall(moveSpeedX, moveSpeedY);
	}

	//this checks if the ball went into either the right or the left goal
	int checkIfScored() {
		ball.move(moveSpeedX, moveSpeedY);
		if (this->ball.getGlobalBounds().left + this->ball.getGlobalBounds().width > 1380.f) {
			sound2.play();
			this->ball.setFillColor(getRandomColor());
			//this->ball.setPosition(687.f, 513.f);
			this->ball.setPosition(625.f, 590.f);
			this->moveSpeedY = -1 * (rand() % 4);
			this->moveSpeedX = -1 * (6);//was 2
			return 2;
		}
		if (this->ball.getPosition().x < 20.f) {
			sound2.play();
			this->ball.setFillColor(getRandomColor());
			this->ball.setPosition(625.f, 590.f);
			this->moveSpeedY = (rand() % 4);
			this->moveSpeedX = 6;//was 2
			return 1;
		}
	}

	//this checks if ball collided with the upper or lower wall, or a player
	void checkCollisionBall(float topl, float heightl, float leftl, float widthl, float topr, float heightr, float leftr, float widthr) {

		if (this->ball.getGlobalBounds().top <= 250.f) {
			sound1.play();
			this->ball.setFillColor(getRandomColor());
			ball.move(moveSpeedX *= 1, moveSpeedY *= -1);
		}

		else if (this->ball.getGlobalBounds().top + this->ball.getGlobalBounds().height >= 850.f) {
			sound1.play();
			this->ball.setFillColor(getRandomColor());
			ball.move(moveSpeedX *= 1, moveSpeedY *= -1);
		}

	}

	void checkCollisionBallPlayer(float topl, float heightl, float leftl, float widthl, float topr, float heightr, float leftr, float widthr, int p1speed, int p2speed) {

		//blue
		if (this->ball.getPosition().x <= leftl + widthl && (this->ball.getPosition().y >= topl && this->ball.getPosition().y <= topl + heightl)) {
			sound1.play();
			this->ball.setFillColor(getRandomColor());

			ball.move(moveSpeedX = (moveSpeedX - 1) * -1, moveSpeedY += RA(-2, 2));
		}

		//reverse if of this->ball.getPosition().y + this->ball.getGlobalBounds().height

		//blue
		else if (this->ball.getPosition().x <= leftl + widthl && (this->ball.getPosition().y + this->ball.getGlobalBounds().height >= topl && this->ball.getPosition().y + this->ball.getGlobalBounds().height <= topl + heightl)) {
			sound1.play();
			this->ball.setFillColor(getRandomColor());

			ball.move(moveSpeedX = (moveSpeedX - 1) * -1, moveSpeedY += RA(-2, 2));
		}

		//red
		if (this->ball.getPosition().x + this->ball.getGlobalBounds().width >= leftr && (this->ball.getPosition().y >= topr && this->ball.getPosition().y <= topr + heightr)) {
			sound1.play();
			this->ball.setFillColor(getRandomColor());
			ball.move(moveSpeedX = (moveSpeedX + 1) * -1, moveSpeedY += RA(-2, 2));

		}

		//reverse if of this->ball.getPosition().y + this->ball.getGlobalBounds().height

		//red
		else if (this->ball.getPosition().x + this->ball.getGlobalBounds().width >= leftr && (this->ball.getPosition().y + this->ball.getGlobalBounds().height >= topr && this->ball.getPosition().y + this->ball.getGlobalBounds().height <= topr + heightr)) {
			sound1.play();
			this->ball.setFillColor(getRandomColor());

			ball.move(moveSpeedX = (moveSpeedX + 1) * -1, moveSpeedY += RA(-2, 2));
		}


		//blue
		if (this->ball.getPosition().x - abs(this->moveSpeedX) == leftl + widthl && (this->ball.getPosition().y >= topl && this->ball.getPosition().y <= topl + heightl) ||
			(this->ball.getPosition().x - abs(this->moveSpeedX) == leftl + widthl && (this->ball.getPosition().y + this->ball.getGlobalBounds().height >= topl && this->ball.getPosition().y + this->ball.getGlobalBounds().height <= topl + heightl))) {
			sound1.play();
			this->ball.setFillColor(getRandomColor());
			ball.move(moveSpeedX = (moveSpeedX - 1) * -1, moveSpeedY += RA(-2, 2));
		}

		//red
		if (this->ball.getPosition().x + 40.f + (10 + this->moveSpeedX) == leftr && (this->ball.getPosition().y >= topr && this->ball.getPosition().y <= topr + heightr) ||
			(this->ball.getPosition().x + 40.f + (10 + this->moveSpeedX) == leftr && (this->ball.getPosition().y + this->ball.getGlobalBounds().height >= topr && this->ball.getPosition().y + this->ball.getGlobalBounds().height <= topr + heightr))) {
			sound1.play();
			this->ball.setFillColor(getRandomColor());
			ball.move(moveSpeedX = (moveSpeedX + 1) * -1, moveSpeedY += RA(-2, 2));
		}
	}
};

//////////////

//Player1 class

class Player1 : public Player {
private:
	float posX, posY;
	sf::Color color;

public:
	void createPlayer1() {
		this->posX = 55.f;
		this->posY = 480.f;
		this->color = sf::Color::Blue;
		createPlayer(posX, posY, color);
	}

	Player1() {
		this->createPlayer1();
	}

	void checkInput() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (thisPlayer().getGlobalBounds().top > 260.f) {
				movePlayer(0.f, -getMoveSpeed());
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (thisPlayer().getGlobalBounds().top + thisPlayer().getGlobalBounds().height < 840.f) {
				movePlayer(0.f, getMoveSpeed());
			}
		}
	}

};

//////////////

//Player2 class

class Player2 : public Player {
private:
	float posX, posY;
	sf::Color color;

public:
	void createPlayer2() {
		this->posX = 1340.f;
		this->posY = 480.f;
		this->color = sf::Color::Red;
		createPlayer(posX, posY, color);
	}

	Player2() {
		this->createPlayer2();
	}

	void checkInput() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (thisPlayer().getGlobalBounds().top > 260.f) {
				movePlayer(0.f, -getMoveSpeed());
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (thisPlayer().getGlobalBounds().top + thisPlayer().getGlobalBounds().height < 840.f) {
				movePlayer(0.f, getMoveSpeed());
			}
		}
	}

};

//////////////

//Class WallsAndGates
class WallsAndGates {
private:
	sf::RectangleShape leftGate, rightGate, upperWall, lowerWall;

public:

	//creating the walls and gates
	void createFigure(sf::RectangleShape& figure, float posX, float posY, float sizeX, float SizeY, sf::Color color) {
		figure.setSize(sf::Vector2f(sizeX, SizeY));
		figure.setFillColor(color);
		figure.setOutlineColor(color);
		figure.setOutlineThickness(1.f);
		figure.setPosition(posX, posY);
	}

	//constructor
	WallsAndGates() {
		createFigure(leftGate, 0.f, 250.f, 50.f, 600.f, sf::Color::Blue);
		createFigure(rightGate, 1350.f, 250.f, 50.f, 600.f, sf::Color::Red);
		createFigure(upperWall, 0.f, 200.f, 1400.f, 50.f, sf::Color::Yellow);
		createFigure(lowerWall, 0.f, 850.f, 1400.f, 50.f, sf::Color::Yellow);
	}

	//prining the static objects on screen
	void printWallsAndGates(sf::RenderWindow* win) {
		win->draw(this->leftGate);
		win->draw(this->rightGate);
		win->draw(this->upperWall);
		win->draw(this->lowerWall);
	}

};

//////////////

//Scoreboard class
class Scoreboard {
private:
	sf::Font score_font;
	sf::Font line_font;
	sf::Text score_blue;
	sf::Text score_red;
	sf::Text line;
public:

	void pritnScore(sf::RenderWindow* win, int blue, int red) {
		this->score_red.setString(to_string(red));
		this->score_blue.setString(to_string(blue));
		win->draw(this->score_blue);
		win->draw(this->score_red);
		win->draw(this->line);
	}

	Scoreboard() {
		try {
			if (this->score_font.loadFromFile("Fonts/Begok v15_2015.ttf")) {
				cout << "Font loaded" << endl;
			}
			else {
				throw 404;
			}
		}
		catch (...) {
			cout << "Could not load font.\n";
		}
		try {
			if (this->line_font.loadFromFile("Fonts/line.ttf")) {
				cout << "Font loaded" << endl;
			}
			else {
				throw 404;
			}
		}
		catch (...) {
			cout << "Could not load font.\n";
		}
		//Blue player score
		this->score_blue.setFont(this->score_font);
		this->score_blue.setCharacterSize(100);
		this->score_blue.setFillColor(sf::Color::Blue);
		this->score_blue.setStyle(sf::Text::Bold);
		this->score_blue.setPosition(400.f, 30.f);

		this->score_red.setFont(this->score_font);
		this->score_red.setCharacterSize(100);
		this->score_red.setFillColor(sf::Color::Red);
		this->score_red.setStyle(sf::Text::Bold);
		this->score_red.setPosition(900.f, 30.f);

		this->line.setFont(this->line_font);
		this->line.setCharacterSize(100);
		this->line.setFillColor(sf::Color::Green);
		this->line.setStyle(sf::Text::Bold);
		this->line.setString("I");
		this->line.setPosition(700.f, 30.f);
	}

};

//////////////

//Game Class
class Game
{
private:
	//Mouse Position in window
	sf::Vector2i mousePosInWindow;

	//Variables
	sf::RenderWindow* window;
	sf::Event eve;
	Ball ball;
	Scoreboard score;
	int score_blue_num;
	Player1 player1;
	Player2 player2;
	int score_red_num;
	bool win_condition;
	int win_score;
	sf::Font winTextFont;
	sf::Text winText;
	sf::SoundBuffer buffer3;
	sf::Sound sound3;


	//Static objects of the game 
	WallsAndGates wallsAndGates;

	//Functions
	void initializeVars() {
		this->window = nullptr;
		this->score_blue_num = 0;
		this->score_red_num = 0;
		this->win_condition = false;
		this->win_score = 10;
		try {
			if (buffer3.loadFromFile("Sound/sound3.wav")) {
				sound3.setBuffer(buffer3);
				cout << "Sound loaded" << endl;
			}
			else {
				throw 404;
			}
		}
		catch (...) {
			cout << "Could not load sound.\n";
		}
	}

	void initializeWindow() {
		this->window = new sf::RenderWindow(sf::VideoMode(1400, 900), "Game Window", sf::Style::Titlebar | sf::Style::Close);
		this->window->setFramerateLimit(100);
	}

	void updateScore() {
		int num = ball.checkIfScored();
		if (num == 1) {
			this->score_red_num += 1;
		}
		if (num == 2) {
			this->score_blue_num += 1;
		}
	}

	void blueWon() {
		if (!this->winTextFont.loadFromFile("Fonts/Begok v15_2015.ttf")) {
			throw("Font can not be opened!");
		}
		this->winText.setFont(this->winTextFont);
		this->winText.setCharacterSize(100);
		this->winText.setFillColor(sf::Color::Blue);
		this->winText.setStyle(sf::Text::Bold);
		this->winText.setString("blue player won\n\npress esc to quit");
		this->winText.setPosition(70.f, 200.f);
		this->window->draw(winText);
	}

	void redWon() {
		if (!this->winTextFont.loadFromFile("Fonts/Begok v15_2015.ttf")) {
			throw("Font can not be opened!");
		}
		this->winText.setFont(this->winTextFont);
		this->winText.setCharacterSize(100);
		this->winText.setFillColor(sf::Color::Red);
		this->winText.setStyle(sf::Text::Bold);
		this->winText.setString("red player won\n\npress esc to quit");
		this->winText.setPosition(70.f, 200.f);
		this->window->draw(winText);
	}

	int player1Speed() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			return -15;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			return 15;
		}
		else {
			return 0;
		}
		return 0;
	}

	int player2Speed() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			return -15;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			return 15;
		}
		else {
			return 0;
		}
		return 0;
	}


public:

	//test func
	WallsAndGates getBoard() {
		return wallsAndGates;
	}

	//Constructor and Destructor
	Game() {
		this->initializeVars();
		this->initializeWindow();
	}

	~Game() {
		delete this->window;
	}

	//check if game is running
	bool gameRunState() {
		return this->window->isOpen();
	}

	//Rendering Game
	void gameRender() {
		this->window->clear();

		if (this->score_blue_num == this->win_score || this->score_red_num == this->win_score) {
			this->win_condition = true;
		}

		//Checking win condition
		if (!this->win_condition) {
			sound3.play();
			//printing score
			this->updateScore();
			this->score.pritnScore(this->window, this->score_blue_num, this->score_red_num);

			//printing player
			this->player1.printPlayer(this->window);
			this->player2.printPlayer(this->window);

			this->wallsAndGates.printWallsAndGates(this->window);

			this->ball.printBall(this->window);
		}
		else {
			if (this->score_blue_num == this->win_score) {
				this->blueWon();
			}
			if (this->score_red_num == this->win_score){
				this->redWon();
			}
		}

		this->window->display();
	}

	//Updating Game
	void gameUpdate() {
		this->getKeboardInp();
		this->player1Speed();
		this->player2Speed();

		//checking input for each player
		this->player1.checkInput();
		this->player2.checkInput();

		this->ball.checkCollisionBallPlayer(this->player1.getPlayer().top, this->player1.getPlayer().height, this->player1.getPlayer().left, this->player1.getPlayer().width,
			this->player2.getPlayer().top, this->player2.getPlayer().height, this->player2.getPlayer().left, this->player2.getPlayer().width, this->player1Speed(), this->player2Speed());

		this->ball.checkCollisionBall(this->player1.getPlayer().top, this->player1.getPlayer().height, this->player1.getPlayer().left, this->player1.getPlayer().width,
			this->player2.getPlayer().top, this->player2.getPlayer().height, this->player2.getPlayer().left, this->player2.getPlayer().width);

	}

	//To close window with input
	void getKeboardInp() {
		while (this->window->pollEvent(this->eve))
		{
			switch (this->eve.type)
			{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				//if esc is pressed we close the window
				if (this->eve.key.code == sf::Keyboard::Escape) {
					this->window->close();
					break;
				}
			}
		}
	}

};

///////////

int main() {

	Game game;

	while (game.gameRunState())
	{
		//Updating the game
		game.gameUpdate();

		//Rendering the game
		game.gameRender(); 

	}

}

Ball::~Ball()
{
}