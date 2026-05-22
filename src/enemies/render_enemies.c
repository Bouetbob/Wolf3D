/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** render_enemies
*/

#include "enemy.h"
#include "engine.h"
#include "wolf3d.h"
#include <math.h>
#include <stdlib.h>

static void draw_stripe(game_t *game, sfSprite *sprite, sfTexture *tex,
    render_data_t *d)
{
    sfVector2u tex_size = sfTexture_getSize(tex);
    int tex_x;
    sfIntRect rect;

    tex_x =
        (int) ((d->current_i - d->start_x) * (float) d->frame_w / d->sprite_w);
    rect = (sfIntRect) {d->x_offset + tex_x, 0, 1, (int) tex_size.y};
    sfSprite_setTextureRect(sprite, rect);
    sfSprite_setScale(sprite,
        (sfVector2f) {1.0f, (float) d->sprite_h / tex_size.y});
    sfSprite_setPosition(sprite,
        (sfVector2f) {(float) d->current_i, (float) d->start_y});
    sfRenderWindow_drawSprite(game->window, sprite, NULL);
}

static void compute_sprite_pos(game_t *game, render_data_t *d, float tx,
    float ty)
{
    int screen_x;

    d->trans_y = ty;
    d->sprite_h = abs((int) (game->win_s.y / ty));
    d->sprite_w = d->sprite_h;
    screen_x = (int) ((game->win_s.x / 2.0f) * (1.0f + tx / ty));
    d->start_y = game->win_s.y / 2 - d->sprite_h / 2 + d->sprite_h / 4;
    d->start_x = screen_x - d->sprite_w / 2;
    d->end_x = screen_x + d->sprite_w / 2;
}

static void render_loop(game_t *game, enemy_t *enemy, sfTexture *tex,
    render_data_t *d)
{
    sfSprite *sprite = sfSprite_create();

    if (!sprite)
        return;
    sfSprite_setTexture(sprite, tex, sfFalse);
    d->x_offset = (enemy->fire_timer < 0.1f) ? d->frame_w : 0;
    for (int i = d->start_x; i < d->end_x; i++) {
        if (i < 0 || i >= game->win_s.x || d->trans_y >= game->z_buffer[i])
            continue;
        d->current_i = i;
        draw_stripe(game, sprite, tex, d);
    }
    sfSprite_destroy(sprite);
}

static void render_one_enemy(game_t *game, enemy_t *enemy, sfTexture *tex,
    int frame_w)
{
    player_t *p = game->player;
    float dx = enemy->position.x - p->pos.x;
    float dy = enemy->position.y - p->pos.y;
    float fov_s = tan(p->FOV / 2.0f);
    float inv_det = 1.0f
        / ((-p->dir_v.y * fov_s) * p->dir_v.y
        - p->dir_v.x * (p->dir_v.x * fov_s));
    float tx = inv_det * (p->dir_v.y * dx - p->dir_v.x * dy);
    float ty =
        inv_det * (-(p->dir_v.x * fov_s) * dx + (-p->dir_v.y * fov_s) * dy);
    render_data_t d;

    if (ty <= 0.01f)
        return;
    d.frame_w = frame_w;
    compute_sprite_pos(game, &d, tx, ty);
    render_loop(game, enemy, tex, &d);
}

static float get_enemy_dist(enemy_t *enemy, game_t *game)
{
    float dx = enemy->position.x - game->player->pos.x;
    float dy = enemy->position.y - game->player->pos.y;

    return dx * dx + dy * dy;
}

static void swap_enemies(enemy_t **sorted, int j)
{
    enemy_t *tmp = sorted[j];

    sorted[j] = sorted[j + 1];
    sorted[j + 1] = tmp;
}

static void bubble_pass(enemy_t **sorted, int limit, game_t *game)
{
    for (int j = 0; j < limit; j++) {
        if (get_enemy_dist(sorted[j], game)
            < get_enemy_dist(sorted[j + 1], game))
            swap_enemies(sorted, j);
    }
}

static sfTexture *get_enemy_texture(game_t *game, enemy_t *enemy)
{
    if (enemy->type == 2)
        return game->enemy_textures[1];
    return game->enemy_textures[0];
}

static int render_enemies_helper(game_t *game, enemy_t *sorted[MAX_ENEMIES],
    int count)
{
    for (int e = 0; e < game->enemy_count; e++) {
        if (game->enemies[e] && game->enemies[e]->alive) {
            sorted[count] = game->enemies[e];
            count++;
        }
    }
    return count;
}

void render_enemies(game_t *game)
{
    enemy_t *sorted[MAX_ENEMIES];
    int count = 0;
    int frame_w;
    sfTexture *tex;

    count = render_enemies_helper(game, sorted, count);
    for (int i = 0; i < count - 1; i++)
        bubble_pass(sorted, count - i - 1, game);
    for (int e = 0; e < count; e++) {
        if (!sorted[e])
            continue;
        tex = get_enemy_texture(game, sorted[e]);
        if (!tex)
            continue;
        frame_w = sfTexture_getSize(tex).x / 2;
        render_one_enemy(game, sorted[e], tex, frame_w);
    }
}
