
#include "Board.h"
#include "Field.h"

using namespace std;

Board::Board(int size) :
	_size(size)
{
	for (int r = 0; r < size; ++r) {
		_shipGrid.push_back({});
		for (int c = 0; c < size; ++c) {
			_shipGrid[r].push_back(Field(c, r));
		}
	}
}

Field & Board::getField(int r, int c)
{
	return _shipGrid[r][c];
}

int Board::getSize()  const
{
	return _size;
}


void Board::markBoard(Ship& ship)
{
	for (Field* f : ship) {
		_shipGrid[f->GetRow()][f->GetCol()].SetShip();
	}
}

bool Board::validCoord(int row, int col) const
{
	return row >= 0 && row < _size && col >= 0 && col < _size;
}

void Board::addShip(Ship & s)
{
	for (Field* f : s) {
		_shipGrid[f->GetRow()][f->GetCol()].SetShip();
	}
	_ships.push_back(s);
}

void Board::operator+=(Ship & s)
{
	addShip(s);
}

bool Board::fleetSunk()
{
	for (Ship& s : _ships) {
		if (!s.IsSunk()) {
			return false;
		}
	}
	return true;
}

