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

    if (scale <= 1)
        scale = 1;
    return (int)(MINI_TILE_BASE * scale);
}

static void draw_tile(game_t *game, int x, int y, int tile_size)
{
    sfColor color = (game->map[y][x] == '0' || game->map[y][x] == 'P' ||
        game->map[y][x] == 'M' || game->map[y][x] == 'T') ? sfBlack : sfWhite;

    sfRectangleShape_setFillColor(game->minimap->tile, color);
    sfRectangleShape_setPosition(game->minimap->tile,
        (sfVector2f){x * tile_size, y * tile_size});
    sfRenderTexture_drawRectangleShape(game->minimap->minimap_tex,
        game->minimap->tile, NULL);
}

static void draw_player_dot(game_t *game, int tile_size)
{
    sfCircleShape_setPosition(game->minimap->player_dot, (sfVector2f){
            game->player->pos.x * tile_size - tile_size / 2,
            game->player->pos.y * tile_size - tile_size / 2});
    sfRenderTexture_drawCircleShape(game->minimap->minimap_tex,
        game->minimap->player_dot, NULL);
}

static void init_dot_tile(game_t *game, int tile_size)
{
    game->minimap->player_dot = sfCircleShape_create();
    sfCircleShape_setRadius(game->minimap->player_dot, tile_size / 2);
    sfCircleShape_setFillColor(game->minimap->player_dot, sfRed);
    game->minimap->tile = sfRectangleShape_create();
    sfRectangleShape_setSize(game->minimap->tile,
        (sfVector2f){tile_size - 1, tile_size - 1});
}

void init_minimap(game_t *game)
{
    int tile_size = get_tile_size(game);
    int weigth = game->map_size.x * tile_size;
    int height = game->map_size.y * tile_size;

    game->minimap->minimap_tex =
        sfRenderTexture_create(weigth, height, sfFalse);
    game->minimap->minimap_sprite = sfSprite_create();
    sfSprite_setTexture(game->minimap->minimap_sprite,
        sfRenderTexture_getTexture(game->minimap->minimap_tex), sfTrue);
    sfSprite_setPosition(game->minimap->minimap_sprite,
        (sfVector2f){MINI_PADDING, MINI_PADDING});
    init_dot_tile(game, tile_size);
}

void clean_mini_map(game_t *game)
{
    if (game->minimap->minimap_tex)
        sfRenderTexture_destroy(game->minimap->minimap_tex);
    if (game->minimap->minimap_sprite)
        sfSprite_destroy(game->minimap->minimap_sprite);
    if (game->minimap->player_dot)
        sfCircleShape_destroy(game->minimap->player_dot);
    if (game->minimap->tile)
        sfRectangleShape_destroy(game->minimap->tile);
}

void render_minimap(game_t *game)
{
    int tile_size = get_tile_size(game);

    sfRenderTexture_clear(game->minimap->minimap_tex,
        (sfColor){30, 30, 30, 180});
    for (int y = 0; y < game->map_size.y; y++)
        for (int x = 0; x < game->map_size.x; x++)
            draw_tile(game, x, y, tile_size);
    draw_player_dot(game, tile_size);
    sfRenderTexture_display(game->minimap->minimap_tex);
    sfRenderWindow_drawSprite(game->window,
        game->minimap->minimap_sprite, NULL);
}
