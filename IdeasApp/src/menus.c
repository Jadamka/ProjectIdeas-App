#include "menus.h"
#include "utils.h"

ITEM **InitItems(char** choices)
{
    // since choices are passed as ** it needs to call this macro
    int countOfChoices = ARRAY_SIZE_2P(choices);
    ITEM **items = (ITEM **)calloc(countOfChoices, sizeof(ITEM *));
    for(int i = 0; i < countOfChoices; i++){
        items[i] = new_item(choices[i], choices[i]);
    }

    return items;
}

MENU *InitMenu(ITEM **items)
{
    MENU *menu = new_menu((ITEM **)items);
    menu_opts_off(menu, O_SHOWDESC);
    set_menu_mark(menu, " > ");

    return menu;
}

WINDOW *InitMenuWindow(MENU *menu)
{
    WINDOW *win;
    win = newwin(LINES-10, COLS-10, 5, 5);
    keypad(win, TRUE);

    set_menu_win(menu, win);
    set_menu_sub(menu, derwin(win, 6, 38, 3, 1));

    return win;
}

void DrawMenu(menu_t *menu, char *title)
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

void ClearMenu(menu_t *menu)
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

void PrintInMiddle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
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

void MainMenu()
{
    char *choices[] = 
    {
            "Show projects",
            "Exit",
            (char *)NULL,
    };

    int c;
    ITEM **my_items;
    MENU *my_menu;
    WINDOW *my_menu_win;

    my_items = InitItems(choices);
    my_menu = InitMenu(my_items);
    my_menu_win = InitMenuWindow(my_menu);

    DrawMenu(my_menu_win, my_menu, "Main Menu");
    wrefresh(my_menu_win);

    int quit = 0;
    while((c = wgetch(my_menu_win)) != KEY_F(1)){
        switch(c){
            case KEY_DOWN:
            case 'j':
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
            case 'k':
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 10: // ENTER 
                int selected_item = item_index(current_item(my_menu));
                switch(selected_item){
                    case 0: // Show projects
                        quit = DifficultyMenu();
                        DrawMenu(my_menu_win, my_menu, "Main Menu");
                        break;
                    case 1: // Exit
                        quit = 1;
                        break;
                }
                pos_menu_cursor(my_menu);
                break;
        }
        wrefresh(my_menu_win);
        if(quit == 1){
            break;
        }
    }

    wclear(my_menu_win);
    ClearMenu(my_menu_win, my_menu, my_items, choices);
}

int DifficultyMenu()
{
    char *choices[] = 
    {
            "Beginner",
            "Intermediate",
            "Advanced",
            "Back",
            (char *)NULL,
    };

    int c;
    ITEM **my_items;
    MENU *my_menu;
    WINDOW *my_menu_win;

    my_items = InitItems(choices);
    my_menu = InitMenu(my_items);
    my_menu_win = InitMenuWindow(my_menu);

    DrawMenu(my_menu_win, my_menu, "Difficulty Menu");
    wrefresh(my_menu_win);

    int quit = 0;
    while((c = wgetch(my_menu_win)) != KEY_F(1)){
        switch(c){
            case KEY_DOWN:
            case 'j':
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
            case 'k':
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 10: /* ENTER */
                int selected_item = item_index(current_item(my_menu));
                switch(selected_item){
                    case 0: /* All difficulties */
                    case 1:
                    case 2:
                        break;
                    case 3: /* Exit */
                        quit = 1;
                        break;
                }
                pos_menu_cursor(my_menu);
                break;
        }
        wrefresh(my_menu_win);
        if(quit == 1){
            break;
        }
    }

    wclear(my_menu_win);
    ClearMenu(my_menu_win, my_menu, my_items, choices);

    return (c == KEY_F(1));
}

menu_t *CreateMainMenu()
{
    char *choices[] = 
        {
            "Show projects",
            "Exit",
            (char *)NULL,
        };

    menu_t *mainMenu = (menu_t *)malloc(sizeof(menu_t));

    mainMenu->countOfChoices = ARRAY_SIZE(choices);
    mainMenu->items = InitItems(choices);
    mainMenu->menu = InitMenu(mainMenu->items);
    mainMenu->win = InitMenuWindow(mainMenu->menu);

    return mainMenu;
}

menu_t *CreateDifficultyMenu()
{
    char *choices[] =
        {
            "Beginner",
            "Intermediate",
            "Advanced",
            (char *)NULL,
        };

    menu_t *difficultyMenu = (menu_t *)malloc(sizeof(menu_t));

    difficultyMenu->countOfChoices = ARRAY_SIZE(choices);
    difficultyMenu->items = InitItems(choices);
    difficultyMenu->menu = InitMenu(difficultyMenu->items);
    difficultyMenu->win = InitMenuWindow(difficultyMenu->menu);

    return difficultyMenu;
}

















