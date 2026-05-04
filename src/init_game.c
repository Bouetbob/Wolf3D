/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** init_game
*/

#include "engine.h"
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

static void init_item(item_t *item_spot, char *file, sfVector2f *sprite_pos,
    char *name)
{
    sfTexture *texture = sfTexture_createFromFile(file, NULL);

    item_spot->name = strdup(name);
    item_spot->position = *sprite_pos;
    item_spot->sprite = sfSprite_create();
    sfSprite_setPosition(item_spot->sprite, item_spot->position);
    sfSprite_setTexture(item_spot->sprite, texture, sfFalse);
}

static void init_test_inventory(player_t *player)
{
    player->inventory = malloc(sizeof(item_t *) * 5);
    player->inventory[4] = NULL;
    player->inventory[0] = malloc(sizeof(item_t));
    player->inventory[1] = malloc(sizeof(item_t));
    player->inventory[2] = malloc(sizeof(item_t));
    player->inventory[3] = malloc(sizeof(item_t));
    init_item(player->inventory[0], "assets/Items/gum.jpeg",
        &(sfVector2f) {300, 300}, "gum");
    init_item(player->inventory[1], "assets/Items/gum.jpeg",
        &(sfVector2f) {100, 300}, "gum");
    init_item(player->inventory[2], "assets/Items/gum.jpeg",
        &(sfVector2f) {300, 100}, "gum");
    init_item(player->inventory[3], "assets/Items/gum.jpeg",
        &(sfVector2f) {100, 100}, "gum");
}

void setup_time(game_t *game)
{
    game->timer->oldtime = game->timer->currenttime;
    game->timer->time = sfClock_getElapsedTime(game->key_clock);
    game->timer->currenttime = sfTime_asSeconds(game->timer->time);
    game->timer->timeframe = (game->timer->currenttime - game->timer->oldtime);
}

static void load_textures(sfTexture *textures[NUM_TEXTURES])
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

static void init_player(player_t *player)
{
    player->stats = malloc(sizeof(stats_t));
    if (!player->stats)
        exit_with_message("can't malloc stats\n", 2, 84);
    player->stats->flashlight = false;
    player->angle = 0;
    player->stats->move_speed = MOVESPEED;
    player->FOV = FORMER_FOV;
    init_test_inventory(player);
    rad_giver(player);
    dir_giver(player);
}

static void init_buttons(game_t *game)
{
    game->buttons[0] = init_button("enter menu",
        &(sfVector2f) {SCREEN_W - 100, 100}, &(sfVector2f) {110, 20}, false);
    game->buttons[0]->on_click = (void *) change_menu_state;
    game->buttons[1] = init_button("leave menu", &(sfVector2f) {100, 100},
        &(sfVector2f) {110, 20}, true);
    game->buttons[1]->on_click = (void *) change_menu_state;
    game->buttons[2] = init_button("print info",
        &(sfVector2f) {100, SCREEN_H - 100}, &(sfVector2f) {110, 20}, false);
    game->buttons[2]->on_click = (void *) print_game_info;
    game->buttons[3] = init_button("print info",
        &(sfVector2f) {SCREEN_W - 100, SCREEN_H - 100},
        &(sfVector2f) {110, 20}, true);
    game->buttons[3]->on_click = (void *) print_game_info;
}

int init_all(game_t *game)
{
    game->timer = malloc(sizeof(timers_t));
    game->buttons = malloc(sizeof(button_t *) * NUM_BUTTONS);
    if (!game->timer || !game->buttons)
        return (84);
    memset(game->textures, 0, sizeof(game->textures));
    load_textures(game->textures);
    init_player(game->player);
    game->is_menu_open = true;
    game->key_clock = sfClock_create();
    game->window = create_window(SCREEN_W, SCREEN_H, "wolf3d");
    if (!game->window)
        return (84);
    init_buttons(game);
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
