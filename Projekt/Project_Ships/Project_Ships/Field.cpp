#include "Field.h"
//konstrktor domyslny, nie ma informacji o polach
Field::Field() : _ship(false), _shot(false)
{
}
//konstruktor pobiera dane z CheckTile
Field::Field(char column, char row) : CheckTile(column,row),
	_ship(false),
	_shot(false)
{
}
//setter statku
void Field::SetShot(bool value) 
{
	_shot = value;
}
//setter strzalu
void Field::SetShip(bool value) 
{
	_ship = value;
}
//akcesor strzalu
bool Field::GetShot() const
{
	return _shot;
}
//sprawdza dwa stany, istotne przy zatopieniu statku
bool Field::IsSunk() const
{
	return _ship && _shot;
}
//ackesor statku
bool Field::GetShip() const
{
	return _ship;
}

