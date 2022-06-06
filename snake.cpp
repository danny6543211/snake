#include "snake.h"
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<ctime>
using namespace std;

// snake
typedef struct _SNAKE {
    int x;
    int y;
    struct _SNAKE *next;
}snake;

// wasd
enum _DICT {
    UP = 'w',
    DOWN = 's',
    LEFT = 'a',
    RIGHT = 'd'
}dict;

// food
typedef struct _FOOD {
    int x;
    int y;
}food;

// 全局變量
int choice;
snake *t_head;
snake *s_head;
food fd;
int score = 0;

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
    hide_cursor();
}

// 開始函數...
void start() {
    if (choice == 3)
        exit(0);
    if (choice == 1) {
        map();
        init_snake();
        cre_food();
        run();
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
    for (int i = 1; i < 5; i++) {
        snake *p = (snake*)malloc(sizeof(snake));
        p -> x = 20 + i;
        p -> y = 20;
        s_head -> next = p;
        s_head = p;
    }
    s_head -> next = nullptr;
}

//地圖
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

// 開始遊戲...
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
        // 如果撞牆
        if (hit_wall()) {
            break;;
        }
        //打印蛇
        pri_snake();        
        // 如果吃食物
        if (eat_food()) {
            score++;
            cre_food();
        }
        
        
        Sleep(100);
    }
    game_over();
}

// 隱藏光標
void hide_cursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);
}

// 撞到牆
int hit_wall() {
    if (s_head -> x > 79 || s_head -> x < 1 || s_head -> y > 28 || s_head -> y < 2)
        return 1;
    return 0;
}

// 遊戲結束
void game_over() {
    system("cls");
    cout << "game over" << endl;
    system("pause");
}

// 生成食物
void cre_food() {
    srand(time(nullptr));
    fd.x = rand() % 79 + 1;
    fd.y = rand() % 26 + 2;
    gotoxy(fd.x, fd.y);
    cout << "*";
}

// 吃到食物
int eat_food() {
    if ((s_head -> x == fd.x) && (s_head -> y == fd.y)) {
        // 蛇變長
        snake *p = (snake*)malloc(sizeof(snake));
        p -> next = t_head;
        t_head = p;
        // 透過新鍊表頭的下一個和下下個的位置相減 再加上下一個的位置 找出新頭要放的位置
        p -> x = (p -> next) -> x - ((p -> next) -> next) -> x + (p -> next) -> x; 
        p -> x = (p -> next) -> y - ((p -> next) -> next) -> y + (p -> next) -> y; 
        return 1;
    }
    if ((t_head -> x == fd.x) && (t_head -> y == fd.y)) {
        cre_food();
    }
    return 0;
}