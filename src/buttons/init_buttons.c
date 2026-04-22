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

static sfText *init_button_text(char *text, int charsize,
    sfVector2f *pos, sfVector2f *rectsize)
{
    sfText *textbox = sfText_create();
    sfFont *font = sfFont_createFromFile("assets/Fonts/Bear_Days.otf");

    if (!textbox || !font)
        return (NULL);
    sfText_setOrigin(textbox,
        (sfVector2f) {rectsize->x / 3, rectsize->y / 3});
    sfText_setCharacterSize(textbox, charsize);
    sfText_setString(textbox, text);
    sfText_setFont(textbox, font);
    sfText_setPosition(textbox, *pos);
    sfText_setColor(textbox, sfBlack);
    return textbox;
}

button_t *init_button(char *string, sfVector2f *position, sfVector2f *size)
{
    button_t *button = malloc(sizeof(button_t));

    if (!button)
        return NULL;
    button->background = init_button_background(position, size);
    if (!button->background)
        return (NULL);
    button->char_size = 10;
    button->hovered = false;
    button->scale = (sfVector2f) {1, 1};
    button->text = init_button_text(string, button->char_size, position, size);
    if (!button->text)
        return (NULL);
    button->on_click = (NULL);
    button->is_menu_button = false;
    return button;
}
