#include <stdio.h>
#include "hawks_and_doves.h"
#define rate 10  //temporary need for functional test

int main()
{
	SETTINGS game_s = set_rate(rate, rate, rate);  //set 10% for hawk, dove and food
	brd_set(&game_s); //arrange characters on the board
	search_mid(); //make variable for the uniform memory allocation for hex_coords

	////////////////////////////////////////////////////////////////////////// 
	for (int i = 0; i < AMOUNT*AMOUNT; i++) {                               //
		for (int j = 0; j < CELL_MAX; j++) {                                //  make loop (function with loop)
			TUNIT tmp = BOARD.cells[i / AMOUNT][i % AMOUNT].content[j];     //  
			if (tmp.type != EMPTY && tmp.used != 1 && tmp.type != FOOD)     //
				make_move(tmp, set_bi_coord(i / AMOUNT, i % AMOUNT), j);    //  until one type of animal dies out, make loop
		}                                                                   //
	}                                                                       //
	check_conflicts_and_corpses();                                          //
	//////////////////////////////////////////////////////////////////////////

	return 0;
}