/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** raycasting helper
*/

#include "engine.h"
#include "math.h"
#include "stdlib.h"
#include <stdbool.h>

int is_wall(float x, float y, game_t *game)
{
    int map_x = (int) x;
    int map_y = (int) y;

    if (map_x < 0 || map_y < 0 || map_x >= game->map_size.x
        || map_y >= game->map_size.y)
        return 1;
    return (game->map[map_y][map_x] > '0' && game->map[map_y][map_x] <= '9');
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

static void render_pixel_floor(floor_context_t *context, sfVector2i *coord,
    float *floor_pos, float intensity)
{
    int fx = (int)((floor_pos[0] - floorf(floor_pos[0])) * context->ftex_s.x)
        & (context->ftex_s.x - 1);
    int fy = (int)((floor_pos[1] - floorf(floor_pos[1])) * context->ftex_s.y)
        & (context->ftex_s.y - 1);
    int f_src = (fy * context->ftex_s.x + fx) * 4;
    int f_dst = (coord->y * context->win_w + coord->x) * 4;

    context->out[f_dst + 0] = (sfUint8)(context->ftex[f_src + 0] * intensity);
    context->out[f_dst + 1] = (sfUint8)(context->ftex[f_src + 1] * intensity);
    context->out[f_dst + 2] = (sfUint8)(context->ftex[f_src + 2] * intensity);
    context->out[f_dst + 3] = 255;
}

static void render_pixel_ceiling(floor_context_t *context, sfVector2i *coord,
    float *floor_pos, float intensity)
{
    int cx = (int)((floor_pos[0] - floorf(floor_pos[0])) * context->ctex_s.x)
        & (context->ctex_s.x - 1);
    int cy = (int)((floor_pos[1] - floorf(floor_pos[1])) * context->ctex_s.y)
        & (context->ctex_s.y - 1);
    int c_src = (cy * context->ctex_s.x + cx) * 4;
    int c_dst = ((context->win_h - coord->y - 1)
        * context->win_w + coord->x) * 4;

    context->out[c_dst + 0] = (sfUint8)(context->ctex[c_src + 0] * intensity);
    context->out[c_dst + 1] = (sfUint8)(context->ctex[c_src + 1] * intensity);
    context->out[c_dst + 2] = (sfUint8)(context->ctex[c_src + 2] * intensity);
    context->out[c_dst + 3] = 255;
}

static void render_row(floor_context_t *context, int y, ray_data_t *rd,
    game_t *game)
{
    float row_dist = rd->half_proj / (float)(y - context->win_h / 2);
    float step_x = row_dist * (rd->rdx1 - rd->rdx0) / (float)context->win_w;
    float step_y = row_dist * (rd->rdy1 - rd->rdy0) / (float)context->win_w;
    float floor_pos[2] = {game->player->pos.x + row_dist * rd->rdx0,
        game->player->pos.y + row_dist * rd->rdy0};
    float intensity = fmaxf(0.0f, 1.0f -
        (row_dist / (float)SHADOW_EFFECT_DIST));

    for (int x = 0; x < context->win_w; x++) {
        floor_pos[0] += step_x;
        floor_pos[1] += step_y;
        render_pixel_floor(context, &(sfVector2i){x, y}, floor_pos, intensity);
        render_pixel_ceiling(context,
            &(sfVector2i){x, y}, floor_pos, intensity);
    }
}

void resize_floor_ceiling(game_t *game)
{
    if (game->background->floor_image)
        sfImage_destroy(game->background->floor_image);
    if (game->background->floor_render_tex)
        sfTexture_destroy(game->background->floor_render_tex);
    if (game->background->floor_sprite)
        sfSprite_destroy(game->background->floor_sprite);
    game->background->floor_image =
        sfImage_create(game->win_s.x, game->win_s.y);
    game->background->floor_render_tex =
        sfTexture_create(game->win_s.x, game->win_s.y);
    game->background->floor_sprite = sfSprite_create();
    sfSprite_setTexture(game->background->floor_sprite,
        game->background->floor_render_tex, sfTrue);
}

void render_floor_ceiling(game_t *game)
{
    floor_context_t context;

    if (!game->background->floor_tex_img || !game->background->ceil_tex_img)
        return;
    context.ftex_s = sfImage_getSize(game->background->floor_tex_img);
    context.ctex_s = sfImage_getSize(game->background->ceil_tex_img);
    context.ftex = sfImage_getPixelsPtr(game->background->floor_tex_img);
    context.ctex = sfImage_getPixelsPtr(game->background->ceil_tex_img);
    context.out =
        (sfUint8 *)sfImage_getPixelsPtr(game->background->floor_image);
    context.win_w = game->win_s.x;
    context.win_h = game->win_s.y;
    get_ray_dirs(game, game->ray_data);
    for (int y = game->win_s.y / 2 + 1; y < game->win_s.y; y++)
        render_row(&context, y, game->ray_data, game);
    sfTexture_updateFromImage(game->background->floor_render_tex,
        game->background->floor_image, 0, 0);
    sfRenderWindow_drawSprite(game->window,
        game->background->floor_sprite, NULL);
}
