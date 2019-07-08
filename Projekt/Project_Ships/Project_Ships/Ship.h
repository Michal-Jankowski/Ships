#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <vector>

class Field;
class Board;
//Klasa wykorzysytwana do przechowywania konkretnie wyszstkich inforamcji o statkach
//wykorzystuje do tego m.in. wektor _sections
class Ship 
{
public:
	
	using iterator_ship = std::vector < Field *>::iterator; // iterator po Field* vectorach

	Ship( Board* board, int column1, int row1, int column2, int row2, int size);
	Ship();

	auto begin() { // zwraca  1 element w wektorze
		return _sections.begin();
	}

	auto end() { // zwraca  ostatni element w wektorze
		return _sections.end();
	}
	// mo¿na w taki sposób utworzyæ pêtle foreach
	bool IsSunk();
	int getSize();
	Board* getBoard();
	
	void saveToFile(FILE* file) const;
	void readFromFile(FILE* file);
	void setBoard(Board* board);

private:
	std::vector<Field*> _sections; // chcemy sie odwolywac bezposrednio do pol klasy Field, aby móc je od razu modyfikowaæ
	//bezsensowne jest robienie na ich kopiach, a potem ponowne przypisywanie tych kopii do aktualnych danych
	int _size, _col1, _col2, _row1, _row2;
	Board* _board;
	void buildShipSections();
};
#endif

