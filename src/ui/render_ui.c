/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** ui render
*/

#include "engine.h"
#include "ui.h"
#include <SFML/Config.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <time.h>
#include <stdio.h>


void init_ui_bar(player_t *player, game_t *game)
{
    sfTexture *tex = sfTexture_createFromFile("assets/UI/ui.png", NULL);
    sfRectangleShape *rect = sfRectangleShape_create();
    sfVector2f scale =
    {(float) game->win_s.x / 2000, 0.6};

    if (!tex || !rect)
        printf("Issue loading UI\n");
    player->ui_bar = rect;
    sfRectangleShape_setSize(player->ui_bar, (sfVector2f) {2000, 200 * 0.6});
    sfRectangleShape_setPosition(player->ui_bar,
        (sfVector2f) {0, game->win_s.y - 200});
    sfRectangleShape_setTexture(player->ui_bar, tex, sfFalse);
    sfRectangleShape_setScale(player->ui_bar, scale);
}

void update_ui_scale(game_t *game, sfVector2f *scale)
{
    sfVector2f new_pos;

    new_pos = sfRectangleShape_getPosition(game->player->ui_bar);
    new_pos.x *= scale->x;
    new_pos.y *= scale->y;
    sfRectangleShape_setScale(game->player->ui_bar, *scale);
    sfRectangleShape_setPosition(game->player->ui_bar, new_pos);
}

void draw_ui(game_t *game)
{
    sfRenderWindow_drawRectangleShape(game->window,
        game->player->ui_bar, NULL);
}
