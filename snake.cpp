#include<iostream>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include<ctime>
#include "snake.h"
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

// score
typedef struct _SCORE {
    string name;
    int level;
}score;

// 全局變量
int choice;
snake *t_head;
snake *s_head;
food fd;
int level = 1;
int HP;
score player;
int player_count;
score rank_table[50];

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

// 設置光標位置
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

//畫地圖
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
    HP = 3;
    char ch;
    table();
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
            HP--;
            if (HP == 0)         
                break;
            delete_snake();
            init_snake();
            table();
        }
        //打印蛇
        pri_snake();        
        // 如果吃食物
        if (eat_food()) {
            level++;
            cre_food();
            table();
        }    
        Sleep(300 / level);
    }
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
    if (s_head -> x > 79 || s_head -> x < 1 || s_head -> y > 28 || s_head -> y < 1)
        return 1;
    return 0;
}

// 遊戲結束
void game_over() {
    system("cls");
    player.level = level;
    // 存入排行榜
    write_rank();
    // 讀取排行
    read_rank();
    // 排序排名
    sort_rank();
    // 打印排行榜
    pri_rank();
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

// 頭像跟分數表...
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

    //排行榜...

}

// 刪掉原本的蛇
void delete_snake() {
    snake *p = t_head;
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

// 成績存入排行
void write_rank() {
    ofstream file;
    file.open("rank.dat", _S_app);
    file << player.name << endl;
    file << player.level << endl;
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
    system("pause");
}

// 初始化玩家數據
void init_player() {
    level = 1;
    system("cls");
    gotoxy(52 ,13);
    cout << "NAME:"; cin >> player.name;
}

// 排序排名
void sort_rank() {
    for (int i = 0; i < player_count; i++) {
        for (int j = 0; j < player_count - i; j++) {
            score temp;
            if (rank_table[i].level < rank_table[i + 1].level) {
                temp = rank_table[i];
                rank_table[i] = rank_table[i + 1];
                rank_table[i + 1] = temp;
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

