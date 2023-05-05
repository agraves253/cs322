#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>

#ifndef BULLET_H
#define BULLET_H

class Bullet 
{
public:
    Bullet(int x, int y, int dy, char symbol)
        : x_(x), y_(y), dy_(dy), symbol_(symbol) {}

    void move() 
    {
        y_ += dy_;
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
    int dy_;
    char symbol_;
};

#endif
