#ifndef CHECKTILE_H
#define CHECKTILE_H
//klasa odpowiedzialna za przechowywanie inforamacji o polu na tablicy statk�w
//konkretne informacje o wierszu i kolumnie
class CheckTile
{
public:
	CheckTile();
	CheckTile(char column, char row) : _column(column), _row(row) { }
	char GetCol() const;
	char GetRow() const;
private:
	char _row, _column;

};
#endif