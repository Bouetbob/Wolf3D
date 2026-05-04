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
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>

static void change_inv_state(game_t *game)
{
    game->is_inv_open = !game->is_inv_open;
}

void analyse_events(sfRenderWindow *window, sfEvent event, UNUSED game_t *game)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyT)
        game->map[2][2] = '1';
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyY)
        game->map[2][2] = '0';
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyG)
        change_menu_state(game);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyI)
        change_inv_state(game);
    for (int i = 0; i < NUM_BUTTONS; i++) {
        button_event(game, game->buttons[i], &event);
    }
}
