/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** init_enemies
*/

#include "enemy.h"
#include "weapons.h"
#include <SFML/System/Vector2.h>
#include <stdlib.h>

static int setup_enemy_stats(enemy_t *enemy, int type)
{
    if (type == 1) {
        enemy->health = 100;
        enemy->weapon = init_magnum();
        enemy->type = 1;
        return (0);
    }
    if (type == 2) {
        enemy->health = 150;
        enemy->weapon = init_thompson();
        enemy->type = 2;
        return (0);
    }
    return (84);
}

enemy_t *init_enemy(int type, sfVector2f *position)
{
    enemy_t *enemy = malloc(sizeof(enemy_t));

    if (!enemy)
        return (NULL);
    enemy->position.x = position->x + 0.5;
    enemy->position.y = position->y + 0.5;
    enemy->alive = true;
    enemy->fire_timer = 0.0f;
    enemy->los = (sfVector2f){0.0f, 0.0f};
    if (setup_enemy_stats(enemy, type) == 84) {
        free(enemy);
        return (NULL);
    }
    return (enemy);
}
