#include <ncurses.h>
#include <unistd.h>

#define DELAY 60000

class Alien
{
public:
    int x, y;
    int max_x;
    int direction;

    Alien(int initialX, int initialY, int maxX, int direction)
    :x(initialX), y(initialY), max_x(maxX), direction(direction){}

    void draw()
    {
        mvaddstr(y-1, x, "   | ");
        mvaddstr(y, x, " _/\\_");
        mvaddstr(y+1, x , "/____\\");
    }

    void move()
    {
        int next_x = x + direction;

        if(next_x+10 >= max_x || next_x < 0 )
        {
            direction*= -1;
        }
        else
        {
            x+=direction;
        }
    }
};

int main(int argc, char *argv[])
{
    initscr();
    noecho();
    curs_set(FALSE);

    // Global var 'stdscr is created by the call to 'initscr()'
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int num_aliens = 5;
    Alien aliens[num_aliens] = {
        Alien(0, 0, max_x, 1),
        Alien(20, 0, max_x, 1),
        Alien(40, 0, max_x, 1),
        Alien(60, 0, max_x, 1),
        Alien(80, 0, max_x, 1)
    };
    
    while(1)
    {
        clear();

        for(int i=0; i<num_aliens; i++)
        {
            aliens[i].draw();
        }

        refresh();
        usleep(DELAY);

        for(int i=0; i<num_aliens; i++)
        {
            aliens[i].move();
        }
    }

    endwin();
}
