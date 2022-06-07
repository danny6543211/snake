#include<iostream>
#include "snake.h"
using namespace std;

int main() {
    extern int choice;
    while (1) {
        menu();
        if (choice == 1) {
            init_player();
            map();
            init_snake();
            cre_food();
            run();
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