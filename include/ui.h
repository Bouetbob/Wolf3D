/*
** EPITECH PROJECT, 2026
** buttons
** File description:
** button file
*/

#include "engine.h"
#include "my.h"
#include <SFML/Graphics.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/PrimitiveType.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/System.h>
#include <SFML/System/Time.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window.h>
#include <SFML/Window/Event.h>
#include <stdbool.h>
#include <unistd.h>

#ifndef UI_H_
    #define UI_H_

    #define BOMB init_item(game->tex->item_tex[0], 1, "BOMB", (void *) bomb)
    #define PIE init_item(game->tex->item_tex[1], 1, "PIE", (void *) pie)
    #define GUM init_item(game->tex->item_tex[2], 1, "GUM", NULL)
    #define FLASH init_item(game->tex->item_tex[3], 1, "FLASH", NULL)

    #define NUM_BUTTONS 5

typedef struct button_params_s {
    char *string;
    sfVector2f *position;
    sfVector2f *size;
    bool is_menu;
} button_params_t;

button_t *init_button(button_params_t *params, game_t *game);
void draw_button(game_t *game, button_t *button);
void button_event(game_t *game, button_t *button, sfEvent *event);

void change_menu_state(game_t *game);
void print_game_info(game_t *game);
void leave_game(game_t *game);

item_t *init_item(sfTexture *texture, int uses, char *name,
    void(function)(void *));
sfRectangleShape *init_background(sfTexture *texture);
void draw_item(game_t *game, item_t *item);
int amount_of_items(player_t *player);
void item_event(game_t *game, item_t *item, sfEvent *event);
int get_inv_free_spot(game_t *game);

void draw_ui(game_t *game);
void update_ui_scale(game_t *game);
void init_ui_bar(player_t *player, game_t *game);

void change_window_size(game_t *game, int x, int y);

void update_text(sfText *item, char *new_string);
sfText *init_text_item(char *string, sfVector2f *position,
    int size, game_t *game);
void get_string_from_num(int number, sfText *item);

void init_weapons(game_t *game);

void bomb(game_t *game);
void pie(game_t *game);

#endif /* !UI_H_ */
