/*
** EPITECH PROJECT, 2026
** events
** File description:
** events .h file
*/

#ifndef EVENT_H_
    #define EVENT_H_

    #include "my.h"
    #include "wolf3d.h"

void analyse_events(sfRenderWindow *window, sfEvent event, game_t *game);

void temp_destroy_bg(game_t *game);
void init_background_and_minimap(game_t *game);

bool is_player_alive(player_t *p);


#endif /* !EVENT_H_ */
