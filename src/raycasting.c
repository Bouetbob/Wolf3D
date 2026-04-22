/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** raycasting
*/

#include "wolf3d.h"
#include "map.h"
#include <math.h>

int map[MAP_HEIGHT][MAP_WIDTH] =
{{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0,
        7},
    {4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        7},
    {4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        7},
    {4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0,
        7},
    {4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7,
        7},
    {4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7,
        1},
    {4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0,
        8},
    {4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7,
        1},
    {4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0,
        8},
    {4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7,
        1},
    {4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7,
        1},
    {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6},
    {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        4},
    {6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6},
    {4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3,
        3},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0,
        2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0,
        2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2,
        2},
    {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0,
        2},
    {4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2,
        2},
    {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0,
        2},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0,
        2},
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3,
        3}};

static void step_ray(ray_t *ray, int *map_x, int *map_y, float *distance)
{
    if (ray->side_dist.x < ray->side_dist.y) {
        *distance = ray->side_dist.x;
        ray->side_dist.x += ray->delta_dist.x;
        *map_x += (int)ray->step.x;
        ray->side = 0;
    } else {
        *distance = ray->side_dist.y;
        ray->side_dist.y += ray->delta_dist.y;
        *map_y += (int)ray->step.y;
        ray->side = 1;
    }
}

static void finalize_distance(ray_t *ray, player_t *player, float distance)
{
    distance = distance * cos(player->rads - ray->current_angle);
    ray->distance = (distance <= 0.0) ? 0.1 : distance;
    if (ray->side == 0)
        ray->wall_x = player->pos.y + ray->distance * ray->ray_direction.y;
    else
        ray->wall_x = player->pos.x + ray->distance * ray->ray_direction.x;
    ray->wall_x -= floorf(ray->wall_x);
}

void get_ray_distance(ray_t *ray, player_t *player)
{
    int map_x = (int)player->pos.x;
    int map_y = (int)player->pos.y;
    float distance = 0.0;

    ray->hit_tile = 0;
    while (map_x >= 0 && map_y >= 0
        && map_x < MAP_WIDTH && map_y < MAP_HEIGHT) {
        if (map[map_y][map_x] > 0) {
            ray->hit_tile = map[map_y][map_x];
            break;
        }
        step_ray(ray, &map_x, &map_y, &distance);
    }
    if (map_x < 0 || map_y < 0 || map_x >= MAP_WIDTH || map_y >= MAP_HEIGHT)
        ray->hit_tile = 0;
    finalize_distance(ray, player, distance);
}

static void fill_ray_struct(player_t *player, ray_t *ray)
{
    int x = player->pos.x;
    int y = player->pos.y;

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
    get_ray_distance(ray, player);
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
    quad[0] = (sfVertex){.position = {i, p->y_start}, .color = p->color,
        .texCoords = {p->tex_x, 0}};
    quad[1] = (sfVertex){.position = {i + 1, p->y_start}, .color = p->color,
        .texCoords = {p->tex_x + 1, 0}};
    quad[2] = (sfVertex){.position = {i + 1, p->y_end}, .color = p->color,
        .texCoords = {p->tex_x + 1, p->tex_size.y}};
    quad[3] = (sfVertex){.position = {i, p->y_start}, .color = p->color,
        .texCoords = {p->tex_x, 0}};
    quad[4] = (sfVertex){.position = {i + 1, p->y_end}, .color = p->color,
        .texCoords = {p->tex_x + 1, p->tex_size.y}};
    quad[5] = (sfVertex){.position = {i, p->y_end}, .color = p->color,
        .texCoords = {p->tex_x, p->tex_size.y}};
}

static void draw_ray(game_t *game, ray_t *ray, sfVertexArray **vertexarr, int i)
{
    quad_params_t p;
    sfVertex quad[6];
    sfTexture *tex = game->textures[ray->hit_tile];

    if (tex == NULL)
        return;
    p.tex_size = sfTexture_getSize(tex);
    p.tex_x = ray->wall_x * (float)p.tex_size.x;
    p.y_start = SCREEN_H / 2.0 - ((SCREEN_H / 2.0) / ray->distance) / 2.0;
    p.y_end = SCREEN_H / 2.0 + ((SCREEN_H / 2.0) / ray->distance) / 2.0;
    set_ray_color(game, ray, &p.color, ray->current_angle);
    fill_quad(quad, i, &p);
    for (int j = 0; j < 6; j++)
        sfVertexArray_append(vertexarr[ray->hit_tile], quad[j]);
}

static void cast_rays(game_t *game, ray_t *ray, sfVertexArray **vertexarr)
{
    float ray_angle = game->player->rads - (game->player->FOV / 2.0);
    float angle_step = game->player->FOV / NUM_RAYS;

    for (int i = 0; i < NUM_RAYS; i++) {
        ray->current_angle = ray_angle;
        ray->ray_direction.x = cos(ray_angle);
        ray->ray_direction.y = sin(ray_angle);
        ray->delta_dist.x = (ray->ray_direction.x == 0)
            ? 1e30 : fabs(1 / ray->ray_direction.x);
        ray->delta_dist.y = (ray->ray_direction.y == 0)
            ? 1e30 : fabs(1 / ray->ray_direction.y);
        fill_ray_struct(game->player, ray);
        if (ray->hit_tile != 0)
            draw_ray(game, ray, vertexarr, i);
        ray_angle += angle_step;
    }
}

int is_wall(float x, float y)
{
    int map_x = (int) x;
    int map_y = (int) y;

    if (map_x < 0 || map_y < 0 || map_x >= MAP_WIDTH || map_y >= MAP_HEIGHT)
        return 1;
    return map[map_y][map_x] > 0;
}

void render_raycast(game_t *game, ray_t *ray, sfVertexArray **vertexarr)
{
    sfRenderStates states;

    for (int i = 1; i < NUM_TEXTURES; i++)
        sfVertexArray_resize(vertexarr[i], 0);
    cast_rays(game, ray, vertexarr);
    for (int i = 1; i < NUM_TEXTURES; i++) {
        if (game->textures[i] == NULL)
            continue;
        states = (sfRenderStates){sfBlendAlpha, sfTransform_Identity,
            game->textures[i], NULL};
        sfRenderWindow_drawVertexArray(game->window, vertexarr[i], &states);
    }
}
