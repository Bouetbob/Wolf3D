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
    #include <stdbool.h>
    #include "engine.h"

    #define MAX_ENEMIES 64

typedef struct enemy_weapon_s {
    int damage;
    int accuracy;
    int firerate;
    float range;
} enemy_weapon_t;

typedef struct enemy_s {
    int type;
    int health;
    bool alive;
    sfVector2f position;
    enemy_weapon_t *weapon;
    sfVector2f los;
    float fire_timer;
    char tile;
} enemy_t;

typedef struct render_data_s {
    int sprite_w;
    int sprite_h;
    int start_x;
    int end_x;
    int start_y;
    int frame_w;
    int x_offset;
    float trans_y;
    int current_i;
} render_data_t;

enemy_t *init_enemy(int type, sfVector2f *position);
void update_enemies(game_t *game);
bool has_line_of_sight(enemy_t *enemy, player_t *player, game_t *game);
void shoot_player(player_t *player, enemy_t *enemy, game_t *game);
void render_enemies(game_t *game);

#endif /* !ENEMY_H_ */
