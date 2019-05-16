#include <stdio.h>
#include "hawks_and_doves.h"
#define rate 10

int main()
{
	SETTINGS game_s = set_rate(rate, rate, rate);
	brd_set(&BOARD, &game_s);
	
	return 0;
}