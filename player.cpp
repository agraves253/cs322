#include <ncurses.h>

class Player 
{
public:
    Player(int x, int y, char symbol)
        : x_(x), y_(y), symbol_(symbol) {}

    void move(int dx, int dy) 
    {
        x_ += dx;
        y_ += dy;
    }

    void draw() const {
        mvaddch(y_, x_, symbol_);
    }

    int x() const { return x_; }
    int y() const { return y_; }
    char symbol() const { return symbol_; }

private:
    int x_;
    int y_;
    char symbol_;
};
