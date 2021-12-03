#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "game.h"

// Initialize game information
void init_game(Game* g) {
    // Call ONCE
    time_t t;
    srand(time(&t));

    g->p.width = BOARD_WIDTH;
    g->p.height = BOARD_HEIGHT;

    g->p.info.empty = '.';
    g->p.info.player_no_item = 'o';
    g->p.info.player_on_item = '@';
    g->p.info.player_carry_item = 'x';

    g->p.info.item_q = 'q';
    g->p.info.item_e = 'e';
    g->p.info.slot_1 = '1';
    g->p.info.slot_2 = '2';

    g->s.slot_1_done = false;
    g->s.slot_2_done = false;
    g->s.player_carry_q = false;
    g->s.player_carry_e = false;

    g->pos.player.x = 7;
    g->pos.player.y = 2;
    g->pos.item_q.x = 0;
    g->pos.item_q.y = 2;
    g->pos.item_e.x = 3;
    g->pos.item_e.y = 8;
    g->pos.slot_1.x = 4;
    g->pos.slot_1.y = 7;
    g->pos.slot_2.x = 5;
    g->pos.slot_2.y = 6;
    
    random_field(g);
}

// Reset game state
void reset_game(Game* g) {
    init_game(g);
}

// Check if locations are the same
bool same_position(Location pos_a, Location pos_b) {
    return (pos_a.x == pos_b.x) && (pos_a.y == pos_b.y);
}

// Return true if all positions are different
bool all_diff(Location* lst) {
    for (int i = 0; i < 1; i++) {
        for (int j = i + 1; j < 2; j++) {
            if (same_position(lst[i], lst[j])) {
                return false;
            }
        }
    }
    return true;
}

// Randomize locations of objects; all different locations
void random_field(Game* g) {
    Location loc[5] = {{0}};

    while (!all_diff(loc)) {
        for (int i = 0; i < 5; i++) {
            loc[i].x = rand() % BOARD_WIDTH;
            loc[i].y = rand() % BOARD_HEIGHT;
        }
    }

    g->pos.player.x = loc[0].x;
    g->pos.player.y = loc[0].y;
    g->pos.item_q.x = loc[1].x;
    g->pos.item_q.y = loc[1].y;
    g->pos.item_e.x = loc[2].x;
    g->pos.item_e.y = loc[2].y;
    g->pos.slot_1.x = loc[3].x;
    g->pos.slot_1.y = loc[3].y;
    g->pos.slot_2.x = loc[4].x;
    g->pos.slot_2.y = loc[4].y;
}

// Print game
void print_game(Game* g) {
    
    
    
    for(int y = 0; y<BOARD_HEIGHT;y++)
    {
        for(int x = 0; x<BOARD_WIDTH;x++)
        {
            Location current;
            current.x = x;
            current.y = y;
                //Check all elements in this order of presidence
                //player
                if (same_position(g->pos.player, current))
                {

                    if( g->s.player_carry_q || g->s.player_carry_e )
                    {
                        printf( "%c", g->p.info.player_carry_item);
                        
                    }
                        
                    else if(same_position(g->pos.player, g->pos.item_q) || same_position(g->pos.player, g->pos.item_e))
                    {
                        printf("%c", g->p.info.player_on_item);
                    }
                        
                    else
                    {
                        printf("%c", g->p.info.player_no_item);
                    }
                }
                    
                    
                //item_q
                else if(same_position(g->pos.item_q, current))
                {
                    if(g->s.slot_1_done)
                    {
                        printf("%c", g->p.info.empty);
                    }
                    else
                    {
                        printf("%c", g->p.info.item_q);
                    }
                }

                //item_e
                else if(same_position(g->pos.item_e, current))
                {
                    if(g->s.slot_2_done)
                    {
                        printf("%c", g->p.info.empty);
                    }
                    else
                    {
                        printf("%c", g->p.info.item_e);
                    }
                }

                //slot_1
                else if(same_position(g->pos.slot_1, current))
                {
                    if(g->s.slot_1_done)
                    {
                        printf("%c", g->p.info.empty);
                    }
                    else
                    {
                        printf("%c", g->p.info.slot_1);
                    }
                }

                //slot_2
                else if(same_position(g->pos.slot_2, current))
                {
                    if(g->s.slot_2_done)
                    {
                        printf("%c", g->p.info.empty);
                    }
                    else
                    {
                        printf("%c", g->p.info.slot_2);
                    }
                }
        

                else
                {
                    //Empty
                    printf(".");
                }

            printf("  ");
        }
        
        printf("\n");
    }
}

// Update game state given input action
// Actions are 0-5 listen in comments
void update_game(Game *g, int action) {
//Fix positions if out of bounds (wrap)
    //Note position is a list and therefore is passed by reference
    //def wrap_position(game, position):
        //position[0] = position[0] % game['param']['width']
        //position[1] = position[1] % game['param']['height']

    // Update position first
    if (action == 0)
        g->pos.player.y = (g->pos.player.y - 1) % BOARD_HEIGHT;
    else if(action == 1)
        g->pos.player.y = (g->pos.player.y + 1) % BOARD_HEIGHT;
    else if(action == 2)
        g->pos.player.x = (g->pos.player.x - 1) % BOARD_WIDTH;
    else if(action == 3)
        g->pos.player.x = (g->pos.player.x + 1) % BOARD_WIDTH;
    else if(action == 4)
    {
    
        // Becomes a NO OP if player is not standing on item
        if(same_position(g->pos.player, g->pos.item_q))
            // Item_q
            g->s.player_carry_q = true;

        else if(same_position(g->pos.player, g->pos.item_e))
            // Item_e
            g->s.player_carry_e = true;

        else
        {}
    }

    else if(action == 5)
    {
        // Becomes a NO OP if player does not have an item
        if(g->s.player_carry_q)
        {
            g->s.player_carry_q = false;
            // Item q
            if(same_position(g->pos.item_q, g->pos.slot_1))
                g->s.slot_1_done = true;
        }

        else if(g->s.player_carry_e)
        {
            g->s.player_carry_e = false;
            // Item e
            if(same_position(g->pos.item_e, g->pos.slot_2))
                g->s.slot_2_done = true;
        }

        else
        {}
    }
    else
    {}

    //After updating positions, update carried item position if applicable
    if(g->s.player_carry_q)
        // Item q
        g->pos.item_q = g->pos.player;

    else if(g->s.player_carry_e)
        // Item e
        g->pos.item_e = g->pos.player;

    else
    {}

    // All game states are updated.
}

int user_input(){
    
    
    printf("Chose your move: WASDQE \n");
    char c = getchar();

    switch(c) {

        case 'W':
            return 0;
          break;
        
        case 'S':
            return 1;
          break;
        
        case 'A':
            return 2;
           break;
            
        case 'D':
            return 3;
           break;
            
        case 'E':
            return 4;
           break;
            
        case 'Q':
            return 5;
           break;
            
        case 'w':
            return 0;
          break;
        
        case 's':
            return 1;
          break;
        
        case 'a':
            return 2;
           break;
            
        case 'd':
            return 3;
           break;
            
        case 'e':
            return 4;
           break;
            
        case 'q':
            return 5;
           break;
      
       default :
            return 6;
    }
    
}

int main( int argc, const char* argv[] ) {

    Game new_game;
    init_game(&new_game);
    
    while(!new_game.s.slot_1_done && !new_game.s.slot_2_done)
    {
        print_game(&new_game);
        
        int action = user_input();
        
        update_game(&new_game, action);
        
    }
    
    printf("You Win!! \n");

}
