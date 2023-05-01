#include <array>
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
      : x(initialX), y(initialY), max_x(maxX), direction(direction) {}

  void draw() 
  {
    mvaddstr(y - 1, x, "   | ");
    mvaddstr(y, x, " _/\\_");
    mvaddstr(y + 1, x, "/____\\");
  }

  void move(std::array<Alien, 5>& aliens) 
  {
    int next_x = x + direction;

    if (next_x + 10 >= max_x || next_x < 0) 
    {
      // Change the direction of each alien in the array
      for (int i = 0; i < aliens.size(); i++) 
      {
        aliens[i].direction *= -1;
      }
      // Move each alien in the opposite direction after changing direction
      for (int i = 0; i < aliens.size(); i++) 
      {
        aliens[i].x += aliens[i].direction;
      }
    } 
    else 
    {
      x += direction;
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

  std::array<Alien, 5> aliens = 
  {
    {
      Alien(0 * 20, 0, max_x, 1),
      Alien(1 * 20, 0, max_x, 1),
      Alien(2 * 20, 0, max_x, 1),
      Alien(3 * 20, 0, max_x, 1),
      Alien(4 * 20, 0, max_x, 1),
    }
  };

  while (1) 
  {
    clear();
    refresh();

    for (int i = 0; i < aliens.size(); i++) 
    {
      aliens[i].draw();
    }

     usleep(DELAY);

    for (int i = 0; i < aliens.size(); i++) 
    {
      aliens[i].move(aliens);
    }
  }

  endwin();
}
