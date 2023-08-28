#include<iostream>
#include<windows.h>
#include<string>
#include<fstream>
#include "player.h"
#include "snake.h"
#include "global.h"
using namespace std;


// score
typedef struct _score {
    std::string name;
    int level;
} score;

snake player;
score t_game;
int level;
int HP;

score rank_table[50];
int player_count;


void init_player() {
    level = 1;
    HP = 3;
    system("cls");
    gotoxy(52 ,13);
    cout << "NAME:"; cin >> t_game.name;
}

void table() {
    gotoxy(80, 3);
    cout << "             ----------     " << endl;
    gotoxy(80, 4);
    cout << "            /           \\   " << endl;
    gotoxy(80, 5);
    cout << "           /   x          \\  " << endl;
    gotoxy(80, 6);
    cout << "          |                \\  " << endl;
    gotoxy(80, 7);
    cout << "          |  /\\     /|     |  " << endl;
    gotoxy(80, 8);
    cout << "           |/  |   /  |    |  " << endl;
    gotoxy(80, 9); 
    cout << "               |/      |  / " << endl;
    gotoxy(80, 10);   
    cout << "                       //     " << endl;
    gotoxy(80, 11); 
    cout << "                      //       " << endl;
    gotoxy(80, 12); 
    cout << "                    //           " << endl;
    gotoxy(80, 13); 
    cout << "                   //              " << endl;
    gotoxy(80, 14); 
    cout << "                 //   "          << endl;
    gotoxy(80, 15); 
    cout << "                \\\\         /   " << endl;
    gotoxy(80, 16); 
    cout << "                   --------      " << endl;
    for (int i = 80; i < 120; i++) {
        gotoxy(i, 18);
        cout << "*";
    }
    // 分數表
    gotoxy(86, 21);
    cout << "level:" << level;
    gotoxy(86, 23);
    cout << "HP:" << HP;
}

// 成績存入排行
void write_rank() {
    ofstream file;
    file.open("rank.dat", _S_app);
    file << t_game.name << endl;
    file << t_game.level << endl;
    file.close();
}

// 讀取成績
void read_rank() {
    player_count = 0;
    ifstream file;
    file.open("rank.dat");
    while (1) {
        file >> rank_table[player_count].name;
        file >> rank_table[player_count].level;
        if (file.eof())
            break;
        player_count++;
    }
    file.close();
}

// 打印排行
void pri_rank() {
    gotoxy(58, 1);
    cout << "RANK";
    // 打印前十名
    for (int i = 0; i < player_count && i < 10; i++) {
        gotoxy(51, 4 + 3 * i);
        cout << i + 1 << ".   NAME:" << rank_table[i].name << endl;
        gotoxy(51, 5 + 3 * i);
        cout << "     LEVEL:" << rank_table[i].level << endl;

    }
    gotoxy(0, 30);
    Sleep(1500);
    system("pause");
}

// 排序排名
void sort_rank() {
    for (int i = 0; i < player_count; i++) {
        for (int j = 0; j < player_count - i; j++) {
            score temp;
            if (rank_table[j].level < rank_table[j + 1].level) {
                temp = rank_table[j];
                rank_table[j] = rank_table[j + 1];
                rank_table[j + 1] = temp;
            }
        }
    }
    ofstream file;
    file.open("rank.dat");
    for (int i = 0; i < player_count; i++) {
        file << rank_table[i].name << endl;
        file << rank_table[i].level << endl;
    }
    file.close();
}

// 遊戲結束
void game_over() {
    system("cls");
    t_game.level = level;
    // 存入排行榜
    write_rank();
    // 讀取排行
    read_rank();
    // 排序排名
    sort_rank();
    // 打印排行榜
    pri_rank();
}

