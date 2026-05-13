/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** thompson
*/

#include "weapons.h"
#include <stdlib.h>

enemy_weapon_t *init_thompson(void)
{
    enemy_weapon_t *thompson = malloc(sizeof(enemy_weapon_t));

    thompson->damage = 5;
    thompson->accuracy = 50;
    thompson->firerate = 10;
    thompson->range = 4;
    return thompson;
}
