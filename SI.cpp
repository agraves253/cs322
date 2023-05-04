#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "player.h"
#include "alien.h"
#include "bullet.h"

int main() 
{
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(100);

    // Initialize the player
    Player player((COLS - 1) / 2, LINES - 2, '@');

    // Initialize the aliens
    std::vector<Alien> aliens;
    for (int i = 0; i < 4; ++i) 
    {
        for (int j = 0; j < 10; ++j) 
        {
            aliens.emplace_back(5 + j * 4, 2 + i * 4, 'O');
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
        for (auto it = bullets.begin(); it != bullets.end();) 
        {
            it->move();
            it->draw();
            if (it->y() <= 0 || it->y() >= LINES - 1) 
            {
                it = bullets.erase(it);
            } 
            else 
            {
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
            if (hit) {
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
    }

    // Clean up ncurses
    endwin();

    return 0;
}

