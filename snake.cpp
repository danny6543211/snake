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
}

// 開始函數
void start() {
    if (choice == 3)
        exit(0);
    if (choice == 1) {
        // map();
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

class xy_point {
    public:
        void set(int a, int b) {
            x = a;
            y = b;
        }
    private:
        int x;
        int y;
};