/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** utils
*/

#include "wolf3d.h"
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Window/VideoMode.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

bool is_player_alive(player_t *p)
{
    if (p->stats->health <= 0) {
        if (p->score <= 150)
            printf("big loss right here..\n");
        if (p->score <= 500 && p->score > 150)
            printf("now we're getting somewhere\n");
        if (p->score <= 1000 && p->score > 500)
            printf("good job!\n");
        return false;
    }
    return true;
}

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

static void dir_giver(player_t *player)
{
    player->dir_v = (sfVector2f) {cos(player->rads), sin(player->rads)};
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
