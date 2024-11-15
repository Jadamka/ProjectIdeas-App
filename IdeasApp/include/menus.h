#ifndef DEF_MENUS_H
#define DEF_MENUS_H

#include <ncurses.h>
#include <menu.h>

#include "project.h"

// serves for an array as an index for each menu (menu[MAIN_MENU]->ShowMenu())
typedef enum menuType
{
    MAIN_MENU = 0,
    DIFFICULTY_MENU = 1,
    PROJECTS_MENU = 2,
    SHOW_DESCRIPTION = 3, // not a menu, but who cares
    TOTAL_MENUS, // number of menus
} menuType_t;

// maybe add title ? char title[80] ???
typedef struct menu
{
    int countOfChoices;
    menuType_t menuType;
    ITEM **items;
    MENU *menu;
    WINDOW *win;
    int (*ShowMenu)(struct menu *self);
} menu_t;

int show_menu(struct menu *menu);
menu_t *create_menu(menuType_t menuType, char **choices, int countOfChoices, project_t *projects);

void free_mymenu(menu_t *menu);

#endif
