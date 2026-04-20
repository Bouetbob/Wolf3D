/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** utils
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Window/VideoMode.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "wolf3d.h"

bool has_display(char **env)
{
    int i = 0;

    while (env[i]) {
        if (strncmp(env[i], "DISPLAY=", 8) == 0)
            return true;
        i++;
    }
    return false;
}

void exit_with_message(char *exit_message, int message_channel, int exit_value)
{
    write(message_channel, exit_message, strlen(exit_message));
    exit(exit_value);
}

void dir_giver(player_t *player)
{
    player->direction_vec =
        (sfVector2f) {cos(player->rads), sin(player->rads)};
}

void rad_giver(player_t *player)
{
    player->rads = player->angle * 0.017453f;
}

void update_player(player_t *player)
{
    rad_giver(player);
    dir_giver(player);
}
