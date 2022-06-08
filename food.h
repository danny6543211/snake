#ifndef _FOOD_
#define _FOOD_
class food {
    public:
        void cre_food();
        int eat_food(snake player);
    private:
        int x;
        int y;
};
#endif