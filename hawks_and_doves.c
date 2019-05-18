#include <stdlib.h>
#include <stdio.h>
#include "hawks_and_doves.h"

char offset[6][3] = {{1, -1, 0},  //array for movement characters(except FOOD)
					 {0, -1, 1},
					 {-1, 0, 1},
					 {-1, 1, 0},
					 {0, 1, -1},
					 {1, 0, -1}};

void brd_set(SETTINGS *SETTINGS) { 
	struct TUNIT V;
	const int max_hp = 10;
	memset(&BOARD, 0, sizeof(BOARD));
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
			BOARD.cells[i][j].content[0] = V;
		}
	}
}

char cell_empty(TCELL cell) {
	if (cell.content[0].type == EMPTY)
		return 1; //yeah, cell is empty
	return 0;
}

TCELL *brd_start() {
	for (int i = 0; i < AMOUNT; i++) {
		for (int j = 0; j < AMOUNT; j++) {
			if (!cell_empty(BOARD.cells[i][j]))
				return &BOARD.cells[i][j];
		}
	}
	return NULL;
}

TCELL *brd_next(int i1, int j1) {
	for (int i = i1; i < AMOUNT; i++) {
		for (int j = j1; j < AMOUNT; j++) {
			if (!cell_empty(BOARD.cells[i][j]))
				return &BOARD.cells[i][j];
		}
	}
	return NULL;
}

void print_board() { 
	for (int i = 0; i < AMOUNT; i++) {
		printf("\n");
		for (int j = 0; j < AMOUNT; j++) {
			printf("%d", BOARD.cells[i][j].content[0].type);
			printf("  ");
		}
	}
}

SETTINGS set_rate(double hawk_rate, double dove_rate, double food_rate) {
	SETTINGS sttgs;
	sttgs.hawk_rate = hawk_rate / 100;
	sttgs.dove_rate = dove_rate / 100;
	sttgs.food_rate = food_rate / 100;
	return sttgs;
}

HEX_COORD bi_to_hex(BI_COORD from) {
	HEX_COORD to;
	to.z = from.p - board_mid.p;
	to.x = from.q - (to.z / 2);
	to.y = ~(to.x + to.z - 1);
	return to;   
}                 
                  
BI_COORD hex_to_bi(HEX_COORD from) {
	BI_COORD to;  
	to.p = from.z + board_mid.p;
	to.q = from.x + (to.p / 2) + board_mid.q;
	return to;
}

void search_mid() {
	board_mid.p = AMOUNT >> 1;
	board_mid.q = AMOUNT >> 1;
}

void make_move(TUNIT character, BI_COORD arr_place, char origin) {
	character.hp--;
	BI_COORD tmp = arr_place;
	arr_place = find_the_way(arr_place);
	if (arr_place.p != -1) {
		BOARD.cells[arr_place.p][arr_place.q].content[cont_ptr] = character;
		BOARD.cells[tmp.p][tmp.q].content[origin].hp = 0;
		BOARD.cells[tmp.p][tmp.q].content[origin].type = EMPTY;
	}
}

BI_COORD find_the_way(BI_COORD arr_place) {
	HEX_COORD tmp = bi_to_hex(arr_place);
	for (int i = 0; i < 6; i++) {
		tmp.x += offset[i][0];
		tmp.y += offset[i][1];
		tmp.z += offset[i][2];
		arr_place = hex_to_bi(tmp);
		if (check_place(arr_place, tmp))
			return arr_place;
	}
	arr_place.p = -1;
	return arr_place;
}

char check_place(BI_COORD bi, HEX_COORD hex) {
	if (bi.p > AMOUNT || bi.q > AMOUNT)
		return 0;
	if (bi.p < 0 || bi.q < 0)
		return 0;
	for (int i = 0; i < CELL_MAX; i++) {
		if (BOARD.cells[bi.p][bi.q].content[i].type == EMPTY) {
			cont_ptr = i;
			return 1;
		}
	}
	return 0;
}