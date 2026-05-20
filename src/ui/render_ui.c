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
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <stdio.h>
#include <time.h>

void init_ui_bar(player_t *player, game_t *game)
{
    sfTexture *tex = sfTexture_createFromFile("assets/UI/ui.png", NULL);
    sfRectangleShape *rect = sfRectangleShape_create();
    sfVector2f scale = {(float) game->win_s.x / 2000, 0.6};

    if (!tex || !rect)
        printf("Issue loading UI\n");
    player->ui_bar = rect;
    sfRectangleShape_setSize(player->ui_bar, (sfVector2f) {2000, 200 / 0.6});
    sfRectangleShape_setPosition(player->ui_bar,
        (sfVector2f) {0, game->win_s.y - 200});
    sfRectangleShape_setTexture(player->ui_bar, tex, sfFalse);
    sfRectangleShape_setScale(player->ui_bar, scale);
}

static void update_gun_scale(game_t *game)
{
    weapon_t **weapons = game->player->weapons;
    float scale_x = (float)game->win_s.x / SCREEN_W;
    float scale_y = (float)game->win_s.y / SCREEN_H;

    for (int i = 0; weapons[i]; i++) {
        sfSprite_setPosition(weapons[i]->sprite,
            (sfVector2f) {(float) game->win_s.x / 2 - 156.0f * scale_x,
                game->win_s.y - 256.0f * scale_y});
        sfSprite_setScale(weapons[i]->sprite,
            (sfVector2f){2.0f * scale_x, 2.0f * scale_y});
    }
}

void update_ui_scale(game_t *game)
{
    sfVector2f new_pos;

    new_pos = sfRectangleShape_getPosition(game->player->ui_bar);
    new_pos.x = 0;
    new_pos.y = 0;
    new_pos.y = game->win_s.y - (((float) game->win_s.y / 2000) * 333);
    sfRectangleShape_setScale(game->player->ui_bar,
        (sfVector2f) {(float) game->win_s.x / 2000,
            (float) game->win_s.y / 2000});
    sfRectangleShape_setPosition(game->player->ui_bar, new_pos);
    update_gun_scale(game);
}

void draw_ui(game_t *game)
{
    get_string_from_num(game->player->stats->health,
        game->player->ui_texts[0]);
    get_string_from_num(game->player->score, game->player->ui_texts[1]);
    get_string_from_num(game->player->weapons[game->player->curr_weapon]->ammo,
        game->player->ui_texts[3]);
    sfRenderWindow_drawRectangleShape(game->window, game->player->ui_bar,
        NULL);
    for (int i = 0; game->player->ui_texts[i]; i++) {
        sfRenderWindow_drawText(game->window, game->player->ui_texts[i], NULL);
    }
}
