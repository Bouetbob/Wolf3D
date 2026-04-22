/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** init_game
*/

#include "wolf3d.h"
#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

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
}

static void init_player(player_t *player)
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
    game->button = init_button("helloooo hi hi hi", &(sfVector2f) {100, 100},
        &(sfVector2f) {150, 30});
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
