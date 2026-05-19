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

static void update_button_pos(game_t *game, int new_x, int new_y)
{
    sfVector2f current_size = {game->win_s.x, game->win_s.y};
    sfVector2f new_pos = {game->win_s.x, game->win_s.y};
    sfVector2f size_factor = {new_x / current_size.x, new_y / current_size.y};

    update_ui_scale(game, &size_factor);
    for (int i = 0; i < NUM_BUTTONS; i++) {
        new_pos = sfRectangleShape_getPosition(game->buttons[i]->background);
        new_pos.x *= size_factor.x;
        new_pos.y *= size_factor.y;
        sfRectangleShape_setPosition(game->buttons[i]->background, new_pos);
        sfText_setPosition(game->buttons[i]->text, new_pos);
    }
}

static void change_window_size(game_t *game, int x, int y)
{
    sfVector2f new_pos;

    if (x <= 0 || y <= 0 || x > SCREEN_W || y >= 4000)
        return;
    update_button_pos(game, x, y);
    sfRenderWindow_close(game->window);
    game->window = create_window(x, y, "wolf3d");
    game->win_s.x = x;
    game->win_s.y = y;
    new_pos = (sfVector2f) {game->win_s.x, game->win_s.y};
    sfRenderTexture_destroy(game->minimap_tex);
    sfSprite_destroy(game->minimap_sprite);
    init_minimap(game);
}

static void change_inv_state(game_t *game)
{
    game->is_inv_open = !game->is_inv_open;
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

void analyse_events(sfRenderWindow *window, sfEvent event, game_t *game)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
        change_menu_state(game);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyI)
        printf("%i\n", game->player->stats->health);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyJ)
        save_map(game);
    handle_ui_events(game, event);
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyG)
        change_window_size(game, game->win_s.x + 200, game->win_s.y + 100);
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyH)
        change_window_size(game, game->win_s.x - 200, game->win_s.y - 100);
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyP)
        add_new_item(game);
    if (event.type == sfEvtKeyReleased && event.key.code == sfKeyB)
        bomb(game);
}
