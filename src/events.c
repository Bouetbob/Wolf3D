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

void analyse_events(sfRenderWindow *window, sfEvent event, game_t *game)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
        sfRenderWindow_close(window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyT)
        map[5][5] = 1;
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyY)
        map[5][5] = 0;
}
