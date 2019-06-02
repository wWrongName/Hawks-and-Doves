#ifndef _STRUCTURES_
#define _STRUCTURES_
#define CELL_MAX 7
#define AMOUNT 19
#define MAX_HP 10

typedef enum TYPE_TUNIT{
	EMPTY,
	DOVE, 
	HAWK, 
	FOOD
} TYPE_TUNIT;

typedef struct TUNIT{
	int hp;
	TYPE_TUNIT type;
	char used;
} TUNIT;

typedef struct TCELL {
	TUNIT content [CELL_MAX];
} TCELL;

struct BOARD {
	TCELL cells[AMOUNT][AMOUNT];
} BOARD;

typedef struct SETTINGS {
	double hawk_rate,
		   dove_rate,
		   food_rate;
} SETTINGS;

typedef struct HEX_COORD { //  Y /\  |  /\ X       coordinates for game board of hexagons|
	int x;             //     \  |  /                                                |
	int y;             //       \|/                                                  |
	int z;		   //       /|\                                                  |
} HEX_COORD;               //     /  |  \                                                |
		           //   /    V Z  \                                              |

typedef struct BI_COORD {  //   Г-----------> Q    coordinatea for an array              |
	int q;             //   |                                                        |
	int p;             //   |                                                        |
} BI_COORD;                //   |                                                        |
                           //   V P                                                      |

char cont_ptr;
BI_COORD board_mid;
unsigned int heroes = 0;

void brd_set(SETTINGS *SETTINGS); //randomly scatters all characters
char cell_empty(TCELL cell); //check cell for EMPTY unit
void print_board(); //print board in the form of a matrix (temporary need for functional test)
SETTINGS set_rate(double hawk_rate, double dove_rate, double food_rate);
HEX_COORD bi_to_hex(BI_COORD from); //translate from rectangular coordinate system on the plane to hexademical system (like coordinate system in the space) 
BI_COORD hex_to_bi(HEX_COORD from); //inverted by previous
void search_mid();
void make_move(TUNIT character, BI_COORD arr_place, char origin);
BI_COORD find_the_way(BI_COORD arr_place); //choose the way for movement
char check_place(BI_COORD bi, HEX_COORD hex); //check borders and free space
BI_COORD set_bi_coord(int q, int p);
void remove_bodies(TCELL cell);
void resolve_conflicts(TCELL cell, BI_COORD place);
void check_conflicts_and_corpses();

#endif
