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



//Ball Class
class Ball {
private:
	float moveSpeedX;
	float moveSpeedY;
	sf::CircleShape ball;
	Player player;

public:

	void createBall(float moveSpeedX, float moveSpeedY) {
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
			this->moveSpeedX = -2.f;
			this->moveSpeedY = 2.f;
			cout << "ayaya rand" << endl;
		}
		this->createBall(moveSpeedX, moveSpeedY);
	}

	//this checks if the ball went into either the right or the left goal
	int checkIfScored() {
		ball.move(moveSpeedX, moveSpeedY);
		if (this->ball.getGlobalBounds().left < 45.f) {
			this->ball.setFillColor(sf::Color::White);
			return 1;
		}
		else if (this->ball.getGlobalBounds().left + this->ball.getGlobalBounds().width > 1355.f) {
			this->ball.setFillColor(sf::Color::White);
			return 2;
		}
	}

	//this checks if ball collided with the upper or lower wall, or a player
	void checkCollisionBall(float topl, float heightl, float leftl, float widthl, float topr, float heightr, float leftr, float widthr) {

		if (this->ball.getGlobalBounds().top <= 250.f) {
			this->ball.setFillColor(sf::Color::Magenta);
			ball.move(moveSpeedX *= 1, moveSpeedY *= -1);
		}
		else if (this->ball.getGlobalBounds().top + this->ball.getGlobalBounds().height >= 850.f) {
			this->ball.setFillColor(sf::Color::Blue);
			ball.move(moveSpeedX *= 1, moveSpeedY *= -1);
		}



		if (this->ball.getPosition().x <= leftl + widthl && (this->ball.getPosition().y >= topl && this->ball.getPosition().y <= topl + heightl)) {
			this->ball.setFillColor(sf::Color::Red);
			ball.move(moveSpeedX *= 1, moveSpeedY *= 1);
		}
		//reverse if of this->ball.getPosition().y + this->ball.getGlobalBounds().height
		if (this->ball.getPosition().x <= leftl + widthl && (this->ball.getPosition().y + this->ball.getGlobalBounds().height >= topl && this->ball.getPosition().y + this->ball.getGlobalBounds().height <= topl + heightl)) {
			this->ball.setFillColor(sf::Color::Red);
			ball.move(moveSpeedX *= -1, moveSpeedY *= 1);
		}

		//now test for red player
		if (this->ball.getPosition().x + this->ball.getGlobalBounds().width >= leftr && (this->ball.getPosition().y >= topr && this->ball.getPosition().y <= topr + heightr)) {
			this->ball.setFillColor(sf::Color::Blue);
			ball.move(moveSpeedX *= 1, moveSpeedY *= 1);
		}
		//reverse if of this->ball.getPosition().y + this->ball.getGlobalBounds().height
		if (this->ball.getPosition().x + this->ball.getGlobalBounds().width >= leftr && (this->ball.getPosition().y + this->ball.getGlobalBounds().height >= topr && this->ball.getPosition().y + this->ball.getGlobalBounds().height <= topr + heightr)) {
			this->ball.setFillColor(sf::Color::Blue);
			ball.move(moveSpeedX *= -1, moveSpeedY *= -1);
		}

		//cout << ball.getPosition().x << endl;
		/*if (this->ball.getPosition().x <= p1.getPlayer().left + p1.getPlayer().width && (this->ball.getPosition().y >= p1.getPlayer().top) && this->ball.getPosition().y <= p1.getPlayer().top - p1.getPlayer().height) {
			this->ball.setFillColor(sf::Color::Red);
			ball.move(moveSpeedX *= -1, moveSpeedY *= 1);   && (this->ball.getPosition().y <= p1.getPlayer().top && this->ball.getPosition().y >= p1.getPlayer().top)
		}*/
		//if (this->ball.getPosition().x + this->ball.getGlobalBounds().width >= p2.getPlayer().left && this->ball.getPosition().y + this->ball.getGlobalBounds().height >= p2.getPlayer().top) {
		//	this->ball.setFillColor(sf::Color::Red);
		//	ball.move(moveSpeedX *= -1, moveSpeedY *= 1);
		//}

		//if (this->ball.getGlobalBounds().top <= 250.f) {
		//	this->ball.setFillColor(sf::Color::Red);
		//	ball.move(moveSpeedX *= 1, moveSpeedY *= -1);
		//}
		//else if (this->ball.getGlobalBounds().top + this->ball.getGlobalBounds().height >= 850.f) {
		//	this->ball.setFillColor(sf::Color::Blue);
		//	ball.move(moveSpeedX *= 1, moveSpeedY *= -1);
		//}
		////else if (this->ball.getGlobalBounds().left > player.getPlayer().left) {
		////	this->ball.setFillColor(sf::Color::Blue);
		////	ball.move(moveSpeedX *= 1, moveSpeedY *= -1);
		////}
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
		if (!this->score_font.loadFromFile("Fonts/Begok v15_2015.ttf")) {
			throw("Font can not be opened!");
		}
		if (!this->line_font.loadFromFile("Fonts/line.ttf")) {
			throw("Font can not be opened!");
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
	Player1 player1;
	Player2 player2;
	Ball ball;
	Scoreboard score;
	int score_blue_num;
	int score_red_num;
	bool win_condition;
	int win_score;
	sf::Font winTextFont;
	sf::Text winText;


	//Objects of the game
	WallsAndGates wallsAndGates;

	//Functions

	void initializeVars() {
		this->window = nullptr;
		this->score_blue_num = 0;
		this->score_red_num = 0;
		this->win_condition = false;
		this->win_score = 10;

	}

	void initializeWindow() {
		this->window = new sf::RenderWindow(sf::VideoMode(1400, 900), "Game Window", sf::Style::Titlebar | sf::Style::Close);
		this->window->setFramerateLimit(60);
	}

	void updateScore() {
		if (ball.checkIfScored() == 1) {
			this->score_red_num++;
		}
		else if (ball.checkIfScored() == 2) {
			this->score_blue_num++;
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

		if (!(this->score_blue_num < 11 && this->score_red_num < 11)) {
			this->win_condition = true;
		}

		//Checking win condition
		//!this->win_condition
		if (true) {
			//printing score
			this->updateScore();
			this->score.pritnScore(this->window, this->score_blue_num, this->score_red_num);

			this->wallsAndGates.printWallsAndGates(this->window);

			//test printing player
			this->player1.printPlayer(this->window);
			this->player2.printPlayer(this->window);

			cout << player1.getPlayer().top << endl;

			this->ball.printBall(this->window);
		}
		else {
			if (this->score_blue_num > 10) {
				this->blueWon();
			}
			else {
				this->redWon();
			}
		} 

		this->window->display();
	}

	//Updating Game
	void gameUpdate() {
		this->ball.checkIfScored();

		this->ball.checkCollisionBall(this->player1.getPlayer().top, this->player1.getPlayer().height, this->player1.getPlayer().left, this->player1.getPlayer().width, 
			this->player2.getPlayer().top, this->player2.getPlayer().height, this->player2.getPlayer().left, this->player2.getPlayer().width);

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