/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** ai
*/

#include "enemy.h"
#include "engine.h"
#include <SFML/Graphics/CircleShape.h>
#include <stdlib.h>

int is_player_in_range(player_t *player, enemy_t *enemy)
{
    float enemy_radius = sfCircleShape_getRadius(enemy->weapon->range);
    float range_x = enemy->position.x;
    float range_y = enemy->position.y;
    float dx = player->pos.x - range_x;
    float dy = player->pos.y - range_y;
    float dsquared = (dx * dx) + (dy * dy);
    float rsquared = (enemy_radius * enemy_radius);

    if (dsquared <= rsquared)
        return 1;
    else
        return 0;
}

bool compute_accuracy(enemy_t *enemy)
{
    int acc_seed = rand() % 100;

    if (acc_seed <= enemy->weapon->accuracy)
        return true;
    return false;
}

int compute_damage(enemy_t *enemy)
{
    int dmg_seed = rand() % 2 - 1;
    int dmg_amount = rand() % 15;
    int dmg = enemy->weapon->damage;

    if (dmg_seed != 0)
        dmg += dmg_seed * dmg_amount;
    return dmg;
}

void apply_damage(player_t *player, enemy_t *enemy)
{
    if (is_player_in_range(player, enemy) && compute_accuracy(enemy)) {
        player->stats->health -= compute_damage(enemy);
    }
}
