#include <stdlib.h>
#include <stdio.h>
#include "hawks_and_doves.h"

void brd_set(struct BOARD *BOARD, SETTINGS *SETTINGS) {
	struct TUNIT V;
	const int max_hp = 10;
	memset(BOARD, 0, sizeof(*BOARD));
	for (int i = 0; i < AMOUNT; i++) {
		for (int j = 0; j < AMOUNT; j++) {
			double randn = (double)rand() / RAND_MAX;
			if (randn < SETTINGS->dove_rate)
				V.type = DOVE;
			else {
				randn -= (SETTINGS->dove_rate);
				if (randn < SETTINGS->hawk_rate)
					V.type = HAWK;
				else {
					randn -= (SETTINGS->hawk_rate);
					if (randn < SETTINGS->food_rate)
						V.type = FOOD;
					else
						V.type = EMPTY;
				}
			}
			BOARD->cells[i][j].content[0] = V;
		}
	}
}

char cell_empty(TCELL cell) {
	if (cell.content[0].type == EMPTY)
		return 1;
	return 0;
}

TCELL *brd_start(struct BOARD *BOARD) {
	for (int i = 0; i < AMOUNT; i++) {
		for (int j = 0; j < AMOUNT; j++) {
			if (!cell_empty(BOARD->cells[i][j]))
				return &BOARD->cells[i][j];
		}
	}
	return NULL;
}

TCELL *brd_next(struct BOARD *BOARD, int i1, int j1) {
	for (int i = i1; i < AMOUNT; i++) {
		for (int j = j1; j < AMOUNT; j++) {
			if (!cell_empty(BOARD->cells[i][j]))
				return &BOARD->cells[i][j];
		}
	}
	return NULL;
}

void print_board(struct BOARD *BOARD) {
	for (int i = 0; i < AMOUNT; i++) {
		printf("\n");
		for (int j = 0; j < AMOUNT; j++) {
			printf("%d", BOARD->cells[i][j].content[0].type);
			printf("  ");
		}
	}
}

SETTINGS set_rate(double hawk_rate, double dove_rate, double food_rate) {
	SETTINGS sttgs;
	sttgs.hawk_rate = hawk_rate / 100;
	sttgs.dove_rate = dove_rate / 100;
	sttgs.hawk_rate = food_rate / 100;
	return sttgs;
}

HEX_COORD *bi_to_hex(BI_COORD *from) {
	HEX_COORD to;
	to.z = from->p;
	to.x = from->q - (to.z >> 1);
	to.y = ~(to.x + to.z - 1);
	return &to;   
}                 
                  
BI_COORD *hex_to_bi(HEX_COORD *from) {
	BI_COORD to;  
	to.p = from->z;
	to.q = from->x + (to.p >> 1);
	return &to;
}