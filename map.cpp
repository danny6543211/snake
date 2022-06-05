// temp
#include<iostream>
#include "snake.h"
using namespace std;

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