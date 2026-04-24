/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** enemy
*/

#ifndef ENEMY_H_
    #define ENEMY_H_

    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Vector2.h>

typedef struct enemy_weapon_s {
    int damage;
    int accuracy;
    int firerate;
    sfCircleShape *range;
} enemy_weapon_t;

typedef struct enemy_s {
    int type;
    int health;
    sfVector2i position;
    enemy_weapon_t *weapon;
} enemy_t;

#endif /* !ENEMY_H_ */
