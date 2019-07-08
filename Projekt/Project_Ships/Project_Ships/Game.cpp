#include "Game.h"
#include "ComputerPlayer.h"

//aktualizacja gry i ustawianie aktualnego gracza (isotne ze wzgledu zapisu)
void Game::GameUpdate()
{
	_currentPlayer = p1;
	UpdateP1();
	if (_exitInfo == 1)
		return;
	_currentPlayer = p2;
	UpdateP2();
	if (_exitInfo == 1)
		return;
}
// rozpoczecie ca³ej gry
//informacje dla graczy o wstawianie statkow
void Game::Run()
{
	if ((parameters._LoadFileName.empty())||(parameters._LoadFileName == "empty")) {
		InitializePlayer();
		SetupBoard(p1, p1Board);
		std::cout << "Now ships place Player 2";//dodalem
		std::cin.get();//dodalem
		SetupBoard(p2, p2Board);
		while (!GameOver()) {
			GameUpdate();
		}
	}
	else {
		p1 = new HumanPlayer(this);
		p2 = new HumanPlayer(this);
		LoadGame();
		if (_currentPlayer == p1) {
			while (!GameOver()) {
				GameUpdate();
			}
		}
		else {
			while (!GameOver()) {
				_currentPlayer = p2;
				UpdateP2();
				if (_exitInfo == 1)
					return;
				_currentPlayer = p1;
				UpdateP1();
				if (_exitInfo == 1)
					return;
			}
		}
	}
	
	
}

//metoda wykonujaca proces aktualizacji dla pierwszego gracza
void Game::UpdateP1() {
	system("cls");//zmina
	std::cout << "P1 moves\n";
	std::cin.get();
	std::cin.clear();
	bool again = true;
	bool win = false;
	while (again) {
		again = false;
		int col, row;
		display.Clear();
		display.placeBoardLeft(p1Board, false);
		display.placeBoardRight(p2Board, true);
		std::cout << display;

		if (p1->Move(col, row, p2Board)) {
			if (p2Board[row][col].IsSunk()) {
				std::cout << p1->GetName() << " hit " << p2->GetName() << "\n";
				if (p2Board.fleetSunk()) {
					win = true;
					break;
				}
				else
					again = true;
			}
		}
		else if (_exitInfo == 1) {
			GameEnd();
			return;
		}
		else
			again = true;
	}
	if (win) {
		system("cls"); 
		std::cout << "Player " << p1->GetName() << " wins!!!";
		std::cin.get();
		std::cin.get();
		GameEnd();
	}
}
//metoda wykonujaca proces aktualizacji dla drugiego gracza
void Game::UpdateP2() {
	system("cls");//zmiana
	std::cout << "P2 moves\n";
	std::cin.get();
	std::cin.clear();
	bool again = true;
	bool win = false;
	while (again) {
		again = false;
		int col, row;
		display.Clear();
		display.placeBoardLeft(p2Board, false);
		display.placeBoardRight(p1Board, true);
		std::cout << display;

		if (p2->Move(col, row, p1Board)) {
			if (p1Board[row][col].IsSunk()) {
				std::cout << p2->GetName() << " hit " << p1->GetName() << "\n";
				if (p1Board.fleetSunk()) {
					win = true;
					break;
				}
				else
					again = true;
			}
		}
		else if (_exitInfo == 1) {
			GameEnd();
			return;
		}
		else
			again = true;
			
	}
	if (win) {
		std::cout << "Player " << p2->GetName() << " wins!!!";
		std::cin.get();
		std::cin.get();
		GameEnd();
	}
}


// zwraca koniec gry jako _finished
bool Game::GameOver() const
{
	return _finished;
}


//metoda odpowiedzialna za ca³y zapis gry, posiadajaca skladowe zapisujace poszczegolne informacje
void Game::SaveGame()
{
	std::string ValidFile = HumanPlayer::StaticValidateSaveFile;
	using namespace std;
	 SaveFile = ValidFile.c_str();

	if(ValidFile =="defsave")
		SaveFile = parameters.SaveFileNameParam.c_str();

	if (ValidFile == "exit") {
		SaveFile = parameters.SaveFileNameParam.c_str();
	}
	FILE* file = fopen(SaveFile, "wb");
	if (file == NULL)
		return;
	int size = p1Board.getSize();
	fwrite(&size, sizeof(int), 1, file);
	SaveBoard(p1Board, file);
	SaveBoard(p2Board, file);
	SaveShip(p1Board, file);
	SaveShip(p2Board, file);
	SavePlayer(p1, file);
	SavePlayer(p2, file);

		
	fclose(file);
	system("cls");
	std::cout << "Game saved!\n";
	if (ValidFile == "exit") {
		_exitInfo = 1;
		GameEnd();
		return;
		
	}
	std::cin.ignore(INT_MAX, '\n');
	

}

void Game::LoadGame()
{
	int size;
	const char * c = (parameters._LoadFileName).c_str();
	FILE* file = fopen(c, "rb");
	if (file == NULL)
		return;
	fread(&size, sizeof(int), 1, file);
	p1Board = Board(size);
	p2Board = Board(size);
	LoadBoard(p1Board, file);
	LoadBoard(p2Board, file);
	LoadShip(p1Board, file);
	LoadShip(p2Board, file);
	p1 = LoadPlayer(file);
	p2 = LoadPlayer(file);
	LoadCurrentPlayer(file);
	fclose(file);
}
// operator pomagajacy rozpoczecie gry
void Game::operator()()
{
	Run();
}
// zapis stanow tablicy do pliku binarnego
void Game::SaveBoard(Board & b, FILE * file)
{
	int size = b.getSize();
	for (int r = 0; r < size; ++r) {
		for (int c = 0; c < size; ++c) {
			Field f = b[r][c];
			fwrite(&f, sizeof(Field), 1, file);
		}
	}
}
// wczytywanie stanow tablicy z pliku binarnego
void Game::LoadBoard(Board & b, FILE * file)
{
	int size = b.getSize();
	for (int r = 0; r < size; ++r) {
		for (int c = 0; c < size; ++c) {
			fread(&b[r][c], sizeof(Field), 1, file);
		}
	}
}
// zapis informacje o graczy (imie) do pliku binarnego
void Game::SavePlayer(Player * p, FILE * file)
{
	int playerType = p->Type();
	fwrite(&playerType, sizeof(int), 1, file);
	SaveString(p->GetName(), file);
}
// wczytywanie informacje o graczu (imie) z pliku binarnego
Player* Game::LoadPlayer(FILE * file)
{
	int playerType;
	fread(&playerType, sizeof(int), 1, file);
	Player* p;
	if (playerType == 1)
		p = new ComputerPlayer(this);
	else
		p = new HumanPlayer(this);
	p->SetName(ReadString(file));
	return p;
}
//metoda pomocniacza do zapisu elementow w stringu do pliku binarnego
void Game::SaveString(std::string const & s, FILE * file)
{
	size_t size = s.size();
	fwrite(&size, sizeof(size_t), 1, file);
	fwrite(s.data(), size + 1, 1, file);
}
//zapis aktualnego gracza wykonujacego ruch do pliku binarnego

//odczyt stringa z pliku binarnego
std::string Game::ReadString(FILE * file)
{
	size_t size;
	fread(&size, sizeof(size_t), 1, file);
	char* s = new char[size];
	fread(s, size+1, 1, file);
	return std::string(s);
}

void Game::SaveCurrentPlayer(FILE * file)
{
	int playerNum;
	if (_currentPlayer == p1)
		playerNum = 1;
	else
		playerNum = 2;
	fwrite(&playerNum, sizeof(int), 1, file);
}
//odczyt aktualnego gracza wykonujacego ruch z pliku binarnego 
void Game::LoadCurrentPlayer(FILE * file)
{
	int playerNum;
	fread(&playerNum, sizeof(int), 1, file);
	if (playerNum == 1)
		_currentPlayer = p1;
	else
		_currentPlayer = p2;
}
// zapis ca³ej informacji o danym statku (dlugosc,wspolrzedne,ilosc statkow) do pliku binarnego
void Game::SaveShip(Board & b, FILE * file)
{
	size_t size = b.getShip().size();
	fwrite(&size, sizeof(size_t), 1, file);
	//pobieramy const& na vector<Ship> z boarda - nie wykonujemy kopiowania vectora
	//iterujemy pêtl¹ foreach, przy czym s jest w ka¿dej iteracji const& do statku z vectora - nie kopiujemy równie¿ zadnego statku
	//na const& mo¿emy wywo³aæ tylko metody z modyfikatorem const
	for (Ship const& s : b.getShip()) {
		s.saveToFile(file);
	}
}
// odczyt ca³ej informacji o danym statku (dlugosc,wspolrzedne,ilosc statkow) z pliku binarnego 
void Game::LoadShip(Board &b,  FILE * file) //bzdury
{
	size_t size;
	fread(&size, sizeof(size_t), 1, file);
	for (size_t i = 0; i < size; ++i) {
		Ship s;
		s.readFromFile(file);
		s.setBoard(&b);
		b.addShip(s);
	}
}




// metoda odpowiedzialna za ustawianie naszej tablicy z statkami, jest to rowniez metoda kolizyjna
void Game::SetupBoard(Player * player, Board & board) {
	//plansza okreslajaca wszystkie punkty "zajete" przez statek albo sasiadujace ze statkami gracza
	bool** collisions = allocBoolBoard(board.getSize());
	clearBoolBoard(collisions, board.getSize());
	//plansza okreslajaca wszystkie punkty "zajete" przez statek albo sasiadujace ze statkiem aktualnie wstawianym
	bool** shipCollisions = allocBoolBoard(board.getSize());
	//rozmiar planszy
	int size = board.getSize();
	std::cin.ignore(INT_MAX, '\n');
	//dla kazdego rozmiaru statku
	for (ShipLength shipLength : parameters.shipLengths) {
		int nShips = shipLength.amount;
		int shipSize = shipLength.length;
		display.Clear();
		for (int s = 0; s < nShips; ++s) {
			display.placeBoardLeft(board, false);//dodalem
			std::cout << display;// dodalem
			std::cout << "Player " << player->GetName() << " places ships\n"; // dodalem
			std::cout << "Ship " << (s + 1) << "\n"; // przesunalem z gory  byla na poczatku fora
			std::cout << "Place " << nShips << " ships of length " << shipSize << " \n"; //dodalem
			int row1, col1, row2, col2;
			while (true) {
				//wczytaj koordynaty pozycji poczatkowej i koncowej statku
				HumanPlayer::GetCoord(row1, col1, board);
				if (shipSize > 1)
					HumanPlayer::GetCoord(row2, col2, board);
				else {
					row2 = row1;
					col2 = col1;
				}
				//jesli ktorykolwiek indeks wychodzi poza plansze
				if (row1 < 0 || row1 >= size || row2 < 0 || row2 >= size || col1 < 0 || col1 >= size || col2 < 0 || col2 >= size) {
					std::cout << "Illegal coordinates\n";
					continue;
				}

				//w dalszej czesci zakladamy ze poczatek (ro1,col1) jest mniejszy niz koniec (ro2,col2)
				if (row1 > row2)
					std::swap(row1, row2);
				if (col1 > col2)
					std::swap(col1, col2);

				//jesli sa w jednym rzedzie
				if (row1 == row2) {
					//liczymy dlugosc, ma sie zgadzac z rozmiarem aktualnie wstawianego statku
					if ((abs(col2 - col1 + 1)) != shipSize) {
						std::cout << "Wrong ship length\n";
						continue;
					}
				}
				//jesli sa w jednej kolumnie
				else if (col1 == col2) {
					//liczymy dlugosc, ma sie zgadzac z rozmiarem aktualnie wstawianego statku
					if ((abs(row2 - row1 + 1)) != shipSize) {
						std::cout << "Wrong ship length\n";
						continue;
					}
				}
				else {
					std::cout << "Ship is not in line\n";
					continue;
				}

				//tworzymy statek ktory automatycznie pobierze sobie pola z planszy na podstawie koordynatow
				Ship ship(&board, col1, row1, col2, row2, shipSize);
				//czyscimy tablice punktow kolizji statku
				clearBoolBoard(shipCollisions, size);

				//flaga okreslajaca wykrycie kolizji
				bool detected = false;
				//dla kazdego pola ktore zajmuje statek
				for (Field* f : ship) {
					//pobieramy rzad i kolumne pola
					int fr = f->GetRow();
					int fc = f->GetCol();
					if (collisions[fr][fc]) {
						if (detected) {
							std::cout << ", " << char((char)fc + 'A') << fr;
						}
						else {
							detected = true;
							std::cout << "Collision detected at: " << char((char)fc + 'A') << fr;
						}
					}
					else {
						//wyliczamy min i max sasiada w poziomie i w pionie
						int minr = std::max(0, fr - 1);
						int maxr = std::min(size - 1, fr + 1);
						int minc = std::max(0, fc - 1);
						int maxc = std::min(size - 1, fc + 1);
						//dla kazdej kolumny kwadratu 3x3 (jesli wyszlismy poza plansze to mniejszy) z sasiadami
						for (int c = minc; c <= maxc; ++c) {
							//i dla kazdego rzedu
							for (int r = minr; r <= maxr; ++r) {
								//ustawiamy punkt kolizji dla aktualnego statku
								shipCollisions[r][c] = true;
							}
						}
					}
				}
				//jesli nie byla wykryta kolizja
				if (!detected) {
					//kopiujemy wszystkie pola kolizji z tymczasowej tablicy dla wstawianego statku do ogólnej
					for (int c = 0; c < size; ++c) {
						for (int r = 0; r < size; ++r) {
							if (shipCollisions[r][c] == true)
								collisions[r][c] = true;
						}
					}
					//ustawiamy na planszy na wszystkich polach nazezachych do statku informacje o tym ze stoi na nich statek					
					board += ship;
				}
				else { //byla kolizja
					std::cout << "\n";
					continue;
				}
				system("cls");
				std::cout << "Ship placed successfully" << std::endl;
				//konczymy petle bo ma warunek (true)
				break;
			}
		}
	}
	deallocBoolBoard(shipCollisions, size);
	deallocBoolBoard(collisions, size);
}
//metoda incjalizujaca gracza, pelni rowniez funkcje komunikacji z graczem
void Game::InitializePlayer()
{
	StartInfo();

	std::cout << " Choose player 1 :\n  For COMPUTER insert 1  For PLAYER insert 2 (max 20 characters)\n";
	while (true) {
		if (InitializeOpponent())
			break;
	}
	if (_opponent == 1) { // zmiana metody
		p1 = new ComputerPlayer(this);
		
		std::cout << " Choose player 2 :\n  For COMPUTER insert 1  For PLAYER insert 2 (max 20 characters)\n";

		while (true) {
			if (InitializeOpponent())
				break;
		}
		if (_opponent == 1) {
			p2 = new ComputerPlayer(this); 
		}
		else if (_opponent == 2) {
			p2 = new HumanPlayer(this);
		}
		else {
			std::cout << "Wrong, please try again \n";
		}

	}
	else if (_opponent == 2) {
		p1 = new HumanPlayer(this);
	
		std::cout << " Choose player 2 :\n  For COMPUTER insert 1  For PLAYER insert 2 (max 20 characters)\n";
		
		while (true){
			if (InitializeOpponent())
				break;
		}

		if (_opponent == 2) {
			p2 = new HumanPlayer(this);
		}
		else if (_opponent == 1) {
			p2 = new ComputerPlayer(this);
		}
		else {
			std::cout << "Wrong, please try again \n";
		}
	}
	p1->SetUpName();
	p2->SetUpName();
	system("cls");
}
//metoda pomocniacza do InitalizePlayer() wczytujaca dane od uzytkownika
//zabezpiecza przed b³êdnie wprowadzonymi danymi
bool Game::InitializeOpponent()
{
	char answer[20];
	int i = 0;
	std::cin >> answer;
	for (; answer[i] != '\0'; i++)
	{
		if (isalpha(answer[i]) !=0 || i==1) {
			std::cout << "Incorrect value \n";
			return false;
		}
	}
	if (answer[0] == '1'|| answer[0] == '2') {
		_opponent = int(answer[0])-48;
		return true;
	}
	else
		std::cout<< "Incorrect integer \n";
	return false;
}
//powitanie dla u¿ytkownika
void Game::StartInfo()
{
	std::cout << "WELCOME TO THE BATTLE SHIP!!!" << std::endl;
}

//alokowanie tablicy kolizji
bool ** Game::allocBoolBoard(size_t size)
{
	bool**connections = new bool*[size];
	for (size_t i = 0; i < size; ++i) {
		connections[i] = new bool[size];
	}
	return connections;
}
//dealokacja tablicy kolizji
void Game::deallocBoolBoard(bool** board, size_t size)
{
	for (size_t i = 0; i < size; ++i) {

		delete[] board[i];
	}
	delete[] board;
}
//czyszczenie tablicy kolizji (domyslnie false)
void Game::clearBoolBoard(bool ** board, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = 0; j < size; ++j)
			board[i][j] = false;
	}	
}
//zwracanie informacji o koncu gry
void Game::GameEnd()
{
	_finished = true;
}
//alokowanie informacji o grze poprzez wykorzystanie danych z klasy Parameters
Game::Game(Parameters params) :
	display(stoi(parameters.BoardSizeParam)),
	parameters(params),
	p1Board(stoi(parameters.BoardSizeParam)),
	p2Board(stoi(parameters.BoardSizeParam)),
	_finished(false)

{
	
}
//dealokacja graczy
Game::~Game()
{
	delete p1;
	delete p2;
}



