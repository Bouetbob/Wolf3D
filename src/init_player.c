/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** init_player
*/

#include "engine.h"
#include "event.h"

void init_player(game_t *game)
{
    player_t *p = game->player;

    init_ui_bar(p, game);
    p->stats = malloc(sizeof(stats_t));
    p->ui_texts = malloc(sizeof(sfText **) * 5);
    p->weapons = malloc(sizeof(weapon_t *) * 3);
    if (!p->stats || !p->ui_texts || !p->weapons)
        exit_with_message("couldn't malloc essentials\n", 2, 84);
    init_ui_texts(game);
    init_weapons(game);
    p->stats->health = 500;
    p->stats->flashlight = false;
    p->angle = 0;
    p->stats->move_speed = MOVESPEED;
    p->FOV = FORMER_FOV;
    p->inventory = malloc(sizeof(item_t *) * INVENTORY_SIZE);
    for (int i = 0; i < INVENTORY_SIZE; i++)
        p->inventory[i] = NULL;
    update_player(p);
}
