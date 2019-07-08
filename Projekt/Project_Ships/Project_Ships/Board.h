#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include "Field.h"
#include "Ship.h"
#include "Display_Interface.h"

class Board {
	//klasa pomocnicza zapamietujaca odwolania do vectora fieldow
	//daje nam mozliwosc odwolania sie do elementu vectora ale nie daje mozliwosci modyfikacji vetora
	class ShipGridRef {
		std::vector<Field>& ref;
	public:
		//posrednik
		inline ShipGridRef(std::vector<Field>& ref) :
			ref(ref)
		{}

		//operator pobierajacy element z vectora na podanym indeksie
		inline Field& operator[](int col) {
			return ref[col];
		}
	};

public:

	Board(int size);
	bool fleetSunk();
	Field& getField(int r, int c);
	int getSize()const;
	bool validCoord(int row, int col) const;
	void addShip(Ship& s);
	void operator+=(Ship& s);
	const std::vector<Ship>& getShip() { return _ships; }

	//operator zwracajacy obiekt-posrednik
	//moglby zwrocic vector<Field>& na pozycji row w shipGrid ale to daloby nam mozliwosc
	//modyfikacji tego vectora a tego chcemy uniknac
	inline ShipGridRef operator[](int row) {
		return ShipGridRef(_shipGrid[row]);
	}
private:
	void markBoard(Ship&);
	std::vector<Ship> _ships;
	int _size;
	std::vector<std::vector<Field>> _shipGrid;

	
};

#endif 
