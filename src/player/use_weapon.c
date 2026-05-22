/*
** EPITECH PROJECT, 2026
** use_weapon
** File description:
** it uses le weapon
*/

#include "engine.h"
#include "event.h"
#include <SFML/Audio/Sound.h>
#include <SFML/Audio/Types.h>
#include <stdint.h>

static void add_new_item(game_t *game)
{
    item_t **inv = game->player->inventory;
    int pos = get_inv_free_spot(game);
    int to_add = rand() % NUM_TEXTURES_ITEMS;

    if (pos == -1)
        return;
    if (to_add == 0)
        inv[pos] = BOMB;
    if (to_add == 1)
        inv[pos] = PIE;
    if (to_add == 2)
        inv[pos] = GUM;
    if (to_add == 3)
        inv[pos] = FLASH;
}

static bool check_enemy_hit(game_t *game, enemy_t *enemy)
{
    sfVector2f temp = game->player->pos;
    sfVector2f dir = game->player->dir_v;
    char result = game->map[(int) temp.x][(int) temp.y];

    while (result == '0' || result == 'P') {
        temp.x += dir.x;
        temp.y += dir.y;
        if (temp.x < 0 || temp.y < 0 || temp.x >= game->map_size.x
            || temp.y >= game->map_size.y)
            return false;
        if ((int) temp.x == (int) enemy->position.x
            && (int) temp.y == (int) enemy->position.y) {
            return true;
        }
        result = game->map[(int) temp.x][(int) temp.y];
    }
    return false;
}

static void hurt_enemy(game_t *game, enemy_t *enemy)
{
    enemy->health -= game->player->weapons[game->player->curr_weapon]->damage;
    game->player->score += 5;
    if (enemy->health <= 0 && enemy->alive) {
        game->map[(int) enemy->position.x][(int) enemy->position.y] = '0';
        add_new_item(game);
        game->player->score += 100;
        enemy->alive = false;
    }
}

void shoot_gun(game_t *game)
{
    player_t *p = game->player;
    weapon_t *curr_weapon = p->weapons[p->curr_weapon];
    bool hit = false;

    if (curr_weapon->ammo <= 0 || curr_weapon->frame != 0)
        return;
    if (curr_weapon->shoot) {
        sfSound_play(curr_weapon->shoot);
    }
    curr_weapon->ammo--;
    curr_weapon->frame = 1;
    game->player->score++;
    for (int i = 0; i < game->enemy_count; i++) {
        hit = check_enemy_hit(game, game->enemies[i]);
        if (hit) {
            hurt_enemy(game, game->enemies[i]);
        }
    }
    return;
}

void reload_gun(game_t *game)
{
    game->player->weapons[game->player->curr_weapon]->ammo =
        game->player->weapons[game->player->curr_weapon]->max_ammo;
}
