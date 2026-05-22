/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** menu background sprite
*/

#include "engine.h"
#include "ui.h"
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/System/Vector2.h>

void init_menu_bg(game_t *game)
{
    sfTexture *tex = sfTexture_createFromFile(
        "assets/UI/ui_background.png", NULL);

    game->menu_bg = NULL;
    if (!tex)
        return;
    game->menu_bg = sfSprite_create();
    if (!game->menu_bg) {
        sfTexture_destroy(tex);
        return;
    }
    sfSprite_setTexture(game->menu_bg, tex, sfTrue);
}

void draw_menu_bg(game_t *game)
{
    sfVector2u tex_size;
    sfVector2f scale;

    if (game->scene_number == GAME || !game->menu_bg)
        return;
    tex_size = sfTexture_getSize(
        sfSprite_getTexture(game->menu_bg));
    scale.x = (float)game->win_s.x / (float)tex_size.x;
    scale.y = (float)game->win_s.y / (float)tex_size.y;
    sfSprite_setPosition(game->menu_bg, (sfVector2f){0.0f, 0.0f});
    sfSprite_setScale(game->menu_bg, scale);
    sfRenderWindow_drawSprite(game->window, game->menu_bg, NULL);
}
