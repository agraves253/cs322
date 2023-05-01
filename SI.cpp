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

class Player 
{
public:
  int x, y;
  int max_x;

  Player(int initialX, int initialY, int maxX)
      : x(initialX), y(initialY), max_x(maxX) {}

  void draw() 
  {
    mvaddstr(y, x, " | ");
    mvaddstr(y + 1, x, "/ \\");
  }

  void move_left() 
  {
    if (x > 0) {
      x--;
    }
  }

  void move_right() 
  {
    if (x + 3 < max_x) 
    {
      x++;
    }
  }
};

int main(int argc, char *argv[]) {
  initscr();
  noecho();
  curs_set(FALSE);

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

  Player player(max_x / 2, max_y - 3, max_x);

while (1) 
{
  clear();

  player.draw();

  for (int i = 0; i < aliens.size(); i++) 
  {
    aliens[i].draw();
  }

  refresh();
  usleep(DELAY);

  int ch = getch();
  switch (ch) {
    case 'a':
      player.move_left();
      break;
    case 'd':
      player.move_right();
      break;
    default:
      break;
  }

  for (int i = 0; i < aliens.size(); i++) 
  {
    aliens[i].move(aliens);
  }
}

  endwin();
}
