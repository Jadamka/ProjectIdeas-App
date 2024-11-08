#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>

#include "project.h"
#include "menus.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void InitCurses();

int main(int argc, char* argv[])
{
    int projectsCount = 0;
    Project* projects = NULL;

    projects = ReadProjects("data.ini", &projectsCount);
    if(projects == NULL){
        printf("Failed to load projects\n");
        return 1;
    }

    InitCurses();

    MainMenu();

    getch();
    endwin();

    FreeProjects(projects, &projectsCount);
    return 0;
}

void InitCurses()
{
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    if(can_change_color()){
        init_color(COLOR_WHITE, 1000, 1000, 1000);
        init_color(COLOR_BLACK, 0, 0, 0);
    }

    refresh();
}




