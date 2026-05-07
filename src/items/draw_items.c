/*
** EPITECH PROJECT, 2026
** draw buttons
** File description:
** buttons but it draws
*/

#include "engine.h"
#include "wolf3d.h"
#include "my.h"
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <time.h>
#include "ui.h"

static void update_item_scale(item_t *item)
{
    sfVector2f original_scale = {1, 1};

    if (item->hovered) {
        original_scale.x *= 1.1;
        original_scale.y *= 1.1;
    }
    sfRectangleShape_setScale(item->background, original_scale);
}

void draw_item(game_t *game, item_t *item)
{
    sfFloatRect rect;

    rect = sfRectangleShape_getGlobalBounds(item->background);
    item->hovered =
        sfFloatRect_contains(&rect, game->mouse_pos.x, game->mouse_pos.y);
    update_item_scale(item);
    sfRenderWindow_drawRectangleShape(game->window, item->background,
        NULL);
}
