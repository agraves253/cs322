#include <ncurses.h>
#include <unistd.h>
#include <vector>

#define DELAY 60000

class Alien
{
	public:
		Alien(int x, int y, int max_x, int max_y, int direction)
			: x_(x), y_(y), max_x_(max_x), max_y_(max_y), direction_(direction) {}

		void update()
		{
			mvaddstr(y_-1,x_, "  | ");
			mvaddstr(y_, x_, " _/\\_");
			mvaddstr(y_+, x_+, "/____\\");
			
			x_ +=direction_;
			if(x_ <= 0 || x_ >= max_x_ -5)
			{
				direction_ =-direction_;
			}
		}

	private:
		int x_;
		int y_;
		int max_x_;
		int max_y_;
		int direction_;
};


class Player
{
	public:
		Player(int x, int y, int max_x, int max_y)
			: x_(x), y_(y), max_x_(max_x), max_y_(max_y) {}

		void moveLeft()
		{
			if (x_ > 0)
			{
				x_--;
			}
		}

		void moveRight()
		{
			if (x_ < max_x_ - 6)
			{
				x_++;
			}
		}


		void draw() const
		{
			mvaddstr(y_, -1, x_, "  | ");
			mvaddstr(y_, x_, "/\\_");
			mvaddstr(y_+1,x_, "/___\\");
		}

	private:
		int x_;
		int y_;
		int max_x_;
		int max_y_;
};


int main(int argc, char *argv[])
{	
	initscr();
	noecho();
	curs_set(FALSE);

	endwin();
	return 0;
}	
