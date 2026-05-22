/*
** EPITECH PROJECT, 2026
** items
** File description:
** items init and free
*/

#include "engine.h"
#include "my.h"
#include "wolf3d.h"
#include "ui.h"
#include <SFML/Config.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include <string.h>

sfRectangleShape *init_background(sfTexture *texture)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfVector2f size = {64, 64};
    sfVector2f pos = {0, 0};

    if (!texture || !rect)
        return (NULL);
    sfRectangleShape_setOrigin(rect, (sfVector2f) {size.x / 2, size.y / 2});
    sfRectangleShape_setPosition(rect, pos);
    sfRectangleShape_setTexture(rect, texture, sfFalse);
    sfRectangleShape_setSize(rect, size);
    return rect;
}

item_t *init_item(sfTexture *texture, int uses, char *name,
    void (function) (void *))
{
    item_t *item = malloc(sizeof(item_t));

    if (!item || !texture)
        return NULL;
    item->name = strdup(name);
    item->background = init_background(texture);
    item->sprite = sfSprite_create();
    if (!item->background || !item->sprite)
        return (NULL);
    sfSprite_setTexture(item->sprite, texture, sfFalse);
    item->hovered = false;
    item->on_use = (void *) function;
    item->uses = uses;
    return item;
}
