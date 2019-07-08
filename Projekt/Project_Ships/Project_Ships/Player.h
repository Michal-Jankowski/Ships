#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>

class Board;
class Game;
//Klasa abstarkcyjna wykorzystywana do komuniakacji  z HumanPlayer i ComputerPlayer
//Umo¿liwia ³adny podzia³ klas 
class Player
{
protected:
	Game* game;
	std::string _name;
public:
	friend class HumanPlayer;
	virtual bool Move(int& col, int& row, Board& board) = 0; // wirtualna metoda na wykonanie ruchu gracza
	virtual void SetUpName() = 0; // wirtualna metoda na wpisanie imie gracza
	void SetName(std::string const& s);
	inline std::string GetName() const { return _name; }
	Player(Game* game);
	virtual int Type() = 0; //wirtualna metoda na typ gracza
	virtual ~Player();
};
#endif
