#include<iostream>
#include<windows.h>
#include "map.h"
#include "global.h"
using namespace std;

int choice;
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
    for(int i = 80; i < 120; i++) {
        gotoxy(i, 0);
        cout << "*";
    }
    for (int j = 0; j < 30; j++) {
        gotoxy(119, j);
        cout << "*";
    }
    for(int i = 80; i < 120; i++) {
        gotoxy(i, 29);
        cout << "*";
    }
    gotoxy(0, 0);
}

void pri_hp() {
    extern int HP;
    system("cls");
    gotoxy(52 ,13);
    cout << "HP:" << HP;
    Sleep(3000);
}