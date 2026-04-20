/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** movement
*/

#include "wolf3d.h"

static sfVector2f move_player(player_t *player, game_t *game)
{
    sfVector2f next = {player->pos.x, player->pos.y};

    if (sfKeyboard_isKeyPressed(sfKeyUp) || sfKeyboard_isKeyPressed(sfKeyZ)) {
        next.x += player->direction_vec.x * game->timer->timeframe * MOVESPEED;
        next.y += player->direction_vec.y * game->timer->timeframe * MOVESPEED;
    }
    if (sfKeyboard_isKeyPressed(sfKeyDown)
        || sfKeyboard_isKeyPressed(sfKeyS)) {
        next.x -= player->direction_vec.x * game->timer->timeframe * MOVESPEED;
        next.y -= player->direction_vec.y * game->timer->timeframe * MOVESPEED;
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        next.x += player->direction_vec.y * game->timer->timeframe * MOVESPEED;
        next.y -= player->direction_vec.x * game->timer->timeframe * MOVESPEED;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        next.x -= player->direction_vec.y * game->timer->timeframe * MOVESPEED;
        next.y += player->direction_vec.x * game->timer->timeframe * MOVESPEED;
    }
    return next;
}

static void rotate_player(player_t *player, game_t *game)
{
    if (sfKeyboard_isKeyPressed(sfKeyRight))
        player->angle += ROTATESPEED * game->timer->timeframe;
    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        player->angle -= ROTATESPEED * game->timer->timeframe;
    if (player->angle >= 360)
        player->angle -= 360;
    if (player->angle < 0)
        player->angle += 360;
    if (sfKeyboard_isKeyPressed(sfKeyA))
        player->FOV *= 1.01;
    if (sfKeyboard_isKeyPressed(sfKeyE))
        player->FOV /= 1.01;
    if (sfKeyboard_isKeyPressed(sfKeyK))
        player->FOV = FORMER_FOV;
}

void handle_movement(player_t *player, game_t *game)
{
    sfVector2f next = {player->pos.x, player->pos.y};
    float margin = 0.1;
    sfTime elapsed;

    next = move_player(player, game);
    if (!is_wall(next.x + margin * (next.x > player->pos.x ? 1 : -1),
            player->pos.y))
        player->pos.x = next.x;
    if (!is_wall(player->pos.x,
            next.y + margin * (next.y > player->pos.y ? 1 : -1)))
        player->pos.y = next.y;
    if (sfKeyboard_isKeyPressed(sfKeyF)) {
        elapsed = sfClock_getElapsedTime(game->key_clock);
        if (sfTime_asMilliseconds(elapsed) >= 500) {
            player->stats->flashlight = !player->stats->flashlight;
            sfClock_restart(game->key_clock);
        }
    }
    rotate_player(player, game);
    update_player(player);
}
