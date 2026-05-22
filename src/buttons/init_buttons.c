/*
** EPITECH PROJECT, 2026
** buttons
** File description:
** buttons init and free
*/

#include "my.h"
#include "wolf3d.h"
#include "ui.h"
#include <SFML/Config.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>

static sfRectangleShape *init_button_background(sfVector2f *pos,
    sfVector2f *size)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfTexture *texture = sfTexture_createFromFile("assets/UI/button.png", NULL);

    if (!texture || !rect)
        return (NULL);
    sfRectangleShape_setOrigin(rect, (sfVector2f) {size->x / 2, size->y / 2});
    sfRectangleShape_setPosition(rect, *pos);
    sfRectangleShape_setTexture(rect, texture, sfFalse);
    sfRectangleShape_setSize(rect, *size);
    return rect;
}

static sfText *init_button_text(char *text, button_t *button, game_t *game)
{
    sfText *textbox = sfText_create();
    sfVector2f pos = sfRectangleShape_getPosition(button->background);
    sfVector2f sz = sfRectangleShape_getSize(button->background);

    if (!textbox || !game->font)
        return (NULL);
    sfText_setOrigin(textbox, (sfVector2f) {sz.x / 3, sz.y / 3});
    sfText_setCharacterSize(textbox, button->char_size);
    sfText_setString(textbox, text);
    sfText_setFont(textbox, game->font);
    sfText_setPosition(textbox, pos);
    sfText_setColor(textbox, sfBlack);
    return textbox;
}

button_t *init_button(button_params_t *params, game_t *game)
{
    button_t *button = malloc(sizeof(button_t));

    if (!button)
        return NULL;
    button->background =
        init_button_background(params->position, params->size);
    if (!button->background)
        return (NULL);
    button->char_size = 10;
    button->hovered = false;
    button->text = init_button_text(params->string, button, game);
    if (!button->text)
        return (NULL);
    button->on_click = (NULL);
    button->is_menu_button = params->is_menu;
    return button;
}
