/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** init all da buttons
*/

#include "engine.h"
#include "event.h"
#include "map.h"
#include "wolf3d.h"
#include <SFML/Graphics.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>

void init_game_buttons(game_t *game)
{
    sfVector2f sz = {110, 20};
    sfVector2f p1 = {game->win_s.x - 100, 100};
    sfVector2f p2 = {game->win_s.x - 100, game->win_s.y - 100};

    game->buttons[0] = init_button("enter menu", &p1, &sz, GAME);
    game->buttons[0]->on_click = (void *) change_menu_state;
    game->buttons[2] = init_button("open inventory", &p2, &sz, GAME);
    game->buttons[2]->on_click = (void *) change_inv_state;
}

void init_menu_buttons(game_t *game)
{
    sfVector2f sz = {110, 20};
    sfVector2f p1 = {(float) game->win_s.x / 2, game->win_s.y - 300};
    sfVector2f p2 = {game->win_s.x - 100, game->win_s.y - 100};
    sfVector2f p3 = {(float) game->win_s.x / 2, game->win_s.y - 150};
    sfVector2f p4 = {(float) game->win_s.x / 2, game->win_s.y - 450};

    game->buttons[1] = init_button("leave menu", &p1, &sz, MENU);
    game->buttons[1]->on_click = (void *) change_menu_state;
    game->buttons[3] = init_button("open inventory", &p2, &sz, MENU);
    game->buttons[3]->on_click = (void *) change_inv_state;
    game->buttons[4] = init_button("leave game", &p3, &sz, MENU);
    game->buttons[4]->on_click = (void *) leave_game;
    game->buttons[9] = init_button("open settings", &p4, &sz, MENU);
    game->buttons[9]->on_click = (void *) change_settings_state;
}

void init_inv_buttons(game_t *game)
{
    sfVector2f sz = {110, 20};
    sfVector2f p1 = {game->win_s.x - 100, 100};

    game->buttons[5] = init_button("close inventory", &p1, &sz, INVENTORY);
    game->buttons[5]->on_click = (void *) change_inv_state;
}

void init_settings_buttons(game_t *game)
{
    sfVector2f sz = {110, 20};
    sfVector2f p1 = {((float) game->win_s.x / 4), (float) game->win_s.y / 4};
    sfVector2f p2 = {((float) game->win_s.x / 4) * 2,
        (float) game->win_s.y / 4};
    sfVector2f p3 = {((float) game->win_s.x / 4) * 3,
        (float) game->win_s.y / 4};
    sfVector2f p4 = {(float) game->win_s.x / 2, game->win_s.y - 150};
    sfVector2f p5 = {p2.x, p4.y / 2};

    game->buttons[6] = init_button("800x600", &p1, &sz, SETTINGS);
    game->buttons[6]->on_click = (void *) min_window_size;
    game->buttons[7] = init_button("1280x800", &p2, &sz, SETTINGS);
    game->buttons[7]->on_click = (void *) mid_window_size;
    game->buttons[8] = init_button("1920x1080", &p3, &sz, SETTINGS);
    game->buttons[8]->on_click = (void *) max_window_size;
    game->buttons[10] = init_button("close settings", &p4, &sz, SETTINGS);
    game->buttons[10]->on_click = (void *) change_settings_state;
    game->buttons[11] = init_button("fullscreen", &p5, &sz, SETTINGS);
    game->buttons[11]->on_click = (void *) window_fullscreen;
}
