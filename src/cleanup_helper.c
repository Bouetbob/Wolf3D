/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** cleanup helper
*/

#include "engine.h"
#include "wolf3d.h"
#include <SFML/Audio/Sound.h>
#include <SFML/Audio/SoundBuffer.h>
#include <SFML/Audio/Types.h>

static void free_buttons_content(game_t *game, int i)
{
    const sfTexture *tex;

    if (game->buttons[i]->background) {
        tex = sfRectangleShape_getTexture(game->buttons[i]->background);
        sfRectangleShape_destroy(game->buttons[i]->background);
        if (tex)
            sfTexture_destroy((sfTexture *) tex);
    }
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

static void free_weapon_sprite(weapon_t *weapon)
{
    const sfTexture *tex = sfSprite_getTexture(weapon->sprite);

    sfSprite_destroy(weapon->sprite);
    if (tex)
        sfTexture_destroy((sfTexture *) tex);
}

void free_weapons(player_t *player)
{
    if (!player->weapons)
        return;
    for (int i = 0; player->weapons[i]; i++) {
        if (player->weapons[i]->sprite)
            free_weapon_sprite(player->weapons[i]);
        if (player->weapons[i]->shoot) {
            sfSoundBuffer_destroy(player->weapons[i]->buff);
        }
        free(player->weapons[i]);
    }
    free(player->weapons);
}

static void clean_ui_bar(player_t *player)
{
    const sfTexture *tex = sfRectangleShape_getTexture(player->ui_bar);

    sfRectangleShape_destroy(player->ui_bar);
    player->ui_bar = NULL;
    if (tex)
        sfTexture_destroy((sfTexture *) tex);
}

static void clean_inventory(player_t *player)
{
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (player->inventory[i]) {
            sfRectangleShape_destroy(player->inventory[i]->background);
            free(player->inventory[i]->name);
            free(player->inventory[i]);
        }
    }
    free(player->inventory);
}

void clean_player(player_t *player)
{
    free(player->stats);
    if (player->ui_bar)
        clean_ui_bar(player);
    for (int i = 0; player->ui_texts[i]; i++)
        sfText_destroy(player->ui_texts[i]);
    free(player->ui_texts);
    free_weapons(player);
    clean_inventory(player);
    free(player);
}
