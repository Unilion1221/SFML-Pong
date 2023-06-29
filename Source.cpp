#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
//using namespace sf;

//Ball Class

class Ball {
private:
	float moveSpeedX;
	float moveSpeedY;
	sf::CircleShape ball;

public:

	void createBall(float moveSpeedX, float moveSpeedY) {
		cout << "ayaya" << endl;
		ball.move(moveSpeedX, moveSpeedY);

	}

	virtual ~Ball();



	void printBall(sf::RenderWindow* win) {
		win->draw(this->ball);
	}

	Ball() {
		cout << "ayaya again" << endl;
		this->ball.setFillColor(sf::Color::Green);
		this->ball.setRadius(50);
		this->ball.setOutlineColor(sf::Color::Black);
		this->ball.setOutlineThickness(-3);
		this->ball.setPosition(625.f, 500.f);

		if (rand() % 10 >= 5) {
			this->moveSpeedX = 3.f;
			this->moveSpeedY = 3.f;
			cout << "ayaya radn" << endl;
		}
		else
		{
			this->moveSpeedX = 3.f;
			this->moveSpeedY = 3.f;
			cout << "ayaya rand" << endl;
		}
		this->createBall(moveSpeedX, moveSpeedY);
	}


	bool checkIfScored() {
		ball.move(moveSpeedX, moveSpeedY);
		if (this->ball.getGlobalBounds().left < 45.f) {
			this->ball.setFillColor(sf::Color::White);
			return false;
		}
		else if (this->ball.getGlobalBounds().left + this->ball.getGlobalBounds().width > 1355.f) {
			this->ball.setFillColor(sf::Color::White);
			return false;
		}
		else return true;
	}


	void checkCollisionBall() {

		if (this->ball.getGlobalBounds().top <= 250.f) {
			this->ball.setFillColor(sf::Color::Red);
			this->createBall(moveSpeedX, -moveSpeedY);
		}
		else if (this->ball.getGlobalBounds().top + this->ball.getGlobalBounds().height >= 900.f) {
			this->ball.setFillColor(sf::Color::Blue);
			this->createBall(-10.f, -10.f);
		}
	}


};




//Player Class

class Player {
private:
	float moveSpeed;
	sf::RectangleShape p;

public:
	void createPlayer(float posX, float posY, sf::Color color) {
		this->moveSpeed = 15.f;
		this->p.setFillColor(color);
		this->p.setSize(sf::Vector2f(20.f, 140.f));
		this->p.setPosition(posX, posY);
	}

	virtual ~Player() {

	}

	//test printing player
	void printPlayer(sf::RenderWindow* win) {
		win->draw(this->p);
	}

	//Movement input with collision check
	void checkInput1() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (this->p.getGlobalBounds().top > 260.f) {
				this->p.move(0.f, -this->moveSpeed);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (this->p.getGlobalBounds().top + this->p.getGlobalBounds().height < 840.f) {
				this->p.move(0.f, this->moveSpeed);
			}
		}
	}

	void checkInput2() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (this->p.getGlobalBounds().top > 260.f) {
				this->p.move(0.f, -this->moveSpeed);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (this->p.getGlobalBounds().top + this->p.getGlobalBounds().height < 840.f) {
				this->p.move(0.f, this->moveSpeed);
			}
		}
	}

	auto getPlayer() {
		return this->p.getGlobalBounds();
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
		this->posX = 100.f;
		this->posY = 480.f;
		this->color = sf::Color::Blue;
		createPlayer(posX, posY, color);
	}

	Player1() {
		this->createPlayer1();
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
		this->posX = 1280.f;
		this->posY = 480.f;
		this->color = sf::Color::Red;
		createPlayer(posX, posY, color);
	}

	Player2() {
		this->createPlayer2();
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

//Game Class
class Game
{
private:
	//Mouse Position in window
	sf::Vector2i mousePosInWindow;

	//Variables
	sf::RenderWindow* window;
	sf::Event eve;
	Player1 player1;
	Player2 player2;
	Ball ball;

	//Objects of the game
	WallsAndGates wallsAndGates;

	//Functions

	void initializeVars() {
		this->window = nullptr;

	}

	void initializeWindow() {
		this->window = new sf::RenderWindow(sf::VideoMode(1400, 900), "Game Window", sf::Style::Titlebar | sf::Style::Close);
		this->window->setFramerateLimit(60);
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

	//Initializing

	//Rendering Game
	void gameRender() {
		this->window->clear();

		this->wallsAndGates.printWallsAndGates(this->window);

		//test printing player
		this->player1.printPlayer(this->window);
		this->player2.printPlayer(this->window);
		if (ball.checkIfScored()) {
			this->ball.printBall(this->window);
		}


		this->window->display();
	}

	//Updating Game
	void gameUpdate() {
		this->ball.checkIfScored();

		this->ball.checkCollisionBall();

		this->getKeboardInp();
		//checking input for each player
		this->player1.checkInput1();
		this->player2.checkInput2();

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

	//MAY BE REMOVED
	//Mouse Position Update Function
	void updMouseInWindowPos() {
		this->mousePosInWindow = sf::Mouse::getPosition(*this->window);
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