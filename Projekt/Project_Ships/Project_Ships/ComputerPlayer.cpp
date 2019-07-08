#include "ComputerPlayer.h"
#include "Board.h"


//tworzenie losowej wartosci w konstruktorze do poruszania sie
ComputerPlayer::ComputerPlayer(Game * game):
	Player(game)
{
	srand((unsigned)time(nullptr));
}
//poruszanie sie po planszy komputera
bool ComputerPlayer::Move(int & col, int & row, Board & board)
{
	col = rand()%board.getSize();
	row = rand()%board.getSize();
	while (board[row][col].GetShot()) {
		col = rand() % board.getSize();
		row = rand() % board.getSize();
	}
	board[row][col].SetShot();
	return true;
}
//nazwa komputera
void ComputerPlayer::SetUpName()
{
	_name = "Computer";
}

ComputerPlayer::~ComputerPlayer()
{
}

