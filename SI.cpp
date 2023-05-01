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
        Alien(0 * 20, 0, max_x, 1),
        Alien(1 * 20, 0, max_x, 1),
        Alien(2 * 20, 0, max_x, 1),
        Alien(3 * 20, 0, max_x, 1),
        Alien(4 * 20, 0, max_x, 1)
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
