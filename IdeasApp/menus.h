#ifndef DEF_MENUS_H
#define DEF_MENUS_H

// put this define into utils.h
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>

void MainMenu();
void DifficultyMenu();
void ProjectsMenu();
void ShowDescription();
void print_in_middle(WINDOW* win, int starty, int startx, int width, char* string, chtype color);

#endif
