/*
** EPITECH PROJECT, 2026
** events
** File description:
** events file
*/

#include "engine.h"
#include "my.h"
#include "wolf3d.h"
#include "ui.h"
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>
#include "map.h"

void analyse_events(sfRenderWindow *window, sfEvent event, UNUSED game_t *game)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyT)
        map[5][5] = 1;
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyY)
        map[5][5] = 0;
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyG)
        change_menu_state(game);
    for (int i = 0; i < NUM_BUTTONS; i++) {
        button_event(game, game->buttons[i], &event);
    }
}
