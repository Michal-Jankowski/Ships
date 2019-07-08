#include "Player.h"


//ustawia imie dla gracza
void Player::SetName(std::string const & s)
{
	_name = s;
}

//konsturktor
Player::Player(Game * game):
	game(game)
{
}
//destruktor
Player::~Player()
{
}
