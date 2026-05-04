/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** main file
*/

//hours spent on this : around 25 (22/04 11:33)

#include "engine.h"
#include "my.h"
#include "wolf3d.h"
#include "event.h"
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
#include <stdio.h>
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

static void render_inventory(game_t *game)
{
    item_t **items = game->player->inventory;

    sfRenderWindow_drawSprite(game->window, items[0]->sprite, NULL);
    sfRenderWindow_drawSprite(game->window, items[1]->sprite, NULL);
    sfRenderWindow_drawSprite(game->window, items[2]->sprite, NULL);
    sfRenderWindow_drawSprite(game->window, items[3]->sprite, NULL);
}

void init_floor_ceiling(game_t *game)
{
    game->floor = sfRectangleShape_create();
    sfRectangleShape_setSize(game->floor, (sfVector2f)
        {sfRenderWindow_getSize(game->window).x,
            sfRenderWindow_getSize(game->window).y / 2});
    sfRectangleShape_setFillColor(game->floor, sfColor_fromRGB(169, 169, 169));
    sfRectangleShape_setPosition(game->floor, (sfVector2f){0,
            sfRenderWindow_getSize(game->window).y / 2});
    game->ceiling = sfRectangleShape_create();
    sfRectangleShape_setSize(game->ceiling, (sfVector2f){
            sfRenderWindow_getSize(game->window).x,
            sfRenderWindow_getSize(game->window).y / 2});
    sfRectangleShape_setFillColor(game->ceiling, sfColor_fromRGB(90, 90, 90));
    sfRectangleShape_setPosition(game->ceiling, (sfVector2f){0, 0});
}

void rendering_function(game_t *game, ray_t *ray,
    sfVertexArray *vertexarr[NUM_TEXTURES])
{
    sfRenderWindow_clear(game->window, sfBlack);
    if (!game->is_menu_open) {
        handle_movement(game->player, game);
        sfRenderWindow_drawRectangleShape(game->window, game->floor, NULL);
        sfRenderWindow_drawRectangleShape(game->window, game->ceiling, NULL);
        render_raycast(game, ray, vertexarr);
    }
    if (game->is_inv_open) {
        render_inventory(game);
    }
    for (int i = 0; i < NUM_BUTTONS; i++) {
        draw_button(game, game->buttons[i]);
    }
    sfRenderWindow_display(game->window);
}

void main_game_loop(game_t *game, ray_t *ray)
{
    sfVertexArray *vertexarr[NUM_TEXTURES];

    for (int i = 0; i < NUM_TEXTURES; i++) {
        vertexarr[i] = sfVertexArray_create();
        sfVertexArray_setPrimitiveType(vertexarr[i], sfTriangles);
    }
    init_floor_ceiling(game);
    while (sfRenderWindow_isOpen(game->window)) {
        setup_time(game);
        while (sfRenderWindow_pollEvent(game->window, &game->event))
            analyse_events(game->window, game->event, game);
        game->mouse_pos = sfMouse_getPositionRenderWindow(game->window);
        rendering_function(game, ray, vertexarr);
    }
    free_ressource(game, ray, vertexarr);
}

int main(UNUSED int ac, UNUSED char **av, UNUSED char **env)
{
    game_t *game = malloc(sizeof(game_t));
    ray_t *ray = malloc(sizeof(ray_t));

    if (ac != 2)
        return (84);
    check_exit_conditions(game, ray, env);
    game->is_inv_open = false;
    game->player = malloc(sizeof(player_t));
    if (!game->player)
        exit_with_message("can't malloc game->player struct\n", 2, 84);
    if (load_map_from_file(game, av[1]) == 84 || init_all(game) == 84)
        return (84);
    main_game_loop(game, ray);
    return 0;
}
