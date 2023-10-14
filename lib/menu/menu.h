#ifndef MENU_H
#define MENU_H

#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 24

#define MENU_WIDTH 72
#define MENU_HEIGHT 19

typedef struct Game Game;

typedef enum MenuType {
  MENU_TYPE_TRAINER_LIST,
  MENU_TYPE_POKEMON_CENTER,
  MENU_TYPE_POKEMART,
} MenuType;

typedef struct Menu {
  MenuType type;
  int position;
  int (*move)(int move, Game *game);
  void (*render)();
} Menu;

int prepareMenu(MenuType type, Menu *menu);
int destroyMenu(Menu *menu);

#endif