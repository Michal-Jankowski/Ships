#include "Game.h"
#include "Parameters.h"


int main(int argc, char* argv[]) {

	Parameters params(argc, argv);//przekazanie parametrow do klasy Parameters
	Game bs(params); //w tym momencie w params zapamietane wszystkie wazne informacje sparsowane z argv
	bs(); // koniec gry	
	return 0;
	
}