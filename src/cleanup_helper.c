/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** cleanup helper
*/

#include "engine.h"
#include "wolf3d.h"

static void free_buttons_content(game_t *game, int i)
{
    if (game->buttons[i]->background)
        sfRectangleShape_destroy(game->buttons[i]->background);
    if (game->buttons[i]->text)
        sfText_destroy(game->buttons[i]->text);
}

void free_buttons(game_t *game)
{
    if (!game->buttons)
        return;
    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (game->buttons[i]) {
            free_buttons_content(game, i);
            free(game->buttons[i]);
        }
    }
    free(game->buttons);
}

void free_weapons(player_t *player)
{
    if (!player->weapons)
        return;
    for (int i = 0; player->weapons[i]; i++) {
        if (player->weapons[i]->sprite)
            sfSprite_destroy(player->weapons[i]->sprite);
        free(player->weapons[i]);
    }
    free(player->weapons);
}
