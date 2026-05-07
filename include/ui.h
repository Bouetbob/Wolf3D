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



    #define BOMB init_item(game->textures->item_textures[0], 1, "BOMB")
    #define PIE init_item(game->textures->item_textures[1], 1, "PIE")
    #define GUM init_item(game->textures->item_textures[2], 1, "GUM")
    #define FLASH init_item(game->textures->item_textures[3], 1, "FLASH")




    #define NUM_BUTTONS 5

button_t *init_button(char *string, sfVector2f *position, sfVector2f *size,
    bool is_menu);
void draw_button(game_t *game, button_t *button);
void button_event(game_t *game, button_t *button, sfEvent *event);

void change_menu_state(game_t *game);
void print_game_info(game_t *game);
void leave_game(game_t *game);

item_t *init_item(sfTexture *texture, int uses, char *name);
void draw_item(game_t *game, item_t *item);
int amount_of_items(player_t *player);
void item_event(game_t *game, item_t *item, sfEvent *event);
int get_inv_free_spot(game_t *game);

#endif /* !UI_H_ */
