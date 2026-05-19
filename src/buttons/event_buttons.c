/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** buttons events
*/

#include "engine.h"
#include "ui.h"
#include <SFML/Graphics/Rect.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Mouse.h>
#include <stdio.h>

void print_game_info(game_t *game)
{
    printf("%i\n", game->scene_number);
    printf("%i %i\n", game->mouse_pos.x, game->mouse_pos.y);
    printf("%f %f\n", game->player->pos.x, game->player->pos.y);
}

void button_event(game_t *game, button_t *button, sfEvent *event)
{
    if (!game || !button || !event)
        return;
    if (event->type == sfEvtMouseButtonReleased
        && event->mouseButton.button == sfMouseLeft) {
        if (game->scene_number == button->is_menu_button && button->hovered) {
            button->on_click(game);
        }
    }
}
