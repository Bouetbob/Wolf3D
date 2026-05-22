/*
** EPITECH PROJECT, 2026
** events
** File description:
** events file
*/

#include "engine.h"
#include "event.h"
#include "map.h"
#include "my.h"
#include "ui.h"
#include "wolf3d.h"
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/VideoMode.h>
#include <SFML/Window/WindowBase.h>
#include <stdbool.h>
#include <stdio.h>
#include "weapons.h"

void change_window_size(game_t *game, int x, int y)
{
    if (x <= 0 || y <= 0 || x >= 2000 || y >= 4000)
        return;
    temp_destroy_bg(game);
    update_button_and_text_pos(game, x, y);
    sfRenderWindow_destroy(game->window);
    game->window = create_window(x, y, "wolf3d");
    game->win_s.x = x;
    game->win_s.y = y;
    clean_mini_map(game);
    init_background_and_minimap(game);
    resize_floor_ceiling(game);
    update_ui_scale(game);
}

void change_settings_state(game_t *game)
{
    if (game->scene_number != SETTINGS)
        game->scene_number = SETTINGS;
    else
        game->scene_number = MENU;
}

void change_inv_state(game_t *game)
{
    if (game->scene_number != INVENTORY)
        game->scene_number = INVENTORY;
    else
        game->scene_number = MENU;
}

static void handle_ui_events(game_t *game, sfEvent event)
{
    for (int i = 0; i < NUM_BUTTONS; i++)
        button_event(game, game->buttons[i], &event);
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        item_event(game, game->player->inventory[i], &event);
        if (game->player->inventory[i]
            && game->player->inventory[i]->uses == 0) {
            free(game->player->inventory[i]);
            game->player->inventory[i] = NULL;
        }
    }
}

bool is_enemy(sfVector2f *pos, game_t *game)
{
    int map_x = (int) pos->x;
    int map_y = (int) pos->y;
    char to_see;

    if (map_x < 0 || map_y < 0 || map_x >= game->map_size.x
        || map_y >= game->map_size.y)
        return false;
    to_see = game->map[map_x][map_y];
    if (to_see == 'T' || to_see == 'M')
        return true;
    return false;
}

void analyse_events(sfRenderWindow *window, sfEvent event, game_t *game)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
        change_menu_state(game);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyM)
        game->minimap->need_map_render = !game->minimap->need_map_render;
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeySpace)
        shoot_gun(game);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyJ)
        save_map(game);
    handle_ui_events(game, event);
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyG)
        change_window_size(game, game->win_s.x + 200, game->win_s.y + 100);
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyH)
        change_window_size(game, game->win_s.x - 200, game->win_s.y - 100);
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyR)
        reload_gun(game);
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyTab)
        change_inv_state(game);
}
