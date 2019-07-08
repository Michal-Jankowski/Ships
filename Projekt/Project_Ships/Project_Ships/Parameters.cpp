
#include "Parameters.h"
#include <Windows.h>
//generacja domyslnej nazwy dla pliku
std::string Parameters::GenerateFileName() {

	SYSTEMTIME time;
	GetLocalTime(&time);
	return "gra_" + std::to_string(time.wYear) + "_" + std::to_string(time.wMonth) + "_" + std::to_string(time.wDay);

}
// odczyt nazwy pliku, istotny gdy gra byla juz wczesniej zapisna
void Parameters::GetFileSize()
{
	const char * c = (_LoadFileName).c_str();
	char buffer[] = " ";
	FILE *ptr = fopen(c, "rb");
	if (ptr == NULL) {
		SetupDefaultShipLengths();
		Prompt_info();
		_LoadFileName = "empty";
		return;
	}
	fread(&buffer, sizeof(buffer), 1, ptr);
	std::string _LoadFileName(buffer);
	fclose(ptr);
}
//pobiera z pliku informacje o statkach w innym przpadku inicjalizacja domyslna iloscia statkow
void Parameters::ShipSizeFile()
{
	if (!_LoadFileName.empty())// nie ma statkow
		return;
	if (ShipSizeFileNameParam.empty()) { //dodatkowy warunek dla bezpieczenstwa
		//domyslne wartosci
		SetupDefaultShipLengths();
		return;
	}
	std::ifstream File(ShipSizeFileNameParam); // wykorzystano back-inserter do oczytania zawartosci z pliku do struktury ShipLenghts
	if (File) {
		std::copy(std::istream_iterator<ShipLength>(File), //kopiowanie zawartosci z pliku
			std::istream_iterator<ShipLength>(),// iteracja po ShipLenghts 
			std::back_inserter(shipLengths)); //wsadzanie do shipLengths inforamcji o ilosci i dlugosci statkow
	}
	else {
		std::cerr << "Couldn't open " << ShipSizeFileNameParam << " for reading\n"; // jezeli plik istnieje a nie udalo sie utworzc
		SetupDefaultShipLengths();
	}
	

}
//konstruktor przekazujacy parametry do metod sprawdzajacych dane
Parameters::Parameters(int argc, char*argv[]):_argc(argc)
{
	InitalizeParam(argv);
	GenerateFileName();
	CheckParam(arguments);
	ShipSizeFile();
}

//podzial parametrow na rozmiar oraz wykorzystanie domyslnych danych(parametrow)
void Parameters::CheckParam(std::vector<std::string> arguments)
{
	if ((arguments).size() > 7 || (arguments).size() == 1||arguments.size() == 3||arguments.size() == 5)
	{

		_LoadFileName = "";
		ShipSizeFileNameParam = "";
		SaveFileNameParam = GenerateFileName();
		BoardSizeParam = "10";
		std::cout << "Wrong number of parameters" << std::endl;
		return;
	}

	
	_LoadFileName = "";
	ShipSizeFileNameParam = "";
	SaveFileNameParam = GenerateFileName();
	BoardSizeParam = "10";

	if ((arguments).size() == 2)
	{
		if (arguments[0] == "-in")
		{
			_LoadFileName = arguments[1];
			GetFileSize();
			return;
		}

	    if (arguments[0] == "-innum")
		{
			ShipSizeFileNameParam = arguments[1];
		}

		else if (arguments[0] == "-n") {
			BoardSizeParam = arguments[1];
		}
		else if (arguments[0] == "-out") {
			SaveFileNameParam = arguments[1];
		}
		else
			Prompt_info();
	}
	if ((arguments).size() == 4)

	{
		if (arguments[0] == "-in")
		{
			_LoadFileName = arguments[1];
			GetFileSize();
			return;
		}

		else if (arguments[0] == "-innum")
		{
			ShipSizeFileNameParam = arguments[1];
		}

		else if (arguments[0] == "-n") {
			BoardSizeParam = arguments[1];
		}
		else if (arguments[0] == "-out") {
			SaveFileNameParam = arguments[1];
		}
		else if (arguments[2] == "-innum")
		{
			ShipSizeFileNameParam = arguments[3];
		}

		else if (arguments[2] == "-n") {
			BoardSizeParam = arguments[3];
		}
		else if (arguments[2] == "-out") {
			SaveFileNameParam = arguments[3];
		}
		else if (arguments[0] == "-innum" && arguments[2] == "-out") {
			ShipSizeFileNameParam = arguments[1];
			SaveFileNameParam = arguments[3];
			
		}
		else if (arguments[2] == "-innum" && arguments[0] == "-out") {

			ShipSizeFileNameParam = arguments[3];
			SaveFileNameParam = arguments[1];
		
		}

		else if (arguments[0] == "-innum" && arguments[2] == "-n") {
			ShipSizeFileNameParam = arguments[1];
			BoardSizeParam = arguments[3];
			
		}
		else if (arguments[2] == "-innum" && arguments[0] == "-n") {
			ShipSizeFileNameParam = arguments[3];
			BoardSizeParam = arguments[1];

		}

		else if (arguments[0] == "-n" && arguments[2] == "-out") {
			BoardSizeParam = arguments[1];
			SaveFileNameParam = arguments[3];
		}

		else if (arguments[2] == "-n" && arguments[0] == "-out") {
			BoardSizeParam = arguments[3];
			SaveFileNameParam = arguments[1];
		}
		else
			Prompt_info();

	}
	if (arguments.size() == 6) {

		if (arguments[0] == "-in")
		{
			_LoadFileName = arguments[1];
			GetFileSize();
			return;
		}

		else if (arguments[0] == "-innum")
		{
			ShipSizeFileNameParam = arguments[1];
		}

		else if (arguments[0] == "-n") {
			BoardSizeParam = arguments[1];
		}
		else if (arguments[0] == "-out") {
			SaveFileNameParam = arguments[1];
		}
		else if (arguments[2] == "-innum")
		{
			ShipSizeFileNameParam = arguments[3];
		}

		else if (arguments[2] == "-n") {
			BoardSizeParam = arguments[3];
		}
		else if (arguments[2] == "-out") {
			SaveFileNameParam = arguments[3];
		}
		else if (arguments[4] == "-innum")
		{
			ShipSizeFileNameParam = arguments[5];
		}

		else if (arguments[4] == "-n") {
			BoardSizeParam = arguments[5];
		}
		else if (arguments[4] == "-out") {
			SaveFileNameParam = arguments[5];
		}
		else if (arguments[0] == "-innum" && arguments[2] == "-out") {
			ShipSizeFileNameParam = arguments[1];
			SaveFileNameParam = arguments[3];

		}
		else if (arguments[2] == "-innum" && arguments[0] == "-out") {

			ShipSizeFileNameParam = arguments[3];
			SaveFileNameParam = arguments[1];

		}

		else if (arguments[0] == "-innum" && arguments[2] == "-n") {
			ShipSizeFileNameParam = arguments[1];
			BoardSizeParam = arguments[3];

		}
		else if (arguments[2] == "-innum" && arguments[0] == "-n") {
			ShipSizeFileNameParam = arguments[3];
			BoardSizeParam = arguments[1];

		}

		else if (arguments[0] == "-n" && arguments[2] == "-out") {
			BoardSizeParam = arguments[1];
			SaveFileNameParam = arguments[3];
		}

		else if (arguments[2] == "-n" && arguments[0] == "-out") {
			BoardSizeParam = arguments[3];
			SaveFileNameParam = arguments[1];
		}
		///
		else if (arguments[0] == "-innum" && arguments[4] == "-out") {
			ShipSizeFileNameParam = arguments[1];
			SaveFileNameParam = arguments[5];

		}
		else if (arguments[4] == "-innum" && arguments[0] == "-out") {

			ShipSizeFileNameParam = arguments[5];
			SaveFileNameParam = arguments[1];

		}

		else if (arguments[0] == "-innum" && arguments[4] == "-n") {
			ShipSizeFileNameParam = arguments[1];
			BoardSizeParam = arguments[5];

		}
		else if (arguments[4] == "-innum" && arguments[0] == "-n") {
			ShipSizeFileNameParam = arguments[5];
			BoardSizeParam = arguments[1];

		}

		else if (arguments[0] == "-n" && arguments[4] == "-out") {
			BoardSizeParam = arguments[1];
			SaveFileNameParam = arguments[5];
		}

		else if (arguments[4] == "-n" && arguments[0] == "-out") {
			BoardSizeParam = arguments[5];
			SaveFileNameParam = arguments[1];
		}
		if (arguments[0] == "-innum" && arguments[2] == "-n" && arguments[4] == "-out") {
			ShipSizeFileNameParam = arguments[1];
			BoardSizeParam = arguments[3];
			SaveFileNameParam = arguments[5];
		}
		else if (arguments[0] == "-innum" && arguments[2] == "-out" && arguments[4] == "-n") {
			ShipSizeFileNameParam = arguments[1];
			BoardSizeParam = arguments[5];
			SaveFileNameParam = arguments[3];
		}
		else if (arguments[0] == "-n" && arguments[2] == "-out" && arguments[4] == "-innum") {
			ShipSizeFileNameParam = arguments[5];
			BoardSizeParam = arguments[1];
			SaveFileNameParam = arguments[3];
		}
		else if (arguments[0] == "-n" && arguments[2] == "-innum" && arguments[4] == "-out") {
			ShipSizeFileNameParam = arguments[3];
			BoardSizeParam = arguments[1];
			SaveFileNameParam = arguments[5];
		}
		else if (arguments[0] == "-out" && arguments[2] == "-innum" && arguments[4] == "-n") {
			ShipSizeFileNameParam = arguments[3];
			BoardSizeParam = arguments[5];
			SaveFileNameParam = arguments[1];
		}
		else if (arguments[0] == "-out" && arguments[2] == "-n" && arguments[4] == "-innum") {
			ShipSizeFileNameParam = arguments[5];
			BoardSizeParam = arguments[3];
			SaveFileNameParam = arguments[1];
		}
		else
			Prompt_info();
	}
	
}
//przekazanie argumentow z tablicy argv do wektora
void Parameters::InitalizeParam(char*argv[])
{
	for (size_t i = 1; i < _argc; ++i) { // parametry

			arguments.push_back(argv[i]); 
	}
}




//wypisuje informacje o czesciowej poprawnosci parameterow
void Parameters::Prompt_info()
{
	std::cout << "Some parameters may be wrong!"; 
}
//domyslne statki
void Parameters::SetupDefaultShipLengths()
{
	shipLengths.push_back({ 1,1 });
	shipLengths.push_back({ 4,2 });
}

//operator strumieniowy >> wykorzystywany przy przekazywaniu danych do struktury ShipLenght
std::istream & operator>>(std::istream & is, ShipLength& coordinates)
{
	is >> coordinates.length >> coordinates.amount;
	return is;
}
