/*
** EPITECH PROJECT, 2026
** draw buttons
** File description:
** buttons but it draws
*/

#include "wolf3d.h"
#include "my.h"
#include <time.h>
#include "ui.h"

void draw_button(game_t *game, button_t *button)
{
    sfRenderWindow_drawRectangleShape(game->window, button->background,
        NULL);
    sfRenderWindow_drawText(game->window, button->text, NULL);
}
