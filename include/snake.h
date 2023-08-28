#ifndef _SNAKE_
#define _SNAKE_

// 蛇的方向wasd
enum _DICT {
    UP = 'w',
    DOWN = 's',
    LEFT = 'a',
    RIGHT = 'd'
};

// 蛇的點
class snake_dot {
    public:
        int x;
        int y;
        snake_dot *next;
};

// 蛇類
class snake {
    public:
        // 初始化蛇
        void init_snake();
        // 打印蛇
        void pri_snake();
        // 移動蛇
        void move_snake();
        // 改變蛇的方向
        void set_dict(_DICT di);
        // 是否撞到牆
        int hit_wall();
        // 刪掉自己
        void delete_snake();
        // 
        snake_dot *get_t_head();
        //
        void set_t_head(snake_dot *hd);
        //
        snake_dot *get_s_head();
        //
        void set_s_head(snake_dot *hd);
        //
    private:
        // 鍊表頭
        snake_dot *t_head;
        // 蛇頭
        snake_dot *s_head;
        // 蛇的方向
        _DICT dict;
        
};

void run_player(snake player);

#endif
