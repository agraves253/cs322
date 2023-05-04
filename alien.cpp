#include <ncurses.h>

class Alien 
{
public:
    Alien(int x, int y, char symbol)
        : x_(x), y_(y), symbol_(symbol), direction_(1) {}

    void move() 
    {
        x_ += direction_;
    }

    void reverseDirection() 
    {
        direction_ *= -1;
        y_ += 1;
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
    int direction_;
};
