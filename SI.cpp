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

int menuMain();

int main() 
{
    //menuMain();
    
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    //timeout(10);
    
    refresh();
    
    Player player((COLS - 3) / 2, LINES - 2, "/_\\");

    // Initialize the aliens
    std::vector<Alien> aliens;
    for (int i = 0; i < 4; ++i) 
    {
        for (int j = 0; j < 20; ++j) 
        {
            aliens.emplace_back(5 + j * 4, 2 + i * 4, "  -@|^^|@-  ");
        }
    }

    // Initialize the bullets
    std::vector<Bullet> bullets;
    
    int score = 0;
// Print score label in the top right-hand corner
mvprintw(0, COLS - 15, "Score: %d", score);

// Game loop
while (true) 
{
    clear();
    
    // Move and draw the player
    int ch = getch();
    switch (ch) 
    {
    case KEY_LEFT:
        player.move(-1, 0);
        break;
    case KEY_RIGHT:
        player.move(1, 0);
        break;
    case ' ':
        bullets.emplace_back(player.x(), player.y() - 1, -1, '|');
        break;
    }
    player.draw();

    // Move and draw the aliens
    bool reverseDirection = false;
    for (auto& alien : aliens) 
    {
        alien.move();
        alien.draw();
        if (alien.x() <= 0 || alien.x() >= COLS - 1) 
        {
            reverseDirection = true;
        }
    }
    if (reverseDirection) 
    {
        for (auto& alien : aliens) 
        {
            alien.reverseDirection();
        }
    }

    // Move and draw the bullets
    for (auto it = bullets.begin(); it != bullets.end();) 
    {
        it->move();
        it->draw();
        if (it->y() <= 0 || it->y() >= LINES - 1) 
        {
            it = bullets.erase(it);
        } else {
            ++it;
        }
    }

    // Check for collisions between bullets and aliens
    for (auto it = bullets.begin(); it != bullets.end();) 
    {
        bool hit = false;
        for (auto jt = aliens.begin(); jt != aliens.end();) 
        {
            if (it->y() == jt->y() && it->x() >= jt->x() && it->x() < jt->x() + jt->symbol().length()) 
            {
                jt = aliens.erase(jt);
                hit = true;
                score += 10;  // Update score
                // Print updated score in the top right-hand corner
                mvprintw(0, COLS - 15, "Score: %d", score);
                break;
            } 
            else 
            {
                ++jt;
            }
        }
        if (hit) 
        {
            it = bullets.erase(it);
        } 
        else 
        {
            ++it;
        }
    }

    // Check for game over
    if (aliens.empty()) 
    {
        mvprintw(LINES / 2, (COLS - 20) / 2, "YOU WIN!");
        refresh();
        getch();
        break;
    }

    refresh();
    usleep(20000);
}

// Print final score
mvprintw(0, COLS - 10, "SCORE: %d", score);
refresh();
usleep(20000);

// Clean up ncurses
endwin();

return 0;
}
