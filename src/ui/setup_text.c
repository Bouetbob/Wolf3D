/*
** EPITECH PROJECT, 2026
** setup text
** File description:
** text-related functions
*/

#include "engine.h"
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void get_string_from_num(int number, sfText *item)
{
    char *val = NULL;

    asprintf(&val, "%d", number);
    sfText_setString(item, val);
    free(val);
}

sfText *init_text_item(char *string, sfVector2f *position, int size,
    game_t *game)
{
    sfText *item = sfText_create();
    sfFloatRect rect = sfText_getGlobalBounds(item);

    if (!item || !game->font)
        return (NULL);
    sfText_setCharacterSize(item, size);
    sfText_setPosition(item, *position);
    sfText_setString(item, string);
    sfText_setFont(item, game->font);
    sfText_setOrigin(item, (sfVector2f) {rect.height / 2, rect.width / 2});
    return item;
}
