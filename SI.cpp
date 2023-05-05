#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>
#include "alien.h"
#include "bullet.h"
#include "player.h"


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
