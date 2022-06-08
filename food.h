#ifndef _FOOD_
#define _FOOD_

class food {
    public:
        void cre_food();
        int eat_food(snake player);
        void set_xy(int a, int b);
        void draw(char ch);
    private:
        int x;
        int y;
};
class h_food : public food {
    public:
        void cre_food();
};

#endif