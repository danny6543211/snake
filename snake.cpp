#include<iostream>
using namespace std;
#include "snake.h"

// 菜單
int menu() {
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
    int choice;
    cin >> choice;
    return choice;
}

void map() {
    for (int i = 0; i < 80; i++) {
        cout << "*";
    }   
    cout << endl;
    for (int i = 0; i < 27; i++) {
        cout << "*";
        for (int i = 0; i < 78; i++) {
            cout << " ";
        }
        cout << "*";
        cout << endl;
    }
    for (int i = 0; i < 80; i++) {
        cout << "*";
    }


}