/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** main file
*/

//hours spent on this : around 25 (22/04 11:33)

#include <stdio.h>
#include "enemy.h"
#include "engine.h"
#include "event.h"
#include "map.h"
#include "my.h"
#include "ui.h"
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
#include <SFML/Window/WindowBase.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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

static void render_item(game_t *game, item_t **items, sfVector2f *item_pos,
    int i)
{
    if (items[i]) {
        item_pos->x += 100;
        if (item_pos->x > (float) game->win_s.x / 2) {
            item_pos->x = 100;
            item_pos->y += 100;
        }
        sfRectangleShape_setPosition(items[i]->background, *item_pos);
        draw_item(game, items[i]);
    }
}

static void render_inventory(game_t *game)
{
    item_t **items = game->player->inventory;
    sfVector2f item_pos = {0, 100};

    for (int i = 0; i < INVENTORY_SIZE; i++) {
        render_item(game, items, &item_pos, i);
    }
}

void init_background_and_minimap(game_t *game)
{
    init_minimap(game);
    game->background->floor_image = sfImage_create(SCREEN_W, SCREEN_H);
    game->background->floor_render_tex = sfTexture_create(SCREEN_W, SCREEN_H);
    game->background->floor_sprite = sfSprite_create();
    sfSprite_setTexture(game->background->floor_sprite,
        game->background->floor_render_tex, sfTrue);
    game->background->floor_tex_img =
        sfTexture_copyToImage(game->tex->ray_tex[TEX_FLOOR]);
    game->background->ceil_tex_img =
        sfTexture_copyToImage(game->tex->ray_tex[TEX_CEIL]);
}

static void render_weapon(game_t *game)
{
    weapon_t *weapon = game->player->weapons[game->player->curr_weapon];

    if (weapon->frame != 0) {
        weapon->time_until_switch -= game->timer->timeframe;
        if (weapon->time_until_switch <= 0) {
            weapon->frame += 1;
            weapon->time_until_switch = weapon->frame_time;
        }
        if (weapon->frame == 4)
            weapon->frame = 0;
    }
    weapon->rect.left = 128 * weapon->frame;
    sfSprite_setTextureRect(weapon->sprite, weapon->rect);
    sfRenderWindow_drawSprite(game->window,
        weapon->sprite, NULL);
}

static void render_game(game_t *game, ray_t *ray,
    sfVertexArray *vertexarr[NUM_TEXTURES_RAY])
{
    handle_movement(game->player, game);
    update_enemies(game);
    render_raycast(game, ray, vertexarr);
    draw_ui(game);
    if (game->minimap->need_map_render)
        render_minimap(game);
    render_weapon(game);
}

void rendering_function(game_t *game, ray_t *ray,
    sfVertexArray *vertexarr[NUM_TEXTURES_RAY])
{
    sfRenderWindow_clear(game->window, sfBlack);
    if (!game->scene_number) {
        render_game(game, ray, vertexarr);
    }
    if (game->scene_number == 2) {
        render_inventory(game);
    }
    for (int i = 0; i < NUM_BUTTONS; i++) {
        draw_button(game, game->buttons[i]);
    }
    sfRenderWindow_display(game->window);
}

void main_game_loop(game_t *game, ray_t *ray)
{
    sfVertexArray *vertexarr[NUM_TEXTURES_RAY];

    for (int i = 0; i < NUM_TEXTURES_RAY; i++) {
        vertexarr[i] = sfVertexArray_create();
        sfVertexArray_setPrimitiveType(vertexarr[i], sfTriangles);
    }
    init_background_and_minimap(game);
    while (sfRenderWindow_isOpen(game->window)) {
        setup_time(game);
        while (sfRenderWindow_pollEvent(game->window, &game->event))
            analyse_events(game->window, game->event, game);
        game->mouse_pos = sfMouse_getPositionRenderWindow(game->window);
        rendering_function(game, ray, vertexarr);
    }
    save_map(game);
    free_ressource(game, ray, vertexarr);
}

int main(UNUSED int ac, UNUSED char **av, UNUSED char **env)
{
    game_t *game = malloc(sizeof(game_t));
    ray_t *ray = malloc(sizeof(ray_t));

    if (ac != 2)
        return (84);
    check_exit_conditions(game, ray, env);
    game->player = malloc(sizeof(player_t));
    if (!game->player)
        exit_with_message("can't malloc game->player struct\n", 2, 84);
    if (init_all(game) == 84 || load_map_from_file(game, av[1]) == 84)
        return (84);
    if (load_window(game) == 84)
        return (84);
    main_game_loop(game, ray);
    return 0;
}
