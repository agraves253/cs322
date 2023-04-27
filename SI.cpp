#include <ncurses.h>
#include <thread>
#include <unistd.h>
#define DELAY 10000

class Alien
{

int x, y;
int max_x;
int direction;

public:
        Alien(int initialX, int initialY, int maxX, int direction)
        :x(initialX), y(initialY), max_x(maxX), direction(direction){}

        void draw()
        {
                mvaddstr(y-1, x, "  | ");
                mvaddstr(y, x, "_/\\_");
                mvaddstr(y+1, x, "/___\\");
                refresh();
        }

        void move()
        {
                int next_x = x + direction;

                if(next_x+10 >= max_x || max_x < 0)
                {
                        direction *= -1;
                }
                else
                {
                        x+=direction;
                }
        }
};

int main(int argc, char *argv[])
{
        //initializes ncurses
        initscr();
        noecho();
        curs_set(FALSE);

        //get dimensions of screen
        int max_y, max_x;

        //getmaxyx(stdscr, max_y, max_x);

        //populate aliens
        int number_aliens = 10;

        Alien aliens[] =
        {
                Alien(0,0,max_x,1),
                Alien(20,0,max_x,-1),
                Alien(40,0,max_x,1),
        };

        while(1)
        {
                clear();

                getmaxyx(stdscr, max_y, max_x);

                //draw aliens
                for(int i = 0; i < number_aliens; i++)
                {
                        aliens[i].draw();
                }
                refresh();
                usleep(DELAY);
                //refresh alien position
                for(int i = 0; i < number_aliens; i++)
                {
                        aliens[i].move();
                }



        }

        endwin();
}
