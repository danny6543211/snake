#include<iostream>
#include<windows.h>
#include "map.h"
#include "snake.h"
#include "food.h"
#include "player.h"
using namespace std;


int main() { 
    extern int choice;
    extern food fd;
    extern snake player;
    while (1) {
        menu();
        if (choice == 1) {
            init_player();
            map();
            player.init_snake();
            fd.cre_food();
            run_player(player);
            game_over();
        }
        if (choice == 2) {
            read_rank();
            sort_rank();
            pri_rank();
        }
        if (choice == 3)
            break;
    }
    return 0;
}