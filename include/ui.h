/*
** EPITECH PROJECT, 2026
** buttons
** File description:
** button file
*/

#include "my.h"
#include "engine.h"
#include <SFML/Graphics.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/PrimitiveType.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/System.h>
#include <SFML/System/Time.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window.h>
#include <SFML/Window/Event.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef UI_H_
    #define UI_H_

button_t *init_button(char *string, sfVector2f *position, sfVector2f *size);
void draw_button(game_t *game, button_t *button);


#endif /* !UI_H_ */
