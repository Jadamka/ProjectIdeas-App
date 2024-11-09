#include "menus.h"
#include "utils.h"

static ITEM **InitItems(char **choices, int countOfChoices)
{
    ITEM **items = (ITEM **)calloc(countOfChoices, sizeof(ITEM *));
    for(int i = 0; i < countOfChoices; i++){
        items[i] = new_item(choices[i], choices[i]);
    }
    items[countOfChoices] = (ITEM *)NULL;

    return items;
}

static MENU *InitMenu(ITEM **items)
{
    MENU *menu = new_menu((ITEM **)items);
    menu_opts_off(menu, O_SHOWDESC);
    set_menu_mark(menu, " > ");

    return menu;
}

static WINDOW *InitMenuWindow(MENU *menu)
{
    WINDOW *win;
    win = newwin(LINES-10, COLS-10, 5, 5);
    keypad(win, TRUE);

    set_menu_win(menu, win);
    set_menu_sub(menu, derwin(win, 6, 38, 3, 1));

    return win;
}


static void PrintInMiddle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{
    int length, x, y;
    float temp;

    if(win == NULL){
        win = stdscr;
    }
    getyx(win, y, x);
    if(startx != 0){
        x = startx;
    }
    if(starty != 0){
        y = starty;
    }
    if(width == 0){
        width = 80;
    }

    length = strlen(string);
    temp = (width - length)/2;
    x = startx + (int)temp;
    mvwprintw(win, y, x, "%s", string);
    refresh();
}

static void DrawMenu(menu_t *menu, char *title)
{
    box(menu->win, 0, 0);
    PrintInMiddle(menu->win, 1, 0, COLS-10, title, 0);
    mvwaddch(menu->win, 2, 0, ACS_LTEE);
    mvwhline(menu->win, 2, 1, ACS_HLINE, COLS-12);
    mvwaddch(menu->win, 2, COLS-11, ACS_RTEE);
    refresh();

    post_menu(menu->menu);
    wrefresh(menu->win);
}

static int MainMenu(menu_t *menu)
{
    DrawMenu(menu, "Main Menu");

    int c;
    int quit = MAIN_MENU;
    while(quit == MAIN_MENU && ((c = wgetch(menu->win)) != KEY_F(1))){
        switch(c){
            case KEY_DOWN:
            case 'j':
                menu_driver(menu->menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
            case 'k':
                menu_driver(menu->menu, REQ_UP_ITEM);
                break;
            case 10: // ENTER 
                int selected_item = item_index(current_item(menu->menu));
                switch(selected_item){
                    case 0: // Show projects
                        quit = DIFFICULTY_MENU;
                        break;
                    case 1: // Exit
                        quit = -1;
                        break;
                }
                pos_menu_cursor(menu->menu);
                break;
        }
        wrefresh(menu->win);
    }

    if(c == KEY_F(1)){
        quit = -1;
    }
    // should be wclear(menu->win) but that would make items not show when returning until I press UP/DOWN key
    // so i will use unpost_menu intead... not sure if it is okay tho
    unpost_menu(menu->menu);
    return quit;
}

static int DifficultyMenu(menu_t *menu)
{
    DrawMenu(menu, "Difficulty Menu");

    int c;
    int quit = DIFFICULTY_MENU;
    while(quit == DIFFICULTY_MENU && ((c = wgetch(menu->win)) != KEY_F(1))){ 
        switch(c){
            case KEY_DOWN:
            case 'j':
                menu_driver(menu->menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
            case 'k':
                menu_driver(menu->menu, REQ_UP_ITEM);
                break;
            case 10: // ENTER 
                int selected_item = item_index(current_item(menu->menu));
                switch(selected_item){
                    case 0:
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3: // Back
                        quit = MAIN_MENU;
                        break;
                }
                pos_menu_cursor(menu->menu);
                break;
        }
        wrefresh(menu->win);
    }

    if(c == KEY_F(1)){
        quit = -1;
    }
    unpost_menu(menu->menu);
    return quit;
}

void FreeMenu(menu_t *menu)
{
    unpost_menu(menu->menu);
    free_menu(menu->menu);
    for(int i = 0; i < menu->countOfChoices; i++){
        free_item(menu->items[i]);
    }
    free(menu->items);
    delwin(menu->win);

    free(menu);
}

menu_t *CreateMenu(menuType_t menuType, char **choices, int countOfChoices)
{
    menu_t *menu = (menu_t *)malloc(sizeof(menu_t));

    menu->countOfChoices = countOfChoices;
    menu->menuType = menuType;
    menu->items = InitItems(choices, countOfChoices);
    menu->menu = InitMenu(menu->items);
    menu->win = InitMenuWindow(menu->menu);
    menu->ShowMenu = &ShowMenu;

    return menu;
}

int ShowMenu(struct menu_t *menu)
{
    int returnVal = menu->menuType;

    switch(returnVal){
        case MAIN_MENU:
            returnVal = MainMenu(menu);
            break;
        case DIFFICULTY_MENU:
            returnVal = DifficultyMenu(menu);
            break;
        case PROJECTS_MENU:
            break;
        case SHOW_DESCRIPTION:
            break;
    }

    returnVal;
}














