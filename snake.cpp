#include<iostream>
#include "snake.h"
#include<windows.h>
#include<conio.h>
using namespace std;

// snake
typedef struct _snake {
    int x;
    int y;
    struct _snake *next;
}snake;

// 全局變量
static int choice;
snake *t_head;
snake *s_head;
enum _dict {
    UP = 'w',
    DOWN = 's',
    LEFT = 'a',
    RIGHT = 'd'
}dict;

// 菜單
void menu() {
    for (int i = 0; i < 7; i++) {
        cout << endl;
    }
    cout << "                       **********    **         *      ********      *          *      **********    " << endl;
    cout << "                      *              * *        *    *          *    *        *      *               " << endl;
    cout << "                     *               *  *       *    *          *    *      *        *               " << endl;
    cout << "                     *               *   *      *    *          *    *    *          *               " << endl;
    cout << "                     *               *    *     *    *          *    *  *            *               " << endl;
    cout << "                     ************    *     *    *    ************    **              ************    " << endl;
    cout << "                                *    *      *   *    *          *    *  *            *               " << endl;
    cout << "                                *    *       *  *    *          *    *    *          *               " << endl;
    cout << "                                *    *        * *    *          *    *      *        *               " << endl;
    cout << "                                *    *         **    *          *    *        *      *               " << endl;
    cout << "                     ***********     *          *    *          *    *          *      **********    " << endl;
    for (int i = 0; i < 5; i++) {
        cout << endl;   
    }
    cout << "                                      1. START         2. RANK          3. EXIT" << endl;
    for (int i = 0; i < 5; i++) {
        cout << endl;   
    }
    cout << ":";
    cin >> choice;
    system("cls");
}

// 開始函數
void start() {
    if (choice == 3)
        exit(0);
    if (choice == 1) {
        map();
        init_snake();
        run();
        // system("pause");
        // ...
    }

}

// 設置光標
void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

// 初始化蛇
void init_snake() {
    dict = RIGHT;
    snake *temp = (snake*)malloc(sizeof(snake));
    temp -> x = 20;
    temp -> y = 20;
    // 鍊表頭
    t_head = temp;
    // 蛇頭
    s_head = temp;
    for (int i = 1; i < 4; i++) {
        snake *p = (snake*)malloc(sizeof(snake));
        p -> x = 20 + i;
        p -> y = 20;
        s_head -> next = p;
        s_head = p;
    }
    s_head -> next = nullptr;
}

//地圖跟記分板
void map() {
    int temp;
    for (int i = 0; i < 80; i++) {
        gotoxy(i, 0);
        cout << "*";
    }   
    for (int j = 1; j < 29; j++){
        gotoxy(0, j);
        cout << "*";
        for(int i = 1; i < 79; i++) {
            gotoxy(i ,j);
            cout << " ";
        }
        gotoxy(79, j);
        cout << "*";
    }
    for (int i = 0; i < 80; i++) {
        gotoxy(i, 29);
        cout << "*";
    }   
}

// 打印蛇
void pri_snake() {
    snake *p = t_head;
    gotoxy(t_head -> x, t_head -> y);
    cout << " ";
    p = p -> next;
    while (p != nullptr) {
        gotoxy(p -> x, p -> y);
        cout << "*";
        p = p -> next;
    }
}

// 移動蛇
void move_snake() {
    // 新蛇頭
    snake *new_head = (snake*)malloc(sizeof(snake));
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
    snake *temp = t_head -> next;
    delete t_head;
    t_head = temp;
}

// 開始遊戲
void run() {
    char ch;
    while (1) {
        // 如果有改變方向的鍵盤輸入
        if (kbhit()) {
            ch = getch();
            switch (ch) {
                case 'w':
                    dict = UP;
                    break;
                case 'a':
                    dict = LEFT;
                    break;
                case 's':
                    dict = DOWN;
                    break;
                case 'd':
                    dict = RIGHT;
                    break;
                default:
                    break;
            }
        }
        // 移動蛇
        move_snake();
        //打印蛇
        pri_snake();
        // 判斷死亡與食物
        Sleep(1000);
    }
}

