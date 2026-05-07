/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** init_game
*/

#include "engine.h"
#include "event.h"
#include "map.h"
#include "wolf3d.h"
#include <SFML/Config.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

static void init_test_inventory(game_t *game)
{
    player_t *player = game->player;

    player->inventory = malloc(sizeof(item_t *) * INVENTORY_SIZE);
    for (int i = 0; i < INVENTORY_SIZE; i++)
        player->inventory[i] = NULL;
}

void setup_time(game_t *game)
{
    game->timer->oldtime = game->timer->currenttime;
    game->timer->time = sfClock_getElapsedTime(game->key_clock);
    game->timer->currenttime = sfTime_asSeconds(game->timer->time);
    game->timer->timeframe = (game->timer->currenttime - game->timer->oldtime);
}

static int load_item_textures(sfTexture *textures[NUM_TEXTURES_ITEMS])
{
    textures[0] = sfTexture_createFromFile("assets/Items/bomb.jpeg", NULL);
    textures[1] = sfTexture_createFromFile("assets/Items/applepie.jpeg", NULL);
    textures[2] = sfTexture_createFromFile("assets/Items/gum.jpeg", NULL);
    textures[3] = sfTexture_createFromFile("assets/Items/flash.jpeg", NULL);
    if (!textures[0 || !textures[1] || !textures[2] || !textures[3]])
        return (84);
    return (0);
}

static void load_ray_textures(sfTexture *textures[NUM_TEXTURES_RAY])
{
    textures[1] =
        sfTexture_createFromFile("assets/World_Textures/redbrick.png", NULL);
    textures[2] =
        sfTexture_createFromFile("assets/World_Textures/wood.png", NULL);
    textures[3] =
        sfTexture_createFromFile("assets/World_Textures/bluestone.png", NULL);
    textures[4] =
        sfTexture_createFromFile("assets/World_Textures/eagle.png", NULL);
    textures[5] =
        sfTexture_createFromFile("assets/World_Textures/greystone.png", NULL);
    textures[6] =
        sfTexture_createFromFile("assets/World_Textures/colorstone.png", NULL);
    textures[7] = sfTexture_createFromFile(
        "assets/World_Textures/purplestone.png", NULL);
    textures[8] =
        sfTexture_createFromFile("assets/World_Textures/mossy.png", NULL);
    textures[9] =
        sfTexture_createFromFile("assets/World_Textures/floor.png", NULL);
}

static void init_player(game_t *game)
{
    player_t *player = game->player;

    player->stats = malloc(sizeof(stats_t));
    if (!player->stats)
        exit_with_message("can't malloc stats\n", 2, 84);
    player->stats->flashlight = false;
    player->angle = 0;
    player->stats->move_speed = MOVESPEED;
    player->FOV = FORMER_FOV;
    init_test_inventory(game);
    rad_giver(player);
    dir_giver(player);
}

static void init_buttons(game_t *game)
{
    game->buttons[0] =
        init_button("enter menu", &(sfVector2f) {game->win_s.x - 100, 100},
        &(sfVector2f) {110, 20}, false);
    game->buttons[0]->on_click = (void *) change_menu_state;
    game->buttons[1] = init_button("leave menu",
        &(sfVector2f) {(float) game->win_s.x / 2, game->win_s.y - 300},
        &(sfVector2f) {110, 20}, true);
    game->buttons[1]->on_click = (void *) change_menu_state;
    game->buttons[2] = init_button("print info",
        &(sfVector2f) {game->win_s.x - 100, game->win_s.y - 100},
        &(sfVector2f) {110, 20}, false);
    game->buttons[2]->on_click = (void *) print_game_info;
    game->buttons[3] = init_button("print info",
        &(sfVector2f) {game->win_s.x - 100, game->win_s.y - 100},
        &(sfVector2f) {110, 20}, true);
    game->buttons[3]->on_click = (void *) print_game_info;
    game->buttons[4] = init_button("leave game",
        &(sfVector2f) {(float) game->win_s.x / 2, game->win_s.y - 150},
        &(sfVector2f) {110, 20}, true);
    game->buttons[4]->on_click = (void *) leave_game;
}

int load_window(game_t *game)
{
    game->window = create_window(game->win_s.x, game->win_s.y, "wolf3d");
    if (!game->window)
        return (84);
    return (0);
}

int init_all(game_t *game)
{
    game->win_s.x = SCREEN_W;
    game->win_s.y = SCREEN_H;
    game->timer = malloc(sizeof(timers_t));
    game->textures = malloc(sizeof(textures_t));
    game->buttons = malloc(sizeof(button_t *) * NUM_BUTTONS);
    if (!game->timer || !game->buttons || !game->textures)
        return (84);
    memset(game->textures->ray_textures, 0,
        sizeof(game->textures->ray_textures));
    memset(game->textures->item_textures, 0,
        sizeof(game->textures->item_textures));
    load_ray_textures(game->textures->ray_textures);
    if (load_item_textures(game->textures->item_textures) == 84)
        return (84);
    init_player(game);
    game->is_menu_open = true;
    game->key_clock = sfClock_create();
    init_buttons(game);
    return (0);
}

void free_ressource(game_t *game, ray_t *ray,
    sfVertexArray *vertexarr[NUM_TEXTURES_RAY])
{
    for (int i = 0; i < NUM_TEXTURES_RAY; i++)
        if (vertexarr[i])
            sfVertexArray_destroy(vertexarr[i]);
    for (int i = 1; i < NUM_TEXTURES_RAY; i++)
        if (game->textures->ray_textures[i])
            sfTexture_destroy(game->textures->ray_textures[i]);
    for (int i = 0; i < NUM_TEXTURES_ITEMS; i++)
        sfTexture_destroy(game->textures->item_textures[i]);
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
