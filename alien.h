#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>

#ifndef ALIEN_H
#define ALIEN_H


//Alien class
class Alien 
{
public:
    //create an Alien object
    Alien(int x, int y, std::string symbol)
        : x_(x), y_(y), symbol_(symbol), direction_(1) {}

    // Move the alien horizontally by adding the direction to its x-coordinate
    void move() 
    {
        x_ += direction_;
    }

    // Reverse the direction of the alien and move it down one row
    void reverseDirection() 
    {
        direction_ *= -1;
        y_ += 1;
    }

    // Draw the alien on the screen
    void draw() const 
    {
        for (int i = 0; i < symbol_.size(); ++i) 
        {
            mvaddch(y_, x_ + i, symbol_[i]);
        }
    }

    // Return the x-coordinate of the alien
    int x() const { return x_; }

    // Return the y-coordinate of the alien
    int y() const { return y_; }

    // Return the symbol of the alien
    std::string symbol() const { return symbol_; }

private:
    int x_;
    int y_;
    std::string symbol_;
    int direction_;
};

#endif // ALIEN_H
