#include<iostream>
#include "snake.h"
#include<windows.h>
using namespace std;

// 菜單
void menu() {
    for (int i = 0; i < 7; i++) {
        cout << endl;
    }
    cout << "                       **********    **         *      ********      *          *      **********       " << endl;
    cout << "                      *              * *        *    *          *    *        *      *              " << endl;
    cout << "                     *               *  *       *    *          *    *      *        *               " << endl;
    cout << "                     *               *   *      *    *          *    *    *          *               " << endl;
    cout << "                     *               *    *     *    *          *    *  *            *               " << endl;
    cout << "                     ************    *     *    *    ************    **              ************                " << endl;
    cout << "                                *    *      *   *    *          *    *  *            *              " << endl;
    cout << "                                *    *       *  *    *          *    *    *          *               " << endl;
    cout << "                                *    *        * *    *          *    *      *        *              " << endl;
    cout << "                                *    *         **    *          *    *        *      *                  " << endl;
    cout << "                     ***********     *          *    *          *    *          *      **********                  " << endl;
    for (int i = 0; i < 5; i++) {
        cout << endl;   
    }
    cout << "                                      1. START         2. RANK          3. EXIT" << endl;
    for (int i = 0; i < 5; i++) {
        cout << endl;   
    }
    cout << ":";
    extern int choice;
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

// snake
typedef struct _snake {
    int x;
    int y;
    struct _snake *next;
}snake;

// 初始化蛇
void init_snake() {
    snake *tail = (snake*)malloc(sizeof(snake));
    tail -> x = 20;
    tail -> y = 20;
    tail -> next = nullptr;
    snake *head = tail;
    for(int i = 1; i < 4; i++) {
        snake *p = (snake*)malloc(sizeof(snake));
        p -> x = 20 + i;
        p -> y = 20;
        p -> next = head;
        head = p;
    }
    snake *temp = head;
    // 打印蛇
    while (temp != nullptr) {
        gotoxy(temp -> x, temp -> y);
        cout << "*";
        temp = temp -> next;
    }
    // ..讓蛇動
}

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
    // cin >> temp;


}