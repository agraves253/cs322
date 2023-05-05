#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>

//player class
class Player 
{
public:
    //initialize player's starting position and symbol
    Player(int x, int y, const std::string& symbol)
        : x_(x), y_(y), symbol_(symbol) {}

    //move the player's position by dx and dy
    void move(int dx, int dy) 
    {
        x_ += dx;
        y_ += dy;
        // Ensure the player stays within the screen boundaries
        if (x_ < 0) 
        {
            x_ = 0;
        }
        if (x_ + symbol_.length() > COLS) 
        {
            x_ = COLS - symbol_.length();
        }
    }

    //draw the player at their current position
    void draw() const {       
        for (size_t i = 0; i < symbol_.length(); ++i) 
        {
            mvaddch(y_, x_ + i, symbol_[i]);
        }
    }

    //return the player's x coordinate
    int x() const { return x_; }

    //return the player's y coordinate
    int y() const { return y_; }

    //return player's symbol
    const std::string& symbol() const { return symbol_; }

private:
    int x_; 
    int y_; 
    std::string symbol_; 
};
