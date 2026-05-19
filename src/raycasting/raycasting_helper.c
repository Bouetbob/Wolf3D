/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** raycasting helper
*/

#include "engine.h"
#include "math.h"
#include "stdlib.h"

int is_wall(float x, float y, game_t *game)
{
    int map_x = (int) x;
    int map_y = (int) y;

    if (map_x < 0 || map_y < 0 || map_x >= game->map_size.x
        || map_y >= game->map_size.y)
        return 1;
    return (game->map[map_y][map_x] > '0' && game->map[map_y][map_x] <= '9');
}

static void apply_intensity(sfColor *c, float intensity)
{
    c->r = (sfUint8)(c->r * intensity);
    c->g = (sfUint8)(c->g * intensity);
    c->b = (sfUint8)(c->b * intensity);
}

static void get_ray_dirs(game_t *game, ray_data_t *rd)
{
    float fov = tanf(game->player->FOV / 2.0f);
    float px = -game->player->dir_v.y * fov;
    float py = game->player->dir_v.x * fov;
    float rdx0_raw = game->player->dir_v.x - px;
    float rdy0_raw = game->player->dir_v.y - py;
    float len = sqrtf(rdx0_raw * rdx0_raw + rdy0_raw * rdy0_raw);

    rd->rdx0 = rdx0_raw / len;
    rd->rdy0 = rdy0_raw / len;
    rd->rdx1 = (game->player->dir_v.x + px) / len;
    rd->rdy1 = (game->player->dir_v.y + py) / len;
    rd->half_proj = (game->win_s.x / 2.0f) /
        tanf(game->player->FOV / 2.0f) / 2.0f;
}

static void render_pixel(game_t *game, sfVector2i *coord,
    float *floor_pos, float intensity)
{
    sfVector2u ftex_s = sfImage_getSize(game->floor_tex_img);
    sfVector2u ctex_s = sfImage_getSize(game->ceil_tex_img);
    sfColor fc = sfImage_getPixel(game->floor_tex_img,
        (int)((floor_pos[0] - floorf(floor_pos[0])) * ftex_s.x) &
        (ftex_s.x - 1), (int)((floor_pos[1] - floorf(floor_pos[1]))
            * ftex_s.y) & (ftex_s.y - 1));
    sfColor cc = sfImage_getPixel(game->ceil_tex_img,
        (int)((floor_pos[0] - floorf(floor_pos[0])) * ctex_s.x) &
        (ctex_s.x - 1), (int)((floor_pos[1] - floorf(floor_pos[1]))
            * ctex_s.y) & (ctex_s.y - 1));

    apply_intensity(&fc, intensity);
    apply_intensity(&cc, intensity);
    sfImage_setPixel(game->floor_image, coord->x, coord->y, fc);
    sfImage_setPixel(game->floor_image, coord->x,
        game->win_s.y - coord->y - 1, cc);
}

static void render_row(game_t *game, int y, ray_data_t *rd)
{
    float row_dist = rd->half_proj / (float)(y - game->win_s.y / 2);
    float step_x = row_dist * (rd->rdx1 - rd->rdx0) / (float)game->win_s.x;
    float step_y = row_dist * (rd->rdy1 - rd->rdy0) / (float)game->win_s.x;
    float floor_pos[2] = {game->player->pos.x + row_dist * rd->rdx0,
        game->player->pos.y + row_dist * rd->rdy0};
    float intensity = fmaxf(0.0f, 1.0f -
        (row_dist / (float)SHADOW_EFFECT_DIST));
    sfVector2i coord;

    for (int x = 0; x < game->win_s.x; x++){
        floor_pos[0] += step_x;
        floor_pos[1] += step_y;
        coord.x = x;
        coord.y = y;
        render_pixel(game, &coord, floor_pos, intensity);
    }
}

void render_floor_ceiling(game_t *game)
{
    if (!game->floor_tex_img || !game->ceil_tex_img)
        return;
    get_ray_dirs(game, game->ray_data);
    for (int y = game->win_s.y / 2 + 1; y < game->win_s.y; y++)
        render_row(game, y, game->ray_data);
    sfTexture_updateFromImage(game->floor_render_tex, game->floor_image, 0, 0);
    sfRenderWindow_drawSprite(game->window, game->floor_sprite, NULL);
}
