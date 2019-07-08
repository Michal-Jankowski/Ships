#ifndef FIELD_H
#define FIELD_H
#include "CheckTile.h"
//klasa dziedziczaca z CheckTile
//pobiera ona informacje o danym polu (wiersz, kolumna)
// ustawia odpowiednie stany _ship oraz _shot dla danego pola
class Field : public CheckTile  {
public:
	Field();
	Field(char column, char row); 

	void SetShot(bool value = true);
	void SetShip(bool value = true);
	bool GetShip()const;
	bool GetShot()const;
	bool IsSunk() const;

private:
	bool _ship;
	bool _shot;

};
#endif
