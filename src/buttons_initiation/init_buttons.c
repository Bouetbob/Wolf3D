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
    button_params_t b1 = {"open menu", &p1, &sz, GAME};
    button_params_t b2 = {"open inventory", &p2, &sz, GAME};

    game->buttons[0] = init_button(&b1, game);
    game->buttons[0]->on_click = (void *) change_menu_state;
    game->buttons[2] = init_button(&b2, game);
    game->buttons[2]->on_click = (void *) change_inv_state;
}

void init_menu_buttons(game_t *game)
{
    sfVector2f sz = {110, 20};
    sfVector2f p1 = {(float) game->win_s.x / 2, game->win_s.y - 300};
    sfVector2f p2 = {game->win_s.x - 100, game->win_s.y - 100};
    sfVector2f p3 = {(float) game->win_s.x / 2, game->win_s.y - 150};
    sfVector2f p4 = {(float) game->win_s.x / 2, game->win_s.y - 450};
    button_params_t b1 = {"leave menu", &p1, &sz, MENU};
    button_params_t b2 = {"open inventory", &p2, &sz, MENU};
    button_params_t b3 = {"leave game", &p3, &sz, MENU};
    button_params_t b4 = {"open settings", &p4, &sz, MENU};

    game->buttons[1] = init_button(&b1, game);
    game->buttons[1]->on_click = (void *) change_menu_state;
    game->buttons[3] = init_button(&b2, game);
    game->buttons[3]->on_click = (void *) change_inv_state;
    game->buttons[4] = init_button(&b3, game);
    game->buttons[4]->on_click = (void *) leave_game;
    game->buttons[9] = init_button(&b4, game);
    game->buttons[9]->on_click = (void *) change_settings_state;
}

void init_inv_buttons(game_t *game)
{
    sfVector2f sz = {110, 20};
    sfVector2f p1 = {game->win_s.x - 100, 100};
    button_params_t b1 = {"close inventory", &p1, &sz, INVENTORY};

    game->buttons[5] = init_button(&b1, game);
    game->buttons[5]->on_click = (void *) change_inv_state;
}

static void init_resize_buttons(sfVector2f *p1, sfVector2f *p2, sfVector2f *p3,
    game_t *game)
{
    sfVector2f sz = {110, 20};
    button_params_t b1 = {"800x600", p1, &sz, SETTINGS};
    button_params_t b2 = {"1280x800", p2, &sz, SETTINGS};
    button_params_t b3 = {"1920x1080", p3, &sz, SETTINGS};

    game->buttons[6] = init_button(&b1, game);
    game->buttons[6]->on_click = (void *) min_window_size;
    game->buttons[7] = init_button(&b2, game);
    game->buttons[7]->on_click = (void *) mid_window_size;
    game->buttons[8] = init_button(&b3, game);
    game->buttons[8]->on_click = (void *) max_window_size;
}

static void init_higher_volume_buttons(button_params_t *b1,
    button_params_t *b2, button_params_t *b3, game_t *game)
{
    game->buttons[14] = init_button(b1, game);
    game->buttons[14]->on_click = (void *) mid_volume;
    game->buttons[15] = init_button(b2, game);
    game->buttons[15]->on_click = (void *) higher_volume;
    game->buttons[16] = init_button(b3, game);
    game->buttons[16]->on_click = (void *) highest_volume;
}

static void init_volume_buttons(sfVector2f *sz, game_t *game)
{
    sfVector2f p1 = {(float) SCREEN_W / 8, (float) SCREEN_H / 3 * 2};
    sfVector2f p2 = {(float) SCREEN_W / 8 * 2, (float) SCREEN_H / 3 * 2};
    sfVector2f p3 = {(float) SCREEN_W / 8 * 3, (float) SCREEN_H / 3 * 2};
    sfVector2f p4 = {(float) SCREEN_W / 8 * 4, (float) SCREEN_H / 3 * 2};
    sfVector2f p5 = {(float) SCREEN_W / 8 * 5, (float) SCREEN_H / 3 * 2};
    button_params_t b1 = {"0%", &p1, sz, SETTINGS};
    button_params_t b2 = {"20%", &p2, sz, SETTINGS};
    button_params_t b3 = {"60%", &p3, sz, SETTINGS};
    button_params_t b4 = {"80%", &p4, sz, SETTINGS};
    button_params_t b5 = {"100%", &p5, sz, SETTINGS};

    game->buttons[12] = init_button(&b1, game);
    game->buttons[12]->on_click = (void *) lowest_volume;
    game->buttons[13] = init_button(&b2, game);
    game->buttons[13]->on_click = (void *) lower_volume;
    init_higher_volume_buttons(&b3, &b4, &b5, game);
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
    button_params_t b4 = {"close settings", &p4, &sz, SETTINGS};
    button_params_t b5 = {"fullscreen", &p5, &sz, SETTINGS};

    init_resize_buttons(&p1, &p2, &p3, game);
    init_volume_buttons(&sz, game);
    game->buttons[10] = init_button(&b4, game);
    game->buttons[10]->on_click = (void *) change_settings_state;
    game->buttons[11] = init_button(&b5, game);
    game->buttons[11]->on_click = (void *) window_fullscreen;
}
