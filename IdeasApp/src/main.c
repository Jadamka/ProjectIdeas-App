#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "project.h"
#include "menus.h"
#include "utils.h"

void init_curses();

int main(int argc, char* argv[])
{
    int projectsCount = 0;
    project_t *projects = NULL;

    projects = read_projects("data/data.ini", &projectsCount);
    if(projects == NULL){
        printf("Failed to load projects\n");
        return 1;
    }

    init_curses();

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
    char *projectsMenuOptions[projectsCount+1];
    for(int i = 0; i < projectsCount; i++){
        projectsMenuOptions[i] = projects[i].name;
    }
    projectsMenuOptions[projectsCount] = "Back";

    menu_t *menus[TOTAL_MENUS];
    menus[MAIN_MENU] = create_menu(MAIN_MENU, mainMenuOptions, ARRAY_SIZE(mainMenuOptions), NULL);
    menus[DIFFICULTY_MENU] = create_menu(DIFFICULTY_MENU, difficultyMenuOptions, ARRAY_SIZE(difficultyMenuOptions), NULL); 
    menus[PROJECTS_MENU] = create_menu(PROJECTS_MENU, projectsMenuOptions, projectsCount+1, projects);
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
                menuIndex = menus[menuIndex]->ShowMenu(menus[menuIndex]);
                break;
            // this will show text in the window and when enter is pressed it will go back
            case SHOW_DESCRIPTION:
                // menuIndex = ShowDescription();
                break;
        }
    }

    endwin();

    free_projects(projects, &projectsCount);
    for(int i = 0; i < TOTAL_MENUS; i++){
        if(menus[i] != NULL){
            free_mymenu(menus[i]);
        }
    }
    return 0;
}

void init_curses()
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




