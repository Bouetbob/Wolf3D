/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** main file
*/

//hours spent on this : around 20 (20/04 12:39)

#include "map.h"
#include "my.h"
#include "wolf3d.h"
#include <SFML/Graphics.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/PrimitiveType.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/System.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool has_display(char **env)
{
    int i = 0;

    while (env[i]) {
        if (strncmp(env[i], "DISPLAY=", 8) == 0)
            return true;
        i++;
    }
    return false;
}

sfRenderWindow *create_window(int width, int heigth, char *name)
{
    sfRenderWindow *window;
    sfVideoMode vid_mode;

    vid_mode.width = width;
    vid_mode.height = heigth;
    vid_mode.bitsPerPixel = 32;
    window = sfRenderWindow_create(vid_mode, name, sfClose, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    return (window);
}

void exit_with_message(char *exit_message, int message_channel, int exit_value)
{
    write(message_channel, exit_message, strlen(exit_message));
    exit(exit_value);
}

int is_wall(float x, float y)
{
    int map_x = (int) x;
    int map_y = (int) y;

    if (map_x < 0 || map_y < 0 || map_x >= MAP_WIDTH || map_y >= MAP_HEIGHT)
        return 1;
    return map[map_y][map_x] > 0;
}

void dir_giver(player_t *player)
{
    player->direction_vec =
        (sfVector2f) {cos(player->rads), sin(player->rads)};
}

void rad_giver(player_t *player)
{
    player->rads = player->angle * 0.017453f;
}

void update_player(player_t *player)
{
    rad_giver(player);
    dir_giver(player);
}

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

void fill_ray_struct(player_t *player, ray_t *ray)
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

sfVector2f move_player(player_t *player, game_t *game)
{
    sfVector2f next = {player->pos.x, player->pos.y};

    if (sfKeyboard_isKeyPressed(sfKeyUp) || sfKeyboard_isKeyPressed(sfKeyZ)) {
        next.x += player->direction_vec.x * game->timer->timeframe * MOVESPEED;
        next.y += player->direction_vec.y * game->timer->timeframe * MOVESPEED;
    }
    if (sfKeyboard_isKeyPressed(sfKeyDown)
        || sfKeyboard_isKeyPressed(sfKeyS)) {
        next.x -= player->direction_vec.x * game->timer->timeframe * MOVESPEED;
        next.y -= player->direction_vec.y * game->timer->timeframe * MOVESPEED;
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        next.x += player->direction_vec.y * game->timer->timeframe * MOVESPEED;
        next.y -= player->direction_vec.x * game->timer->timeframe * MOVESPEED;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        next.x -= player->direction_vec.y * game->timer->timeframe * MOVESPEED;
        next.y += player->direction_vec.x * game->timer->timeframe * MOVESPEED;
    }
    return next;
}

void rotate_player(player_t *player, game_t *game)
{
    if (sfKeyboard_isKeyPressed(sfKeyRight))
        player->angle += ROTATESPEED * game->timer->timeframe;
    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        player->angle -= ROTATESPEED * game->timer->timeframe;
    if (player->angle >= 360)
        player->angle -= 360;
    if (player->angle < 0)
        player->angle += 360;
    if (sfKeyboard_isKeyPressed(sfKeyA))
        player->FOV *= 1.01;
    if (sfKeyboard_isKeyPressed(sfKeyE))
        player->FOV /= 1.01;
    if (sfKeyboard_isKeyPressed(sfKeyK))
        player->FOV = FORMER_FOV;
}

//--------------------MOVEMENT FILE--------------------//
void handle_movement(player_t *player, game_t *game)
{
    sfVector2f next = {player->pos.x, player->pos.y};
    float margin = 0.2;
    sfTime elapsed;

    next = move_player(player, game);
    if (!is_wall(next.x + margin * (next.x > player->pos.x ? 1 : -1),
            player->pos.y))
        player->pos.x = next.x;
    if (!is_wall(player->pos.x,
            next.y + margin * (next.y > player->pos.y ? 1 : -1)))
        player->pos.y = next.y;
    if (sfKeyboard_isKeyPressed(sfKeyF)) {
        elapsed = sfClock_getElapsedTime(game->key_clock);
        if (sfTime_asMilliseconds(elapsed) >= 500) {
            player->stats->flashlight = !player->stats->flashlight;
            sfClock_restart(game->key_clock);
        }
    }
    rotate_player(player, game);
    update_player(player);
}
//----------------------END----------------------//

void analyse_events(sfRenderWindow *window, sfEvent event)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
        sfRenderWindow_close(window);
}

//--------------------INIT FILE--------------------//
void load_textures(sfTexture *textures[NUM_TEXTURES])
{
    textures[1] = sfTexture_createFromFile("textures/redbrick.png", NULL);
    textures[2] = sfTexture_createFromFile("textures/wood.png", NULL);
    textures[3] = sfTexture_createFromFile("textures/bluestone.png", NULL);
    textures[4] = sfTexture_createFromFile("textures/eagle.png", NULL);
    textures[5] = sfTexture_createFromFile("textures/greystone.png", NULL);
    textures[6] = sfTexture_createFromFile("textures/colorstone.png", NULL);
    textures[7] = sfTexture_createFromFile("textures/purplestone.png", NULL);
    textures[8] = sfTexture_createFromFile("textures/mossy.png", NULL);
}

void init_player(player_t *player)
{
    player->stats = malloc(sizeof(stats_t));
    if (!player->stats)
        exit_with_message("can't malloc stats\n", 2, 84);
    player->stats->flashlight = false;
    player->pos.x = 2;
    player->pos.y = 1;
    player->angle = 0;
    player->FOV = FORMER_FOV;
    rad_giver(player);
    dir_giver(player);
}

int init_all(game_t *game)
{
    game->timer = malloc(sizeof(timers_t));
    if (!game->timer)
        return (84);
    memset(game->textures, 0, sizeof(game->textures));
    load_textures(game->textures);
    init_player(game->player);
    game->key_clock = sfClock_create();
    game->window = create_window(SCREEN_W, SCREEN_H, "wolf3d");
    return (0);
}

void free_ressource(game_t *game, ray_t *ray,
    sfVertexArray *vertexarr[NUM_TEXTURES])
{
    for (int i = 0; i < NUM_TEXTURES; i++) {
        if (vertexarr[i])
            sfVertexArray_destroy(vertexarr[i]);
    }
    for (int i = 1; i < NUM_TEXTURES; i++) {
        if (game->textures[i])
            sfTexture_destroy(game->textures[i]);
    }
    if (game->key_clock)
        sfClock_destroy(game->key_clock);
    if (game->window)
        sfRenderWindow_destroy(game->window);
    if (game->player->stats)
        free(game->player->stats);
    if (game->player)
        free(game->player);
    if (game)
        free(game);
    if (ray)
        free(ray);
}

void check_exit_conditions(game_t *game, ray_t *ray, char **env)
{
    if (!has_display(env))
        exit_with_message("no display found\n", 2, 84);
    if (!game)
        exit_with_message("can't malloc game struct\n", 2, 84);
    if (!ray)
        exit_with_message("can't malloc ray struct\n", 2, 84);
}
//----------------------END----------------------//

void setup_time(game_t *game)
{
    game->timer->oldtime = game->timer->currenttime;
    game->timer->time = sfClock_getElapsedTime(game->key_clock);
    game->timer->currenttime = sfTime_asSeconds(game->timer->time);
    game->timer->timeframe = (game->timer->currenttime
        - game->timer->oldtime);
}

void main_game_loop(game_t *game, ray_t *ray,
    sfVertexArray *vertexarr[NUM_TEXTURES])
{
    for (int t = 0; t < NUM_TEXTURES; t++) {
        vertexarr[t] = sfVertexArray_create();
        sfVertexArray_setPrimitiveType(vertexarr[t], sfTriangles);
    }
    while (sfRenderWindow_isOpen(game->window)) {
        setup_time(game);
        while (sfRenderWindow_pollEvent(game->window, &game->event))
            analyse_events(game->window, game->event);
        handle_movement(game->player, game);
        sfRenderWindow_clear(game->window, sfBlack);
        render_raycast(game, ray, vertexarr);
        sfRenderWindow_display(game->window);
        printf("%f %f\n", game->player->pos.x, game->player->pos.y);
    }
    free_ressource(game, ray, vertexarr);
}

int main(UNUSED int ac, UNUSED char **av, UNUSED char **env)
{
    game_t *game = malloc(sizeof(game_t));
    ray_t *ray = malloc(sizeof(ray_t));
    sfVertexArray *vertexarr[NUM_TEXTURES];

    check_exit_conditions(game, ray, env);
    game->player = malloc(sizeof(player_t));
    if (!game->player)
        exit_with_message("can't malloc game->player struct\n", 2, 84);
    for (int i = 0; i < NUM_TEXTURES; i++) {
        vertexarr[i] = sfVertexArray_create();
        sfVertexArray_setPrimitiveType(vertexarr[i], sfTriangles);
    }
    if (init_all(game) == 84)
        return (84);
    main_game_loop(game, ray, vertexarr);
    return 0;
}
