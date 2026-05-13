/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** magnum
*/

#include "weapons.h"
#include <stdlib.h>

enemy_weapon_t *init_magnum(void)
{
    enemy_weapon_t *magnum = malloc(sizeof(enemy_weapon_t));

    magnum->damage = 20;
    magnum->accuracy = 80;
    magnum->firerate = 1;
    magnum->range = 5;
    return magnum;
}
