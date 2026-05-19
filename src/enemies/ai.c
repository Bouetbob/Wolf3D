/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** ai
*/

#include "enemy.h"
#include "engine.h"
#include "wolf3d.h"
#include <math.h>
#include <stdlib.h>

static int is_player_in_range(player_t *player, enemy_t *enemy)
{
    float dx = player->pos.x - enemy->position.x;
    float dy = player->pos.y - enemy->position.y;
    float dsq = dx * dx + dy * dy;
    float rsq = enemy->weapon->range * enemy->weapon->range;

    return (dsq <= rsq);
}

static bool compute_accuracy(enemy_t *enemy)
{
    int roll = rand() % 100;

    return (roll <= enemy->weapon->accuracy);
}

static int compute_damage(enemy_t *enemy)
{
    int base = enemy->weapon->damage;
    int variance = rand() % 15;
    int sign = -1;

    if (rand() % 2) {
        sign = 1;
    }
    return (base + sign * variance);
}

static void set_dda_steps(float *data, int *grid)
{
    grid[0] = (int) data[0];
    grid[1] = (int) data[1];
    grid[2] = 1;
    grid[7] = (grid[0] + 1.0f - data[0]) * data[5];
    if (data[2] < 0.0f) {
        grid[2] = -1;
        data[7] = (data[0] - grid[0]) * data[5];
    }
    grid[3] = 1;
    grid[8] = (grid[1] + 1.0f - data[1]) * data[6];
    if (data[3] < 0.0f) {
        grid[3] = -1;
        data[8] = (data[1] - grid[1]) * data[6];
    }
}

static void init_dda_data(float *data, int *grid)
{
    data[2] /= data[4];
    data[3] /= data[4];
    data[5] = fabsf(1.0f / data[2]);
    if (data[2] == 0.0f) {
        data[5] = 1e30f;
    }
    data[6] = fabsf(1.0f / data[3]);
    if (data[3] == 0.0f) {
        data[6] = 1e30f;
    }
    set_dda_steps(data, grid);
}

static bool walk_line(game_t *game, float *data, int *grid)
{
    float dist = 0.0f;

    while (dist < data[4]) {
        if (data[7] < data[8]) {
            dist = data[7];
            data[7] += data[5];
            grid[0] += grid[2];
        } else {
            dist = data[8];
            data[8] += data[6];
            grid[1] += grid[3];
        }
        if (dist >= data[4])
            return (true);
        if (is_wall((float) grid[0], (float) grid[1], game))
            return (false);
    }
    return (true);
}

bool has_line_of_sight(enemy_t *enemy, player_t *player, game_t *game)
{
    float data[9];
    int grid[4];

    data[0] = enemy->position.x;
    data[1] = enemy->position.y;
    data[2] = player->pos.x - data[0];
    data[3] = player->pos.y - data[1];
    data[4] = sqrtf(data[2] * data[2] + data[3] * data[3]);
    if (data[4] == 0.0f) {
        return (true);
    }
    init_dda_data(data, grid);
    return (walk_line(game, data, grid));
}

static void apply_enemy_attack(game_t *game, enemy_t *enemy)
{
    float rate = (float) enemy->weapon->firerate;

    if (!has_line_of_sight(enemy, game->player, game))
        return;
    if (compute_accuracy(enemy)) {
        game->player->stats->health -= compute_damage(enemy);
    }
    enemy->fire_timer = 1.0f;
    if (rate > 0.0f) {
        enemy->fire_timer = 1.0f / rate;
    }
}

void update_enemies(game_t *game)
{
    enemy_t *npc;
    int i = 0;

    for (i = 0; i < game->enemy_count; i++) {
        npc = game->enemies[i];
        if (!npc || !npc->alive || npc->health <= 0)
            continue;
        if (!is_player_in_range(game->player, npc)) {
            npc->fire_timer = 1.0f;
            continue;
        }
        npc->fire_timer -= game->timer->timeframe;
        if (npc->fire_timer <= 0.0f)
            apply_enemy_attack(game, npc);
    }
}
