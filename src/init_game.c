/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** init_game
*/

#include "enemy.h"
#include "engine.h"
#include "event.h"
#include "map.h"
#include "wolf3d.h"
#include <SFML/Graphics.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void setup_time(game_t *game)
{
    game->timer->oldtime = game->timer->currenttime;
    game->timer->time = sfClock_getElapsedTime(game->key_clock);
    game->timer->currenttime = sfTime_asSeconds(game->timer->time);
    game->timer->timeframe = (game->timer->currenttime - game->timer->oldtime);
}

int load_window(game_t *game)
{
    game->window = create_window(game->win_s.x, game->win_s.y, "wolf3d");
    if (!game->window)
        return (84);
    return (0);
}

static int load_item_textures(sfTexture *textures[NUM_TEXTURES_ITEMS])
{
    textures[0] = sfTexture_createFromFile("assets/Items/bomb.jpeg", NULL);
    textures[1] = sfTexture_createFromFile("assets/Items/applepie.jpeg", NULL);
    textures[2] = sfTexture_createFromFile("assets/Items/gum.jpeg", NULL);
    textures[3] = sfTexture_createFromFile("assets/Items/flash.jpeg", NULL);
    if (!textures[0] || !textures[1] || !textures[2] || !textures[3])
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

static int init_textures(game_t *game)
{
    size_t r_s = sizeof(sfTexture *) * NUM_TEXTURES_RAY;
    size_t i_s = sizeof(sfTexture *) * NUM_TEXTURES_ITEMS;

    memset(game->tex->ray_tex, 0, r_s);
    memset(game->tex->item_tex, 0, i_s);
    load_ray_textures(game->tex->ray_tex);
    if (load_item_textures(game->tex->item_tex) == 84)
        return (84);
    game->enemy_texture = sfTexture_createFromFile(
        "assets/World_Textures/enemy_magnum.png", NULL);
    if (!game->enemy_texture)
        return (84);
    return (0);
}

static void init_player(game_t *game)
{
    player_t *p = game->player;

    p->stats = malloc(sizeof(stats_t));
    if (!p->stats)
        exit_with_message("can't malloc stats\n", 2, 84);
    p->stats->flashlight = false;
    p->angle = 0;
    p->stats->move_speed = MOVESPEED;
    p->FOV = FORMER_FOV;
    p->inventory = malloc(sizeof(item_t *) * INVENTORY_SIZE);
    for (int i = 0; i < INVENTORY_SIZE; i++)
        p->inventory[i] = NULL;
    rad_giver(p);
    dir_giver(p);
}

static void init_buttons(game_t *game)
{
    sfVector2f sz = {110, 20};
    sfVector2f p1 = {game->win_s.x - 100, 100};
    sfVector2f p2 = {(float) game->win_s.x / 2, game->win_s.y - 300};
    sfVector2f p3 = {game->win_s.x - 100, game->win_s.y - 100};
    sfVector2f p4 = {(float) game->win_s.x / 2, game->win_s.y - 150};

    game->buttons[0] = init_button("enter menu", &p1, &sz, false);
    game->buttons[0]->on_click = (void *) change_menu_state;
    game->buttons[1] = init_button("leave menu", &p2, &sz, true);
    game->buttons[1]->on_click = (void *) change_menu_state;
    game->buttons[2] = init_button("print info", &p3, &sz, false);
    game->buttons[2]->on_click = (void *) print_game_info;
    game->buttons[3] = init_button("print info", &p3, &sz, true);
    game->buttons[3]->on_click = (void *) print_game_info;
    game->buttons[4] = init_button("leave game", &p4, &sz, true);
    game->buttons[4]->on_click = (void *) leave_game;
}

static int alloc_essentials(game_t *game)
{
    game->timer = malloc(sizeof(timers_t));
    game->tex = malloc(sizeof(textures_t));
    game->buttons = malloc(sizeof(button_t *) * NUM_BUTTONS);
    if (!game->timer || !game->buttons || !game->tex)
        return (84);
    game->timer->oldtime = 0.0f;
    game->timer->currenttime = 0.0f;
    game->timer->timeframe = 0.0f;
    game->enemies = malloc(sizeof(enemy_t *) * MAX_ENEMIES);
    game->enemy_count = 0;
    if (!game->enemies)
        return (84);
    for (int i = 0; i < MAX_ENEMIES; i++)
        game->enemies[i] = NULL;
    return (0);
}

int init_all(game_t *game)
{
    game->win_s.x = SCREEN_W;
    game->win_s.y = SCREEN_H;
    if (alloc_essentials(game) == 84 || init_textures(game) == 84)
        return (84);
    memset(game->tex->ray_tex, 0,
        sizeof(game->tex->ray_tex));
    memset(game->tex->item_tex, 0,
        sizeof(game->tex->item_tex));
    load_ray_textures(game->tex->ray_tex);
    if (load_item_textures(game->tex->item_tex) == 84)
        return (84);
    init_player(game);
    game->is_menu_open = true;
    game->key_clock = sfClock_create();
    for (int i = 0; i < SCREEN_W; i++)
        game->z_buffer[i] = 1e30f;
    init_buttons(game);
    return (0);
}
