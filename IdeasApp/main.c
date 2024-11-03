#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void initCurses();

int main()
{
    initCurses();

    getch();
    endwin();
    return 0;
}

void initCurses()
{
    initscr();
    start_color();
    noecho();

    if(can_change_color()){
        init_color(COLOR_WHITE, 1000, 1000, 1000);
        init_color(COLOR_BLACK, 0, 0, 0);
    }

    printw("Hello World");
    refresh();
}
