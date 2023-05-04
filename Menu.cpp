#include <ncurses.h>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <string>
#include <vector>

#include "SI.cpp"

int main()
{

    /* NCURSES START */
    initscr();
    noecho();
    cbreak();

    // get screen size

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // create window for input

    WINDOW *menuwin = newwin(6, xMax - 12, yMax - 8, 5);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);

    // make arrow keys usable
    keypad(menuwin, true);

    const char *choices[2];
    choices[0] = "Start New Game";
    choices[1] = "Exit";
    int choice;
    int highlight = 0;

    while (1)
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == highlight)
            {
                wattron(menuwin, A_REVERSE);
            }

            mvwprintw(menuwin, i + 1, 1, " %s", choices[i]);
            wattroff(menuwin, A_REVERSE);
        }

        choice = wgetch(menuwin);

        switch (choice)
        {
        case KEY_UP:
            highlight--;
            if (highlight == -1)
            {
                highlight = 0;
            }
            break;

        case KEY_DOWN:
            highlight++;
            if (highlight == 3)
            {
                highlight = 2;
            }
            break;

        default:
            break;
        }

        if (choice == 10)
        {
            if (highlight == 0)
            {
                clear();
                endwin();
                std::system("clear");  // clear terminal screen
                std::system("c++ SI.cpp -lncurses -o SI.out && ./SI.out");  // compile and run Space Invaders
                initscr();  // reinitialize ncurses after Space Invaders finishes
                noecho();
                cbreak();
                refresh();
                wrefresh(menuwin);
            }
            else
            {
                break;
            }
        }

        printw("Your choice was: %s", choices[highlight]);
    }

    // wait before exiting
    getch();
    endwin();

    return 0;
}
