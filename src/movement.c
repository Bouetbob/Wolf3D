/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** movement
*/

#include "engine.h"
#include "wolf3d.h"
#include <SFML/System/Vector2.h>

static sfVector2f mouvement_up_down(sfVector2f *next, player_t *player,
    game_t *game)
{
    sfVector2f vec = player->direction_vec;

    if (sfKeyboard_isKeyPressed(sfKeyUp) || sfKeyboard_isKeyPressed(sfKeyZ)) {
        next->x += vec.x * game->timer->timeframe * player->stats->move_speed;
        next->y += vec.y * game->timer->timeframe * player->stats->move_speed;
    }
    if (sfKeyboard_isKeyPressed(sfKeyDown)
        || sfKeyboard_isKeyPressed(sfKeyS)) {
        next->x -= vec.x * game->timer->timeframe * player->stats->move_speed;
        next->y -= vec.y * game->timer->timeframe * player->stats->move_speed;
    }
    return *next;
}

static sfVector2f mouvement_right_left(sfVector2f *next, player_t *player,
    game_t *game)
{
    sfVector2f vec = player->direction_vec;

    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        next->x += vec.y * game->timer->timeframe * player->stats->move_speed;
        next->y -= vec.x * game->timer->timeframe * player->stats->move_speed;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        next->x -= vec.y * game->timer->timeframe * player->stats->move_speed;
        next->y += vec.x * game->timer->timeframe * player->stats->move_speed;
    }
    return *next;
}

static sfVector2f move_player(player_t *player, game_t *game)
{
    sfVector2f next = {player->pos.x, player->pos.y};

    next = mouvement_up_down(&next, player, game);
    next = mouvement_right_left(&next, player, game);
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
            player->pos.y, game))
        player->pos.x = next.x;
    if (!is_wall(player->pos.x,
            next.y + margin * (next.y > player->pos.y ? 1 : -1), game))
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
