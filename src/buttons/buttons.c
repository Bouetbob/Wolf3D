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
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>

sfRectangleShape *init_button_background(sfVector2f pos)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfTexture *texture = sfTexture_createFromFile("assets/button.png", NULL)

    sfRectangleShape_setPosition(rect, pos);
    sfRectangleShape_setTexture(rect, texture, sfFalse);
    return rect;
}

sfText *init_button_text(char *text, int charsize)
{
    sfText *textbox = sfText_create();

    sfText_setCharacterSize(textbox, charsize);
    sfText_setString(textbox, text);
    return textbox;
}

button_t *init_button(sfVector2f scale, char *string, sfVector2f position)
{
    button_t *button = malloc(sizeof(button_t));

    button->background = init_button_background(position);
    button->char_size = 10;
    button->hovered = false;
    button->scale = (sfVector2f) {1, 1};
    button->text = init_button_text(string, button->char_size);
    button->on_click = NULL;
}