/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** weapons
*/

#ifndef WEAPONS_H_
    #define WEAPONS_H_

    #include "enemy.h"

enemy_weapon_t *init_magnum(void);
enemy_weapon_t *init_thompson(void);

weapon_t *init_single_weapon(int ammo, int damage, float rate, char *s_path);


#endif /* !WEAPONS_H_ */
