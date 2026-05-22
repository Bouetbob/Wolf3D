/*
** EPITECH PROJECT, 2026
** weapon_volume
** File description:
** volume i guess
*/

#include "engine.h"
#include <SFML/Audio/Sound.h>

void lowest_volume(game_t *game)
{
    weapon_t **weapons = game->player->weapons;

    for (int i = 0; weapons[i]; i++) {
        sfSound_setVolume(weapons[i]->shoot, 20);
    }
}

void lower_volume(game_t *game)
{
    weapon_t **weapons = game->player->weapons;

    for (int i = 0; weapons[i]; i++) {
        sfSound_setVolume(weapons[i]->shoot, 40);
    }
}

void mid_volume(game_t *game)
{
    weapon_t **weapons = game->player->weapons;

    for (int i = 0; weapons[i]; i++) {
        sfSound_setVolume(weapons[i]->shoot, 60);
    }
}

void higher_volume(game_t *game)
{
    weapon_t **weapons = game->player->weapons;

    for (int i = 0; weapons[i]; i++) {
        sfSound_setVolume(weapons[i]->shoot, 80);
    }
}

void highest_volume(game_t *game)
{
    weapon_t **weapons = game->player->weapons;

    for (int i = 0; weapons[i]; i++) {
        sfSound_setVolume(weapons[i]->shoot, 100);
    }
}
