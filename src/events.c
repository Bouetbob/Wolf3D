/*
** EPITECH PROJECT, 2026
** events
** File description:
** events file
*/

#include "engine.h"
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
#include <stdio.h>

static void add_new_item(game_t *game)
{
    item_t **inv = game->player->inventory;
    int pos = get_inv_free_spot(game);
    int to_add = rand() % NUM_TEXTURES_ITEMS;

    if (pos == -1)
        return;
    if (to_add == 0)
        inv[pos] = BOMB;
    if (to_add == 1)
        inv[pos] = PIE;
    if (to_add == 2)
        inv[pos] = GUM;
    if (to_add == 3)
        inv[pos] = FLASH;
}

static void update_button_and_text_pos(game_t *game, int new_x, int new_y)
{
    sfVector2f current_size = {game->win_s.x, game->win_s.y};
    sfVector2f new_pos = {game->win_s.x, game->win_s.y};
    sfVector2f size_factor = {new_x / current_size.x, new_y / current_size.y};

    for (int i = 0; i < NUM_BUTTONS; i++) {
        new_pos = sfRectangleShape_getPosition(game->buttons[i]->background);
        new_pos.x *= size_factor.x;
        new_pos.y *= size_factor.y;
        sfRectangleShape_setPosition(game->buttons[i]->background, new_pos);
        sfText_setPosition(game->buttons[i]->text, new_pos);
    }
    for (int i = 0; game->player->ui_texts[i]; i++) {
        new_pos = sfText_getPosition(game->player->ui_texts[i]);
        new_pos.x *= size_factor.x;
        new_pos.y *= size_factor.y;
        sfText_setPosition(game->player->ui_texts[i], new_pos);
        sfText_setScale(game->player->ui_texts[i], size_factor);
    }
}

void change_window_size(game_t *game, int x, int y)
{
    sfVector2f new_pos;

    if (x <= 0 || y <= 0 || x > SCREEN_W || y >= 4000)
        return;
    update_button_and_text_pos(game, x, y);
    sfRenderWindow_close(game->window);
    game->window = create_window(x, y, "wolf3d");
    game->win_s.x = x;
    game->win_s.y = y;
    new_pos = (sfVector2f) {game->win_s.x, game->win_s.y};
    clean_mini_map(game);
    init_minimap(game);
    update_ui_scale(game);
    new_pos = (sfVector2f) {game->win_s.x, (float) game->win_s.y / 2};
}

static void change_inv_state(game_t *game)
{
    if (game->scene_number != 2)
        game->scene_number = 2;
    else
        game->scene_number = 1;
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

static void shoot_gun(game_t *game)
{
    player_t *p = game->player;
    weapon_t *curr_weapon = p->weapons[p->curr_weapon];

    if (curr_weapon->ammo <= 0)
        return;
    curr_weapon->ammo--;
    curr_weapon->frame = 1;
    game->player->score++;
    return;
}

static void reload_gun(game_t *game)
{
    game->player->weapons[game->player->curr_weapon]->ammo =
        game->player->weapons[game->player->curr_weapon]->max_ammo;
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
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyB)
        change_inv_state(game);
}
