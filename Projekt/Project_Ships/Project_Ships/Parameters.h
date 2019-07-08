#ifndef PARAMETERS_H
#define PARAMETERS_H
#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>


//struktura pomocnicza do przekazywania informacji o dlugosci i liczbie statkow
//wykorzystywana do ustawiania wspolrzednych
struct ShipLength {
	unsigned length;
	unsigned amount;

	friend std::istream& operator>>(std::istream& is, ShipLength& coordinates);

};


//klasa odczytujaca i przekazujaca dane z argumentow wejsciowych do odpowiednich pol przy wykorzystaniu wektora
class Parameters
{

public:
	void ShipSizeFile();
	Parameters(int argc,char* argv[]);
	void CheckParam(std::vector<std::string> arguments);
	void InitalizeParam( char* argv[]);
	void Prompt_info();
	std::string GenerateFileName();
	void GetFileSize();
	
private:
	friend class Game;
	std::string  BoardSizeParam;
	std::string ShipSizeFileNameParam;
	std::string SaveFileNameParam;
	std::vector<std::string> arguments;
	std::string _LoadFileName;
	std::vector<ShipLength> shipLengths;
	void SetupDefaultShipLengths();
	size_t _argc;
	size_t _boardsize;

};
#endif
