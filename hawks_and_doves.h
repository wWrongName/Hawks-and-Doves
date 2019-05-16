#ifndef _STRUCTURES_
#define _STRUCTURES_
#define CELL_MAX 9
#define AMOUNT 20

typedef enum TYPE_TUNIT{
	EMPTY,
	DOVE, 
	HAWK, 
	FOOD
} TYPE_TUNIT;

typedef struct TUNIT{
	int hp;
	TYPE_TUNIT type;
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
	unsigned int z;    //       /|\                                                  |
} HEX_COORD;               //     /  |  \                                                |
                           //   /    V Z  \                                              |

typedef struct BI_COORD {  //   Г-----------> Q    coordinates for an array              |
	int q;             //   |                                                        |
	int p;             //   |                                                        |
} BI_COORD;                //   |                                                        |
                           //   V P                                                      |              


SETTINGS set_rate(double hawk_rate, double dove_rate, double food_rate);
TCELL *brd_next(struct BOARD *BOARD, int i1, int j1);
TCELL *brd_start(struct BOARD *BOARD);
HEX_COORD *bi_to_hex(BI_COORD *from);
BI_COORD *hex_to_bi(HEX_COORD *from);
void brd_set(struct BOARD *BOARD, SETTINGS *SETTINGS);
void print_board(struct BOARD *BOARD);
char cell_empty(TCELL cell);
#endif
