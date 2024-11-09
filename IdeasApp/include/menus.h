#ifndef DEF_MENUS_H
#define DEF_MENUS_H

#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>

// maybe add title ?
typedef struct menu_t
{
    int countOfChoices;
    ITEM **items;
    MENU *menu;
    WINDOW *win;
} menu_t;

// serves for an array as an index for each menu (menu[MAIN_MENU]->ShowMenu())
// add ShowMenu() function
typedef enum menuType_t
{
    MAIN_MENU = 0,
    DIFFICULTY_MENU = 1,
    PROJECTS_MENU = 2,
    SHOW_DESCRIPTION = 3, // not a menu, but who cares
    TOTAL_MENUS; // number of menus
} menuType_t;

// each menu could return int from enum on which menu should open next ??? Loop and all logic would be inside main
void MainMenu();
int DifficultyMenu();
int ProjectsMenu();
void ShowDescription();

menu_t *CreateMainMenu();
menu_t *CreateDifficultyMenu();
menu_t *CreateProjectsMenu();

void PrintInMiddle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
ITEM **InitItems(char **choices);
MENU *InitMenu(ITEM **items);
WINDOW *InitMenuWindow(MENU *menu);
void DrawMenu(menu_t *menu, char *title);
void ClearMenu(menu_t *menu);

#endif
