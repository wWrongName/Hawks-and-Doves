#include <stdio.h>
#include "hawks_and_doves.h"
#define rate 10  //temporary need for functional test

int main()
{
	SETTINGS game_s = set_rate(rate, rate, rate);  //set 10% for hawk, dove and food
	brd_set(&game_s); //arrange characters on the board
	search_mid(); //make variable for the uniform memory allocation for hex_coords
	print_board();
	return 0;
}