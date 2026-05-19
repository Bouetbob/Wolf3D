/*
** EPITECH PROJECT, 2026
** draw buttons
** File description:
** buttons but it draws
*/

#include "engine.h"
#include "wolf3d.h"
#include "my.h"
#include <SFML/Config.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <time.h>
#include "ui.h"

int amount_of_items(player_t *player)
{
    item_t **items = player->inventory;
    int amount = 0;

    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (items[i])
            amount++;
    }
    return amount;
}

int get_inv_free_spot(game_t *game)
{
    item_t **inv = game->player->inventory;
    int pos = 0;

    if (amount_of_items(game->player) >= INVENTORY_SIZE)
        return -1;
    while (inv[pos]) {
        if (inv[pos]->uses == 0) {
            free(inv[pos]);
            inv[pos] = NULL;
            break;
        }
        pos++;
    }
    return pos;
}

void item_event(game_t *game, item_t *item, sfEvent *event)
{
    if (!game || !item || !event)
        return;
    if (event->type == sfEvtMouseButtonReleased
        && event->mouseButton.button == sfMouseLeft) {
        if (game->scene_number == 2 && item->hovered) {
            item->uses -= 1;
        }
        if (game->scene_number == 2 && item->hovered && item->on_use != NULL) {
            item->on_use(game);
        }
    }
}
