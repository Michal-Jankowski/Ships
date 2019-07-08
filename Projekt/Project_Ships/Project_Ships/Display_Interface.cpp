#include "Display_Interface.h"
#include "Board.h"

//konstruktor inicjujacy informacje o tablicy
DisplayInterface::DisplayInterface(int size, int gap) :
	_size(size),
	_gap(gap)
{
	initPanels();
}
//czyszczenie stringa (usuwa elementy stringa i ustawia rozmiar 0) dla
//gracza lub komputera oraz przeciwnika i ich ponowna inicjalizacja
void DisplayInterface::Clear()
{
	_panelLeft.clear();
	_panelRight.clear();
	initPanels();
}
// wyswietla informacje o planszy przeciwnika po lewej bez ujawniania jego statkow (parametr hidden)
void DisplayInterface::placeBoardLeft(Board & board, bool hidden)
{
	placeBoard(_panelLeft, board, hidden);
}
// wyswietla informacje o planszy przeciwnika po prawej bez ujawniania jego statkow (parametr hidden)
void DisplayInterface::placeBoardRight(Board & board, bool hidden)
{
	placeBoard(_panelRight, board, hidden);
}
// tworzenie pustego stringa wypelnionego stanami "woda" w celu poznijegszego ³atwiejszego uzupe³nienia statkami
void DisplayInterface::initPanel(std::vector<std::string>& panel)
{
	panel.reserve(_size);
	for (int i = 0; i < _size; ++i) {

		panel.push_back(std::string(_size, ShipState::Water)); // string ' ' * szerokosc
	}
}
//inicjalizacja panelu lewego i prawego korzystajac z metody initPanel
void DisplayInterface::initPanels()
{
	initPanel(_panelLeft);
	initPanel(_panelRight);
}
//metoda odpowiedzialna za wstawianie na tablicy (stringa vectorow) statków informacji o danym polu
void DisplayInterface::placeBoard(std::vector<std::string>& panel, Board & board, bool hidden)
{
	for (int r = 0; r <  _size; ++r) {
		for (int c = 0; c < _size; ++c) {
			Field f = board[r][c];
			if (f.GetShot()) {
				if (f.GetShip()) {
					panel[r][c] = ShipState::Hit;
				}
				else {
					panel[r][c] = ShipState::Miss;
				}
			}
			else {
				if (f.GetShip()) {
					if (hidden) {
						panel[r][c] = ShipState::Water;
					}
					else {
						panel[r][c] = ShipState::Ship;
					}
				}
				else {
					panel[r][c] = ShipState::Water;
				}
			}
		}
	}
}
//wyswietlanie wspolrzednych poziomych
void DisplayInterface::DisplayHeader() const
{
	std::cout << "    ";
	for (char letter = 'A'; letter < 'A' + _size; ++letter) {
		std::cout << letter;
	}
	DisplayGap(_gap + 4); //przerwa pomiedzy wyswietlaniem ' '
	for (char letter = 'A'; letter < 'A' + _size; ++letter) {
		std::cout << letter;
	}
}
//przerwa pomiedzy dwiema tablicami wykorzystywana jest w operatorze<<
void DisplayInterface::DisplayGap(int gap) const
{
	for (int i = 0; i < gap; ++i)
		std::cout << ' ';
}
//operator strumieniowy <<
//jego zadaniem jest oddzielenie jednej tablicy od siebie
//zachowujac jednoczesnie odpowiednie zaleznosci pomiedzy nimi
//wykorzystana jest metoda DisplayGap oraz std::setw()
//zachowuja one odpowiednie proporcje, umozliwia to przejrzyste wyswietlanie informacji
std::ostream & operator<<(std::ostream & os, DisplayInterface const & di)
{
	di.DisplayHeader();
	os << std::endl;
	for (int r = 0; r < di._size; ++r) { // wyswietlanie ->"lewypanel przerwa prawy panel"
		os << std::setw(3) << std::right << r << " ";
		os << di._panelLeft[r];
		di.DisplayGap(di._gap);
		os << std::setw(3) << std::right << r << " ";
		os << di._panelRight[r] << std::endl;
	}
	return os;
}
