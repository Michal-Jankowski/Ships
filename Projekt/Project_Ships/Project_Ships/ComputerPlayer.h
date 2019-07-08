#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "Player.h"
// Klasa dziedziczaca po Player
// Odpowiedzialna za logikê gry Komputera (m.in. strzelanie w pola na tablicy)
class ComputerPlayer :
	public Player
{
public:
	ComputerPlayer(Game* game);
	virtual bool Move(int& col, int& row, Board& board) override;
	virtual void SetUpName() override;
	//virtualna metoda zwracajaca typ gracza, 1 to komputer
	virtual int Type() override { return 1; }
	~ComputerPlayer();
};
#endif
