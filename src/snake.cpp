#include<iostream>
#include<windows.h>
#include<conio.h>
#include "snake.h"
#include "global.h"
#include "food.h"
#include "player.h"
#include "map.h"
using namespace std;

void snake::init_snake() {
    dict = RIGHT;
    snake_dot *temp = (snake_dot*)malloc(sizeof(snake_dot));
    temp -> x = 20;
    temp -> y = 20;
    // 鍊表頭
    t_head = temp;
    // 蛇頭
    s_head = temp;
    for (int i = 1; i < 5; i++) {
        snake_dot *p = (snake_dot*)malloc(sizeof(snake_dot));
        p -> x = 20 + i;
        p -> y = 20;
        s_head -> next = p;
        s_head = p;
    }
    s_head -> next = nullptr;
}

void snake::pri_snake() {
    snake_dot *p = t_head;
    gotoxy(t_head -> x, t_head -> y);
    cout << " ";
    p = p -> next;
    while (p != nullptr) {
        gotoxy(p -> x, p -> y);
        cout << "*";
        p = p -> next;
    }
}

void snake::move_snake() {
    // 新蛇頭
    snake_dot *new_head = (snake_dot*)malloc(sizeof(snake_dot));
    s_head -> next = new_head;
    new_head -> next = nullptr;
    switch (dict) {
        case UP:       new_head -> x = s_head -> x;        new_head -> y = s_head -> y - 1;    break; 
        case LEFT:     new_head -> x = s_head -> x - 1;    new_head -> y = s_head -> y;        break;
        case DOWN:     new_head -> x = s_head -> x;        new_head -> y = s_head -> y + 1;    break;
        case RIGHT:    new_head -> x = s_head -> x + 1;    new_head -> y = s_head -> y;        break;
    }
    s_head = new_head;

    // 刪掉舊鍊表頭
    snake_dot *temp = t_head -> next;
    delete t_head;
    t_head = temp;
}

void snake::set_dict(_DICT di) {
    dict = di;
}

int snake::hit_wall() {
    if (s_head -> x > 79 || s_head -> x < 1 || s_head -> y > 28 || s_head -> y < 1)
        return 1;
    return 0;
}

void snake::delete_snake() {
    snake_dot *p = t_head;
    while (p != nullptr) {
        gotoxy(p -> x, p -> y);
        cout << " ";
        p = p -> next;
    }
    // 要把蛇頭畫回來 不然牆被吃掉了
    gotoxy(s_head -> x, s_head -> y);
    cout << "*";
    delete s_head;
    delete t_head;
}

snake_dot* snake::get_t_head() {
    return t_head;
}

void snake::set_t_head(snake_dot *hd) {
    t_head = hd;
}

snake_dot* snake::get_s_head() {
    return s_head;
}

void snake::set_s_head(snake_dot *hd) {
    s_head = hd;
}

void run_player(snake player) {
    char ch;
    extern int HP;
    extern int level;
    extern int have_h_food;
    extern int h_level;
    extern food fd;
    extern h_food h_fd;
    table();
    while (1) {
        Sleep(200 / level + (3 / HP) * 5);
        // 如果有改變方向的鍵盤輸入
        if (kbhit()) {
            ch = getch();
            switch (ch) {
                case 'w':
                    player.set_dict(UP);
                    break;
                case 'a':
                    player.set_dict(LEFT);
                    break;
                case 's':
                    player.set_dict(DOWN);
                    break;
                case 'd':
                    player.set_dict(RIGHT);
                    break;
                default:
                    break;
            }
        }
        // 移動蛇
        player.move_snake();
        // 如果撞牆
        if (player.hit_wall()) {
            HP--;
            if (HP == 0)
                break;
            player.delete_snake();
            player.init_snake();
            table();
            pri_hp();
            system("cls");
            table();
            map();
            if (h_level)
                h_fd.cre_food();
            else 
                fd.cre_food();
        }
        //打印蛇
        player.pri_snake(); 



        if (h_level == 0) {
            if (fd.eat_food(player)) {
                level++;
                table();
                if (level > 5) {
                    h_level = 1;
                    continue;
                }
                fd.cre_food();
            }
        } else if (h_level == 1) {
            if (have_h_food == 0) {
                h_fd.cre_food();
                have_h_food = 1;
            }
            if (h_fd.eat_food(player)) {
                level += 2;
                h_fd.cre_food();
                table();
            }
        }
    }   
}