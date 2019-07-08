#include "Ship.h"
#include "Board.h"

using namespace std;
//towrzenie sekcji statku i jej przypisanie jej bezposrednio do Fielda
void Ship::buildShipSections()
{
	int i;

	if (_row1 == _row2) {
		if (_col1 < _col2) {
			for (i = _col1; i <= _col2; ++i) {
				_sections.push_back(&_board->getField(_row1, i));
			}
		}
		else {
			for (i = _col2; i <= _col1; ++i) {
				_sections.push_back(&_board->getField(_row1, i));
			}
		}
	}
	else {
		if (_row1 < _row2) {
			for (i = _row1; i <= _row2; ++i) {
				_sections.push_back(&_board->getField(i, _col1));
			}
		}
		else {
			for (i = _row2; i <= _row1; ++i) {
				_sections.push_back(&_board->getField(i, _col1));
			}
		}
	}
}


Ship::Ship(Board* board, int c1, int r1, int c2, int r2,int size) : 
	_size(size), _board(board),
	_col1(c1), _col2(c2), _row1(r1), _row2(r2)
{
	/*info = i;*/
	buildShipSections();
}
//kosntruktor bezargumentowy potrzebny z puntu zapisu do boardow
Ship::Ship():
	_board(nullptr)
{
}

//sprawdzanie przy wykorzystaniu iteratorow czy caly statek zatonal
bool Ship::IsSunk() 
{
	for (iterator_ship it = _sections.begin(); it != _sections.end(); ++it) {
		if ((*it)->GetShot() == false)
			return false;
	}
	return true;
}
//zwraca rozmiar statku
int Ship::getSize()
{
	return _size;
}
//zwraca rozmiar boarda (tablicy)
Board * Ship::getBoard()
{
	return _board;
}
//tutaj dodatkowo istotny zapis informacji o statkach (rozmiar, wspó³rzêdne)
void Ship::saveToFile(FILE * file) const
{
	fwrite(&_size, sizeof(int), 1, file);
	fwrite(&_col1, sizeof(int), 1, file);
	fwrite(&_col2, sizeof(int), 1, file);
	fwrite(&_row1, sizeof(int), 1, file);
	fwrite(&_row2, sizeof(int), 1, file);
}
//odczyt inoformacji o statkahc (rozmiar, wspó³rzêdne)
void Ship::readFromFile(FILE * file)
{
	fread(&_size, sizeof(int), 1, file);
	fread(&_col1, sizeof(int), 1, file);
	fread(&_col2, sizeof(int), 1, file);
	fread(&_row1, sizeof(int), 1, file);
	fread(&_row2, sizeof(int), 1, file);
}
// ustawianie przekaznego rozmiaru board do pola _board i tworzenie sekcji dla statkow
void Ship::setBoard(Board * board)
{
	_board = board;
	buildShipSections();
}
