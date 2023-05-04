#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>

/*class Player 
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
};*/

class Player 
{
public:
    Player(int x, int y, const std::string& symbol)
        : x_(x), y_(y), symbol_(symbol) {}

    /*void move(int dx, int dy) 
    {
        x_ += dx;
        y_ += dy;
    }*/
    
    void move(int dx, int dy) 
{
    x_ += dx;
    y_ += dy;
    // Ensure the player stays within the screen boundaries
    if (x_ < 0) x_ = 0;
    if (x_ + symbol_.length() > COLS) x_ = COLS - symbol_.length();
}

    void draw() const 
    {       
        for (size_t i = 0; i < symbol_.length(); ++i) 
        {
            mvaddch(y_, x_ + i, symbol_[i]);
        }
    }

    int x() const { return x_; }
    int y() const { return y_; }
    const std::string& symbol() const { return symbol_; }

private:
    int x_;
    int y_;
    std::string symbol_;
};

class Alien 
{
public:
    Alien(int x, int y, std::string symbol)
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

    void draw() const 
    {
        for (int i = 0; i < symbol_.size(); ++i) 
        {
            mvaddch(y_, x_ + i, symbol_[i]);
        }
    }

    int x() const { return x_; }
    int y() const { return y_; }
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

    void draw() const 
    {
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

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    //timeout(10);
    
    refresh(); //possible fuck up
    
    /*// Initialize the player
    Player player((COLS - 1) / 2, LINES - 2, '@');*/
    Player player((COLS - 3) / 2, LINES - 2, "/_\\");

    // Initialize the aliens
    std::vector<Alien> aliens;
    for (int i = 0; i < 4; ++i)
    {
    for (int j = 0; j < 10; ++j) 
    {
        aliens.emplace_back(5 + j * 4, 2 + i * 4, "  -@|__|@-  ");
    }
}

    // Initialize the bullets
    std::vector<Bullet> bullets;

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
        for (auto it = bullets.begin(); it != bullets.end();) {
            it->move();
            it->draw();
            if (it->y() <= 0 || it->y() >= LINES - 1) {
                it = bullets.erase(it);
            } else {
                ++it;
            }
        }

        // Collision detection
        for (auto it = bullets.begin(); it != bullets.end();) 
        {
            bool hit = false;
            for (auto jt = aliens.begin(); jt != aliens.end();) 
            {
                if (it->x() == jt->x() && it->y() == jt->y()) 
                {
                    jt = aliens.erase(jt);
                    hit = true;
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
        usleep(10000);
    }

    // Clean up ncurses
    endwin();

    return 0;
}
