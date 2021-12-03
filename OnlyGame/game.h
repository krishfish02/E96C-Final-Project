#include <stdbool.h>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10

struct Symbol {
    char empty;
    char player_no_item;
    char player_on_item;
    char player_carry_item;

    char item_q;
    char item_e;
    char slot_1;
    char slot_2;
};

struct Params {
    int width;
    int height;

    struct Symbol info;
};

struct State {
    bool slot_1_done;
    bool slot_2_done;

    bool player_carry_q;
    bool player_carry_e;
};

typedef struct LocationStruct {
    int x;
    int y;
} Location;

struct Positions {
    Location player;
    Location item_q;
    Location item_e;
    Location slot_1;
    Location slot_2;
};

typedef struct GameStruct {
    struct Params p;
    struct State s;
    struct Positions pos;
} Game ;

void init_game(Game* g);
void reset_game(Game *g);
void random_field(Game* g);
void print_game(Game* g);
void update_game(Game *g, int action);
int user_input();
