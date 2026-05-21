/*
** EPITECH PROJECT, 2026
** init_single_weapon
** File description:
** it inits one weapon
*/


#include "engine.h"
#include <SFML/Config.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <stdlib.h>
#include <time.h>

static void setup_weapon_stats(weapon_t *weapon, int ammo, int damage, int rate)
{
    weapon->ammo = ammo;
    weapon->max_ammo = ammo;
    weapon->damage = damage;
    weapon->rate = rate;
}

static void setup_weapon_anim(weapon_t *weapon, sfSprite *sprite)
{
    weapon->sprite = sprite;
    weapon->rect.height = 128;
    weapon->rect.width = 128;
    weapon->rect.left = 0;
    weapon->rect.top = 0;
    weapon->frame = 0;
    weapon->frame_time = 0.1f;
    weapon->time_until_switch = weapon->frame_time;
}

weapon_t *init_single_weapon(int ammo, int damage, float rate, char *s_path)
{
    weapon_t *weapon = malloc(sizeof(weapon_t));
    sfSprite *sprite = sfSprite_create();
    sfTexture *tex = sfTexture_createFromFile(s_path, NULL);

    if (!weapon || !sprite || !tex)
        return NULL;
    sfSprite_setTexture(sprite, tex, sfFalse);
    sfSprite_setPosition(sprite,
        (sfVector2f) {(float) SCREEN_W / 2 - 156, SCREEN_H - 256});
    sfSprite_setScale(sprite, (sfVector2f) {2, 2});
    setup_weapon_stats(weapon, ammo, damage, rate);
    setup_weapon_anim(weapon, sprite);
    sfSprite_setTextureRect(sprite, weapon->rect);
    return weapon;
}

void init_weapons(game_t *game)
{
    player_t *p = game->player;

    p->curr_weapon = 0;
    p->score = 0;
    p->weapons[0] =
        init_single_weapon(30, 10, 0.15, "./assets/UI/gun.png");
    p->weapons[1] = NULL;
    p->weapons[2] = NULL;
}
