/*
** EPITECH PROJECT, 2026
** Wolf3D
** File description:
** init_game
*/

#include "enemy.h"
#include "engine.h"
#include "event.h"
#include "map.h"
#include "wolf3d.h"
#include <SFML/Graphics.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void setup_time(game_t *game)
{
    game->timer->oldtime = game->timer->currenttime;
    game->timer->time = sfClock_getElapsedTime(game->key_clock);
    game->timer->currenttime = sfTime_asSeconds(game->timer->time);
    game->timer->timeframe = (game->timer->currenttime - game->timer->oldtime);
}

int load_window(game_t *game)
{
    game->window = create_window(game->win_s.x, game->win_s.y, "wolf3d");
    if (!game->window)
        return (84);
    return (0);
}

int load_item_textures(sfTexture *textures[NUM_TEXTURES_ITEMS])
{
    textures[0] = sfTexture_createFromFile("assets/Items/bomb.jpeg", NULL);
    textures[1] = sfTexture_createFromFile("assets/Items/applepie.jpeg", NULL);
    textures[2] = sfTexture_createFromFile("assets/Items/gum.jpeg", NULL);
    textures[3] = sfTexture_createFromFile("assets/Items/flash.jpeg", NULL);
    if (!textures[0] || !textures[1] || !textures[2] || !textures[3])
        return (84);
    return (0);
}

static void load_ray_textures(sfTexture *textures[NUM_TEXTURES_RAY])
{
    textures[1] =
        sfTexture_createFromFile("assets/World_Textures/redbrick.png", NULL);
    textures[2] =
        sfTexture_createFromFile("assets/World_Textures/wood.png", NULL);
    textures[3] =
        sfTexture_createFromFile("assets/World_Textures/bluestone.png", NULL);
    textures[4] =
        sfTexture_createFromFile("assets/World_Textures/eagle.png", NULL);
    textures[5] =
        sfTexture_createFromFile("assets/World_Textures/greystone.png", NULL);
    textures[6] =
        sfTexture_createFromFile("assets/World_Textures/colorstone.png", NULL);
    textures[7] = sfTexture_createFromFile(
        "assets/World_Textures/purplestone.png", NULL);
    textures[8] =
        sfTexture_createFromFile("assets/World_Textures/mossy.png", NULL);
    textures[9] =
        sfTexture_createFromFile("assets/World_Textures/floor.png", NULL);
}

static int init_textures(game_t *game)
{
    size_t r_s = sizeof(sfTexture *) * NUM_TEXTURES_RAY;
    size_t i_s = sizeof(sfTexture *) * NUM_TEXTURES_ITEMS;

    memset(game->tex->ray_tex, 0, r_s);
    memset(game->tex->item_tex, 0, i_s);
    game->enemy_texture = sfTexture_createFromFile(
        "assets/World_Textures/enemy_magnum.png", NULL);
    if (!game->enemy_texture)
        return (84);
    return (0);
}

void init_ui_texts(game_t *game)
{
    player_t *p = game->player;
    sfVector2f hp_pos = {670, game->win_s.y - 80};
    sfVector2f sc_pos = {170, game->win_s.y - 80};
    sfVector2f num_pos = {400, game->win_s.y - 110};
    sfVector2f am_pos = {800, game->win_s.y - 80};

    p->ui_texts[0] = init_text_item("health", &hp_pos, 40, game);
    p->ui_texts[1] = init_text_item("score", &sc_pos, 40, game);
    p->ui_texts[2] = init_text_item("1", &num_pos, 80, game);
    p->ui_texts[3] = init_text_item("ammo", &am_pos, 40, game);
    p->ui_texts[4] = NULL;
}

static void init_buttons(game_t *game)
{
    init_game_buttons(game);
    init_menu_buttons(game);
    init_inv_buttons(game);
    init_settings_buttons(game);
}

static int alloc_essentials(game_t *game)
{
    game->timer = malloc(sizeof(timers_t));
    game->tex = malloc(sizeof(textures_t));
    game->buttons = malloc(sizeof(button_t *) * NUM_BUTTONS);
    game->ray_data = malloc(sizeof(ray_data_t));
    game->minimap = malloc(sizeof(minimap_t));
    game->background = malloc(sizeof(background_t));
    if (!game->timer || !game->buttons || !game->tex || !game->ray_data ||
        !game->minimap || !game->background)
        return (84);
    game->minimap->need_map_render = false;
    game->timer->oldtime = 0.0f;
    game->timer->currenttime = 0.0f;
    game->timer->timeframe = 0.0f;
    game->enemies = malloc(sizeof(enemy_t *) * MAX_ENEMIES);
    game->enemy_count = 0;
    if (!game->enemies)
        return (84);
    for (int i = 0; i < MAX_ENEMIES; i++)
        game->enemies[i] = NULL;
    return (0);
}

int init_all(game_t *game)
{
    game->win_s.x = SCREEN_W;
    game->win_s.y = SCREEN_H;
    if (alloc_essentials(game) == 84 || init_textures(game) == 84)
        return (84);
    memset(game->minimap, 0, sizeof(minimap_t));
    memset(game->background, 0, sizeof(background_t));
    memset(game->tex->ray_tex, 0, sizeof(game->tex->ray_tex));
    memset(game->tex->item_tex, 0, sizeof(game->tex->item_tex));
    load_ray_textures(game->tex->ray_tex);
    game->font = sfFont_createFromFile("assets/Fonts/Bear_Days.otf");
    if (load_item_textures(game->tex->item_tex) == 84)
        return (84);
    init_player(game);
    game->scene_number = 0;
    game->key_clock = sfClock_create();
    for (int i = 0; i < 3000; i++)
        game->z_buffer[i] = 1e30f;
    init_buttons(game);
    init_menu_bg(game);
    return (0);
}
