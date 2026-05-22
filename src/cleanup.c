/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** cleanup
*/

#include "enemy.h"
#include "engine.h"
#include "event.h"
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>

void clean_game(sfVertexArray *vertexarr[NUM_TEXTURES_RAY], game_t *game)
{
    for (int i = 0; i < NUM_TEXTURES_RAY; i++)
        if (vertexarr[i])
            sfVertexArray_destroy(vertexarr[i]);
    for (int i = 0; i < NUM_TEXTURES_RAY; i++)
        if (game->tex->ray_tex[i])
            sfTexture_destroy(game->tex->ray_tex[i]);
    for (int i = 0; i < NUM_TEXTURES_ITEMS; i++)
        sfTexture_destroy(game->tex->item_tex[i]);
}

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

static void clean_floor_and_ceilling(game_t *game)
{
    if (game->background->floor_image)
        sfImage_destroy(game->background->floor_image);
    if (game->background->floor_render_tex)
        sfTexture_destroy(game->background->floor_render_tex);
    if (game->background->floor_sprite)
        sfSprite_destroy(game->background->floor_sprite);
    if (game->background->floor_tex_img)
        sfImage_destroy(game->background->floor_tex_img);
    if (game->background->ceil_tex_img)
        sfImage_destroy(game->background->ceil_tex_img);
    if (game->ray_data)
        free(game->ray_data);
}

static void clean_map(game_t *game)
{
    if (!game->map)
        return;
    for (int i = 0; game->map[i]; i++)
        free(game->map[i]);
    free(game->map);
}

static void free_resource_helper(game_t *game)
{
    clean_map(game);
    clean_player(game->player);
    free_enemies(game);
    free_buttons(game);
}

void cleanup_game(game_t *game)
{
    if (game->minimap)
        free(game->minimap);
    if (game->key_clock)
        sfClock_destroy(game->key_clock);
    if (game->window)
        sfRenderWindow_destroy(game->window);
    if (game->timer)
        free(game->timer);
    if (game->file_name)
        free(game->file_name);
    if (game->enemy_texture)
        sfTexture_destroy(game->enemy_texture);
    if (game->tex)
        free(game->tex);
    if (game->font)
        sfFont_destroy(game->font);
    if (game->background)
        free(game->background);
}

void free_ressource(game_t *game, ray_t *ray,
    sfVertexArray *vertexarr[NUM_TEXTURES_RAY])
{
    clean_game(vertexarr, game);
    clean_floor_and_ceilling(game);
    clean_mini_map(game);
    cleanup_game(game);
    free_resource_helper(game);
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
