/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** wolf3d's .h file
*/

#include "my.h"
#include "wolf3d.h"
#include <SFML/Graphics.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/PrimitiveType.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/System.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window.h>
#include <SFML/Window/Event.h>
#include <stdbool.h>
#include <unistd.h>

#ifndef MAP_H_
    #define MAP_H_

int load_map_from_file(game_t *game, char *file);

#endif /* !map_h_ */
