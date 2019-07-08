#include "CheckTile.h"

//konstruktor bezargumentowy 
CheckTile::CheckTile(): _column(0),_row(0)
{
}
//Akcesor kolumny
char CheckTile::GetCol() const
{
	return _column;
}
//Akcesor wiersz
char CheckTile::GetRow() const
{
	return _row;
}




