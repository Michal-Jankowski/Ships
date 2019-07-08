#ifndef DISPLAY_INTERFACE_H
#define DISPLAY_INTERFACE_H
//klasa odpowiedzialna za wyswietlanie inforamcji o grze na konsoli
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

class Board;
//enum stanow wewnatrz namespaca ShipState
//okreœla wizualna reprezentacje pola zgodnie z okresolnym stanem w grze
namespace ShipState {
	enum _ShipState : char {
		Hit = 'X', Miss = '*', Water = '.', Ship = '#'
	};
}


class DisplayInterface
{
public:

	//iteratory dla latwiejszego przemieszczania sie po tablicy
	using display_iterator = std::vector<std::vector<std::string> >::iterator;
	using panel_iterator = std::vector<std::string>::iterator;
	
	DisplayInterface(int size, int gap = 2);

	void Clear();
	void placeBoardLeft(Board& board, bool hidden);
	void placeBoardRight(Board& board, bool hidden);
	
	friend std::ostream& operator<<(std::ostream& os, DisplayInterface const& di);

private:
	int _size;
	int _gap;
	std::vector<std::string> _panelLeft;
	std::vector<std::string> _panelRight;
	void initPanel(std::vector<std::string>& panel);
	void initPanels();
	void placeBoard(std::vector<std::string>& panel, Board& board, bool hidden);
	void DisplayHeader() const;
	void DisplayGap(int gap) const;
};
#endif