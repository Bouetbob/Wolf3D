/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** raycasting
*/

#include "enemy.h"
#include "engine.h"
#include "map.h"
#include "wolf3d.h"
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <math.h>

static void step_ray(ray_t *ray, int *map_x, int *map_y, float *distance)
{
    if (ray->side_dist.x < ray->side_dist.y) {
        *distance = ray->side_dist.x;
        ray->side_dist.x += ray->delta_dist.x;
        *map_x += (int) ray->step.x;
        ray->side = 0;
    } else {
        *distance = ray->side_dist.y;
        ray->side_dist.y += ray->delta_dist.y;
        *map_y += (int) ray->step.y;
        ray->side = 1;
    }
}

static void finalize_distance(ray_t *ray, player_t *player, float distance)
{
    ray->distance = (distance <= 0.0) ? 0.1 : distance;
    if (ray->side == 0)
        ray->wall_x = player->pos.y + distance * ray->ray_direction.y;
    else
        ray->wall_x = player->pos.x + distance * ray->ray_direction.x;
    ray->wall_x -= floorf(ray->wall_x);
}

void get_ray_distance(ray_t *ray, player_t *player, game_t *game)
{
    int map_x = (int) player->pos.x;
    int map_y = (int) player->pos.y;
    float distance = 0.0;

    ray->hit_tile = 0;
    while (map_x >= 0 && map_y >= 0 && map_x < game->map_size.x
        && map_y < game->map_size.y) {
        if (game->map[map_y][map_x] > '0' && game->map[map_y][map_x] <= '9') {
            ray->hit_tile = (int) game->map[map_y][map_x] - 48;
            break;
        }
        step_ray(ray, &map_x, &map_y, &distance);
    }
    if (map_x < 0 || map_y < 0 || map_x >= game->map_size.x
        || map_y >= game->map_size.y)
        ray->hit_tile = 0;
    finalize_distance(ray, player, distance);
}

static void fill_ray_struct(player_t *player, ray_t *ray, game_t *game)
{
    int x = (int)player->pos.x;
    int y = (int)player->pos.y;

    if (ray->ray_direction.x < 0) {
        ray->step.x = -1;
        ray->side_dist.x = (player->pos.x - x) * ray->delta_dist.x;
    } else {
        ray->step.x = 1;
        ray->side_dist.x = (x + 1.0 - player->pos.x) * ray->delta_dist.x;
    }
    if (ray->ray_direction.y < 0) {
        ray->step.y = -1;
        ray->side_dist.y = (player->pos.y - y) * ray->delta_dist.y;
    } else {
        ray->step.y = 1;
        ray->side_dist.y = (y + 1.0 - player->pos.y) * ray->delta_dist.y;
    }
    get_ray_distance(ray, player, game);
}

static void set_ray_color(game_t *game, ray_t *ray, sfColor *color,
    float ray_angle)
{
    *color = sfWhite;
    if (ray->side == 1)
        *color = change_color(color);
    if (game->player->stats->flashlight)
        *color = apply_flashlight(color, ray_angle, game->player->rads,
            ray->distance);
    else
        *color = fade_color(color, ray->distance);
}

static void fill_quad(sfVertex quad[6], int i, quad_params_t *p)
{
    quad[0] = (sfVertex) {.position = {i, p->y_start}, .color = p->color,
        .texCoords = {p->tex_x, 0}};
    quad[1] = (sfVertex) {.position = {i + 1, p->y_start}, .color = p->color,
        .texCoords = {p->tex_x + 1, 0}};
    quad[2] = (sfVertex) {.position = {i + 1, p->y_end}, .color = p->color,
        .texCoords = {p->tex_x + 1, p->tex_size.y}};
    quad[3] = (sfVertex) {.position = {i, p->y_start}, .color = p->color,
        .texCoords = {p->tex_x, 0}};
    quad[4] = (sfVertex) {.position = {i + 1, p->y_end}, .color = p->color,
        .texCoords = {p->tex_x + 1, p->tex_size.y}};
    quad[5] = (sfVertex) {.position = {i, p->y_end}, .color = p->color,
        .texCoords = {p->tex_x, p->tex_size.y}};
}

static void draw_ray(game_t *game, ray_t *ray, sfVertexArray **vertexarr, int i)
{
    quad_params_t p;
    sfVertex quad[6];
    sfTexture *tex = game->tex->ray_tex[ray->hit_tile];

    if (tex == NULL)
        return;
    p.tex_size = sfTexture_getSize(tex);
    p.tex_x = ray->wall_x * (float) p.tex_size.x;
    p.y_start = game->win_s.y / 2.0 - (ray->proj_plane / ray->distance) / 2.0;
    p.y_end = game->win_s.y / 2.0 + (ray->proj_plane / ray->distance) / 2.0;
    set_ray_color(game, ray, &p.color, ray->current_angle);
    fill_quad(quad, i, &p);
    for (int j = 0; j < 6; j++)
        sfVertexArray_append(vertexarr[ray->hit_tile], quad[j]);
}

static void cast_single_ray(game_t *game, ray_t *ray, sfVertexArray **va, int i)
{
    float cam_x = 2.0 * i / (float) game->win_s.x - 1.0;
    float fov = tan(game->player->FOV / 2.0);
    float px = -game->player->dir_v.y * fov;
    float py = game->player->dir_v.x * fov;

    ray->current_angle = atan2(game->player->dir_v.y + py * cam_x,
        game->player->dir_v.x + px * cam_x);
    ray->ray_direction.x = game->player->dir_v.x + px * cam_x;
    ray->ray_direction.y = game->player->dir_v.y + py * cam_x;
    ray->delta_dist.x = (ray->ray_direction.x == 0) ? 1e30 :
        fabs(1 / ray->ray_direction.x);
    ray->delta_dist.y = (ray->ray_direction.y == 0) ? 1e30 :
        fabs(1 / ray->ray_direction.y);
    fill_ray_struct(game->player, ray, game);
    game->z_buffer[i] = ray->distance;
    if (ray->hit_tile != 0)
        draw_ray(game, ray, va, i);
}

static void cast_rays(game_t *game, ray_t *ray, sfVertexArray **vertexarr)
{
    int i = 0;

    for (i = 0; i < game->win_s.x; i++)
        game->z_buffer[i] = 1e30f;
    ray->proj_plane = (game->win_s.x / 2.0) / tan(game->player->FOV / 2.0);
    for (i = 0; i < game->win_s.x; i++)
        cast_single_ray(game, ray, vertexarr, i);
}

void render_raycast(game_t *game, ray_t *ray, sfVertexArray **vertexarr)
{
    sfRenderStates states;

    for (int i = 1; i < NUM_TEXTURES_RAY; i++)
        sfVertexArray_resize(vertexarr[i], 0);
    render_floor_ceiling(game);
    cast_rays(game, ray, vertexarr);
    for (int i = 1; i < NUM_TEXTURES_RAY; i++) {
        if (game->tex->ray_tex[i] == NULL)
            continue;
        states = (sfRenderStates) {sfBlendAlpha, sfTransform_Identity,
            game->tex->ray_tex[i], NULL};
        sfRenderWindow_drawVertexArray(game->window, vertexarr[i], &states);
    }
    render_enemies(game);
}
