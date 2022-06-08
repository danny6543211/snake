#include<iostream>
#include "snake.h"
#include "food.h"
#include "global.h"
using namespace std;

food fd;

void food::cre_food() {
    srand(time(nullptr));
    x = rand() % 79 + 1;
    y = rand() % 26 + 2;
    gotoxy(x, y);
    cout << "*";
}

int food::eat_food(snake player) {
    if (((player.get_s_head()) -> x == x) && ((player.get_s_head()) -> y == y)) {
        // 蛇變長
        snake_dot *p = (snake_dot*)malloc(sizeof(snake_dot));
        p -> next =  player.get_t_head();
        player.set_t_head(p);
        // 透過新鍊表頭的下一個和下下個的位置相減 再加上下一個的位置 找出新頭要放的位置
        p -> x = (p -> next) -> x - ((p -> next) -> next) -> x + (p -> next) -> x; 
        p -> y = (p -> next) -> y - ((p -> next) -> next) -> y + (p -> next) -> y; 
        return 1;
    }
    if (((player.get_t_head()) -> x == x) && ((player.get_t_head()) -> y == y)) {
        cre_food();
    }
    return 0;
}