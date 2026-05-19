/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** cleanup
*/

#include "enemy.h"
#include "engine.h"
#include "event.h"
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>

static void free_enemies(game_t *game)
{
    if (!game->enemies)
        return;
    for (int i = 0; i < game->enemy_count; i++) {
        if (game->enemies[i]) {
            free(game->enemies[i]->weapon);
            free(game->enemies[i]);
        }
    }
    free(game->enemies);
}

void clean_game(sfVertexArray *vertexarr[NUM_TEXTURES_RAY], game_t *game)
{
    for (int i = 0; i < NUM_TEXTURES_RAY; i++)
        if (vertexarr[i])
            sfVertexArray_destroy(vertexarr[i]);
    for (int i = 1; i < NUM_TEXTURES_RAY; i++)
        if (game->tex->ray_tex[i])
            sfTexture_destroy(game->tex->ray_tex[i]);
    for (int i = 0; i < NUM_TEXTURES_ITEMS; i++)
        sfTexture_destroy(game->tex->item_tex[i]);
}

void clean_player(player_t *player)
{
    free(player->stats);
    sfRectangleShape_destroy(player->ui_bar);
    for (int i = 0; player->ui_texts[i]; i++) {
        sfText_destroy(player->ui_texts[i]);
    }
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (player->inventory[i]) {
            sfRectangleShape_destroy(player->inventory[i]->background);
            free(player->inventory[i]->name);
            free(player->inventory[i]);
        }
    }
    free(player->inventory);
    free(player);
}

void free_ressource(game_t *game, ray_t *ray,
    sfVertexArray *vertexarr[NUM_TEXTURES_RAY])
{
    clean_game(vertexarr, game);
    if (game->key_clock)
        sfClock_destroy(game->key_clock);
    if (game->window)
        sfRenderWindow_destroy(game->window);
    clean_player(game->player);
    free_enemies(game);
    if (game->enemy_texture)
        sfTexture_destroy(game->enemy_texture);
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
