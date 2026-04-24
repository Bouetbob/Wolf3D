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

void rendering_function(game_t *game, ray_t *ray,
    sfVertexArray *vertexarr[NUM_TEXTURES])
{
    sfRenderWindow_clear(game->window, sfBlack);
    if (!game->is_menu_open) {
        handle_movement(game->player, game);
        render_raycast(game, ray, vertexarr);
    }
    for (int i = 0; i < NUM_BUTTONS; i++) {
        draw_button(game, game->buttons[i]);
    }
    sfRenderWindow_display(game->window);
}

void main_game_loop(game_t *game, ray_t *ray,
    sfVertexArray *vertexarr[NUM_TEXTURES])
{
    for (int t = 0; t < NUM_TEXTURES; t++) {
        vertexarr[t] = sfVertexArray_create();
        sfVertexArray_setPrimitiveType(vertexarr[t], sfTriangles);
    }
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
    sfVertexArray *vertexarr[NUM_TEXTURES];

    if (ac != 2)
        return (84);
    check_exit_conditions(game, ray, env);
    game->player = malloc(sizeof(player_t));
    if (!game->player)
        exit_with_message("can't malloc game->player struct\n", 2, 84);
    for (int i = 0; i < NUM_TEXTURES; i++) {
        vertexarr[i] = sfVertexArray_create();
        sfVertexArray_setPrimitiveType(vertexarr[i], sfTriangles);
    }
    if (init_all(game) == 84 || map_filler(game, av[1]) == 84)
        return (84);
    main_game_loop(game, ray, vertexarr);
    return 0;
}
