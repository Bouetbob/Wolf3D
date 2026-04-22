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

void update_button_scale(button_t *button)
{
    sfVector2f original_scale = button->original_scale;

    if (button->hovered) {
        original_scale.x *= 1.1;
        original_scale.y *= 1.1;
    }
    sfRectangleShape_setScale(button->background, original_scale);
    sfText_setScale(button->text, original_scale);
}

void draw_button(game_t *game, button_t *button)
{
    sfFloatRect rect;

    rect = sfRectangleShape_getGlobalBounds(button->background);
    button->hovered =
        sfFloatRect_contains(&rect, game->mouse_pos.x, game->mouse_pos.y);
    if (button->is_menu_button != game->is_menu_open)
        return;
    update_button_scale(button);
    sfRenderWindow_drawRectangleShape(game->window, button->background,
        NULL);
    sfRenderWindow_drawText(game->window, button->text, NULL);
}
