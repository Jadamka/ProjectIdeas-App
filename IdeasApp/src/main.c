#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "project.h"
#include "menus.h"
#include "utils.h"

void InitCurses();

int main(int argc, char* argv[])
{
    int projectsCount = 0;
    project_t *projects = NULL;

    projects = ReadProjects("data.ini", &projectsCount);
    if(projects == NULL){
        printf("Failed to load projects\n");
        return 1;
    }

    InitCurses();

    char *mainMenuOptions[] =
        {
            "Show ideas",
            "Exit",
        };
    char *difficultyMenuOptions[] =
        {
            "Beginner",
            "Intermediate",
            "Advanced",
            "Back",
        };

    menu_t *menus[TOTAL_MENUS];
    menus[MAIN_MENU] = CreateMenu(MAIN_MENU, mainMenuOptions, ARRAY_SIZE(mainMenuOptions));
    menus[DIFFICULTY_MENU] = CreateMenu(DIFFICULTY_MENU, difficultyMenuOptions, ARRAY_SIZE(difficultyMenuOptions)); 
    menus[PROJECTS_MENU] = NULL;
    menus[SHOW_DESCRIPTION] = NULL;

    int menuIndex = 0; // main menu
    while(menuIndex != -1){
        switch(menuIndex){
            case MAIN_MENU:
                menuIndex = menus[menuIndex]->ShowMenu(menus[menuIndex]);
                break;
            case DIFFICULTY_MENU:
                menuIndex = menus[menuIndex]->ShowMenu(menus[menuIndex]);
                break;
            case PROJECTS_MENU:
                // HAVE OPTIONAL ARGUMENT IN SHOWMENU FUNCTION FOR PROJECTS LIST
                // menuIndex = ProjectsMenu();
                break;
            // MAYBE GET RID OF THIS SINCE IT IS NOT A MENU
            case SHOW_DESCRIPTION:
                // menuIndex = ShowDescription();
                break;
        }
    }

    endwin();

    FreeProjects(projects, &projectsCount);
    for(int i = 0; i < TOTAL_MENUS; i++){
        if(menus[i] != NULL){
            FreeMenu(menus[i]);
        }
    }
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
        init_color(COLOR_BLUE, 0, 0, 1000);
    }

    init_pair(1, COLOR_BLUE, COLOR_WHITE);
    attron(COLOR_PAIR(1) | A_REVERSE);
    mvprintw(LINES-1, 0, "Press F1 to Exit.");
    attroff(COLOR_PAIR(1) | A_REVERSE);

    refresh();
}




