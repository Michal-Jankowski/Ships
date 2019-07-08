#include "HumanPlayer.h"
#include "Game.h"
// zwraca odpowiednia litere, niezaleznie czy jest z wielkiej czy z malej
// w innym przypadku -1
int HumanPlayer::ColIndex(char colLetter)
{
	if (islower(colLetter))
		return colLetter - 'a';
	else if (isupper(colLetter))
		return colLetter - 'A';
	else
		return -1;
}
//interfejs komunikacji z graczem
//tutaj odbywa siê mo¿liwoœæ zapisu w trakcie gry
bool HumanPlayer::validateCommand(std::string const & line, Game *game)
{
	//zapis z mozliwoscia wyboru nazwy
	if (line == "save") {
		std::cout << "Type name file to save your progress \n";
		std::cin >> StaticValidateSaveFile;
		game->SaveGame();
		return true;
	}// zapis wychodzacy z gry wykorzystujacy aktualna date do zapisu
	else if (line == "exit") {
		StaticValidateSaveFile = "exit";
		game->SaveGame();
		return true;
	}// zapis  domyslny wykorzystujacy aktualna date od zapisu
	else if (line == "defsave") {
		StaticValidateSaveFile = "defsave";
		game->SaveGame();
		return true;
	}
	else
	return false;
}
//konstruktor tworzacy u¿ytkownika
HumanPlayer::HumanPlayer(Game* game):
	Player(game)
{
}
//destruktor wirtualny
HumanPlayer::~HumanPlayer()
{
}

//sprawdzanie poprawnosci ruchu gracza, nieaktualna nie korzystamy, poniewa¿ mamy do tego metode kolizyjna
bool HumanPlayer::Move(int& col, int& row, Board & board)
{
	std::string line;
	std::cout << ">> ";
	std::getline(std::cin, line);
	if (!validateCommand(line, game)) {
		if (GetCoord(row, col, board, line)) {
			board[row][col].SetShot();
			return true;
		}
	}
	return false;
}
// pytanie o nazwe uzytkownika
void HumanPlayer::SetUpName()
{
	do {
		std::cout << "Welcome To Battle Ship Game! What is your name  (max 20 chars)?: ";
		std::cin >>_name;
	} while (_name.length() > 20);
}
// pobiera wspolrzedne od uzytkownika ktore sa sprawdzane pod wzglêdem ich poprawnoœci
bool HumanPlayer::GetCoord(int & row, int & col, Board & board, std::string const & line)
{
	if (line.size() < 2)
		return false;
	char colLetter = line.front();
	if (colLetter > 0 && isupper(colLetter))
		col = colLetter - 'A';
	else if (colLetter > 0 && islower(colLetter))
		col = colLetter - 'a';
	else
		return false;
	size_t i = 1;
	while (i < line.size() && line[i] > 0 && isdigit(line[i]))
		++i;
	if (i < line.size())
		return false;
	try {
		row = std::stoi(line.substr(1));
	}
	catch (...) {
		return false;
	}
	if (board.validCoord(row, col)) {
		return true;
	}
	return false;
}

//wykorzystywana do sprawdzenia wprowadzonych danych w metodzie kolizyjnej
bool HumanPlayer::GetCoord(int & row, int & col, Board & board)
{//zaakomentowane niektore komunikaty o zle wprowadzonych danych, poniewaz gra staje sie mniej przejrzysta
	while (true) {
		std::string line;

		std::cout << "Enter coordinates: ";
		if (!std::getline(std::cin, line)) {
			//std::cout << "Wrong coordinates: ";
			continue;
		}
		if (line.size() < 2) {
			//std::cout << "Wrong coordinates: \n";
			continue;
		}
		char colLetter = line.front();
		if (colLetter > 0 && isupper(colLetter))
			col = colLetter - 'A';
		else if (colLetter > 0 && islower(colLetter))
			col = colLetter - 'a';
		else {
		//	std::cout << "Wrong coordinates: ";
			continue;
		}
		size_t i = 1;
		while (i < line.size() && line[i] > 0 && isdigit(line[i]))
			++i;
		if (i < line.size()) {
			//std::cout << "Wrong coordinates: ";
			continue;
		}
		try {
			row = std::stoi(line.substr(1));
		}
		catch (...) {
			//std::cout << "Wrong coordinates: ";
			continue;
		}
		if (board.validCoord(row, col)) {
			return true;
		}
	}
	return false;
	
}
std::string HumanPlayer::StaticValidateSaveFile; // zmienna statyczna przekazywana do Game wykorzystywana przy zapisie
