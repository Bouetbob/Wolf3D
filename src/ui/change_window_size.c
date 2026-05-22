/*
** EPITECH PROJECT, 2026
** change_window_size
** File description:
** it changes the window size
*/

#include "engine.h"
#include "ui.h"
#include "wolf3d.h"
#include "event.h"
#include <SFML/Graphics/Types.h>

void update_button_and_text_pos(game_t *game, int new_x, int new_y)
{
    sfVector2f current_size = {game->win_s.x, game->win_s.y};
    sfVector2f new_pos = {game->win_s.x, game->win_s.y};
    sfVector2f size_factor = {new_x / current_size.x, new_y / current_size.y};

    for (int i = 0; i < NUM_BUTTONS; i++) {
        new_pos = sfRectangleShape_getPosition(game->buttons[i]->background);
        new_pos.x *= size_factor.x;
        new_pos.y *= size_factor.y;
        sfRectangleShape_setPosition(game->buttons[i]->background, new_pos);
        sfText_setPosition(game->buttons[i]->text, new_pos);
    }
    for (int i = 0; game->player->ui_texts[i]; i++) {
        new_pos = sfText_getPosition(game->player->ui_texts[i]);
        new_pos.x *= size_factor.x;
        new_pos.y *= size_factor.y;
        sfText_setPosition(game->player->ui_texts[i], new_pos);
        sfText_setScale(game->player->ui_texts[i], size_factor);
    }
}

void min_window_size(game_t *game)
{
    int x = 800;
    int y = 600;

    temp_destroy_bg(game);
    update_button_and_text_pos(game, x, y);
    sfRenderWindow_close(game->window);
    game->window = create_window(x, y, "wolf3d");
    game->win_s.x = x;
    game->win_s.y = y;
    sfRenderTexture_destroy(game->minimap->minimap_tex);
    sfSprite_destroy(game->minimap->minimap_sprite);
    init_background_and_minimap(game);
    update_ui_scale(game);
}

void mid_window_size(game_t *game)
{
    int x = 1280;
    int y = 800;

    temp_destroy_bg(game);
    update_button_and_text_pos(game, x, y);
    sfRenderWindow_close(game->window);
    game->window = create_window(x, y, "wolf3d");
    game->win_s.x = x;
    game->win_s.y = y;
    sfRenderTexture_destroy(game->minimap->minimap_tex);
    sfSprite_destroy(game->minimap->minimap_sprite);
    init_background_and_minimap(game);
    update_ui_scale(game);
}

void max_window_size(game_t *game)
{
    int x = 1920;
    int y = 1080;

    temp_destroy_bg(game);
    update_button_and_text_pos(game, x, y);
    sfRenderWindow_close(game->window);
    game->window = create_window(x, y, "wolf3d");
    game->win_s.x = x;
    game->win_s.y = y;
    sfRenderTexture_destroy(game->minimap->minimap_tex);
    sfSprite_destroy(game->minimap->minimap_sprite);
    init_background_and_minimap(game);
    update_ui_scale(game);
}

void window_fullscreen(game_t *game)
{
    int x = 1920;
    int y = 1080;

    temp_destroy_bg(game);
    update_button_and_text_pos(game, x, y);
    sfRenderWindow_close(game->window);
    game->window = sfRenderWindow_create((sfVideoMode)
        {x, y, 16}, "wolf3d", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(game->window, 60);
    game->win_s.x = x;
    game->win_s.y = y;
    sfRenderTexture_destroy(game->minimap->minimap_tex);
    sfSprite_destroy(game->minimap->minimap_sprite);
    init_background_and_minimap(game);
    update_ui_scale(game);
}
