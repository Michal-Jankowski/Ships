#ifndef GAME_H
#define GAME_H
//klasa odpowiedzalna za inicjalizowanie gry
//mastêpuje tutaj równie przekazanie argumentow z wiersza polecen do klasy Parameters
//jednoczeœnie odbywa siê tutaj ci¹g³a aktualizacja gry po ka¿dym ruchu gracza
//wystêpuje tutaj równie¿ jenda z istotniejszych metod: metoda kolizyjna statków
//w zwi¹zku z przekazywaniem tutaj istotnych informacji o grze nastêpuje tutaj równie¿ zapis i odczyt gry
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "HumanPlayer.h"
#include "Parameters.h"
class Game
{

public:
	bool GameOver() const;
	Game(Parameters params);
	~Game();
	void UpdateP1();
	void UpdateP2();
	void GameUpdate();
	void SaveGame();
	void LoadGame();
	void operator()(); 
private:
	void Run();
	void SaveBoard(Board& b, FILE* file);
	void LoadBoard(Board& b, FILE* file);
	void SavePlayer(Player* p, FILE* file);
	Player* LoadPlayer(FILE* file);
	void SaveString(std::string const& s, FILE* file);
	void SaveCurrentPlayer(FILE* file);
	void LoadCurrentPlayer(FILE* file);
	void SaveShip( Board& b,FILE * file);
	void LoadShip(Board& b, FILE * file);
	void SetupBoard(Player* player, Board& board);
	void InitializePlayer();
	bool InitializeOpponent(); //zmiana
	void StartInfo();
	std::string ReadString(FILE* file);
	static bool** allocBoolBoard(size_t size);
	static void deallocBoolBoard(bool** board, size_t size);
	static void clearBoolBoard(bool** board, size_t size);

	void GameEnd();
	Parameters parameters;
	DisplayInterface display;
	Board p1Board, p2Board;
	Player* p1, *p2; // dla 2 graczy
	Player* _currentPlayer;// aktualny gracz
	bool _finished;
	bool _win = false;
	unsigned _opponent;
	unsigned _exitInfo = 0;
	const char * SaveFile;
};
#endif
