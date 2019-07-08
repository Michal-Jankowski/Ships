#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include <iostream>
#include <string>
#include "Board.h"
#include "Player.h"

//klasa dziedziczaca z klasy Player
//odpowiedzialna za tworzenie u¿ytkownika jako gracza
class Game;

class HumanPlayer: public Player
{
	

public:
	static std::string StaticValidateSaveFile;
	HumanPlayer(Game* game); 
    ~HumanPlayer();
	friend class Player;
	virtual bool Move(int& col, int& row, Board& board) override; // metoda wirtualna do wykonywania ruchu
	virtual void SetUpName() override;
	static bool GetCoord(int& row, int& col, Board& board, std::string const& line);
	static bool GetCoord(int& row, int& col, Board& board);
	//metoda wirtualna zwraca informacje o typie gracza 2 to u¿ytkownik
	virtual int Type() override { return 2; }
private:
 static int ColIndex(char colLetter);
 bool validateCommand(std::string const& line, Game *game);
 
 
};
#endif
