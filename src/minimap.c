/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** minimap
*/

#include "engine.h"
#include "wolf3d.h"
#include "math.h"

static int get_tile_size(game_t *game)
{
    float scale = fminf((float)game->win_s.x / SCREEN_W,
        (float)game->win_s.y / SCREEN_H);

    return (int)(MINI_TILE_BASE * scale);
}

static void draw_tile(game_t *game, int x, int y, int ts)
{
    sfRectangleShape *tile = sfRectangleShape_create();
    sfColor color = (game->map[y][x] == '0' || game->map[y][x] == 'P' ||
        game->map[y][x] == 'M' || game->map[y][x] == 'T') ? sfBlack : sfWhite;

    sfRectangleShape_setSize(tile, (sfVector2f){ts - 1, ts - 1});
    sfRectangleShape_setFillColor(tile, color);
    sfRectangleShape_setPosition(tile, (sfVector2f){x * ts, y * ts});
    sfRenderTexture_drawRectangleShape(game->minimap_tex, tile, NULL);
    sfRectangleShape_destroy(tile);
}

static void draw_player_dot(game_t *game, int tile_size)
{
    sfCircleShape *dot = sfCircleShape_create();

    sfCircleShape_setRadius(dot, tile_size / 2);
    sfCircleShape_setFillColor(dot, sfRed);
    sfCircleShape_setPosition(dot, (sfVector2f){
            game->player->pos.x * tile_size - tile_size / 2,
            game->player->pos.y * tile_size - tile_size / 2});
    sfRenderTexture_drawCircleShape(game->minimap_tex, dot, NULL);
    sfCircleShape_destroy(dot);
}

void init_minimap(game_t *game)
{
    int tile_size = get_tile_size(game);
    int weigth = game->map_size.x * tile_size;
    int height = game->map_size.y * tile_size;

    game->minimap_tex = sfRenderTexture_create(weigth, height, sfFalse);
    game->minimap_sprite = sfSprite_create();
    sfSprite_setTexture(game->minimap_sprite,
        sfRenderTexture_getTexture(game->minimap_tex), sfTrue);
    sfSprite_setPosition(game->minimap_sprite,
        (sfVector2f){MINI_PADDING, MINI_PADDING});
}

void render_minimap(game_t *game)
{
    int tile_size = get_tile_size(game);

    sfRenderTexture_clear(game->minimap_tex, (sfColor){30, 30, 30, 180});
    for (int y = 0; y < game->map_size.y; y++)
        for (int x = 0; x < game->map_size.x; x++)
            draw_tile(game, x, y, tile_size);
    draw_player_dot(game, tile_size);
    sfRenderTexture_display(game->minimap_tex);
    sfRenderWindow_drawSprite(game->window, game->minimap_sprite, NULL);
}
