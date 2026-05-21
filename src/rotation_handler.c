/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** rotation-related functions
*/

#include <SFML/System/Vector2.h>
#include <math.h>

float angle_calculator(sfVector2f *start, sfVector2f *end)
{
    float len1 = end->x - start->x;
    float len2 = end->y - start->y;
    float angle_deg = atan2(len2, len1) * (180.0 / M_PI);

    return (angle_deg);
}

sfVector2f get_direction(sfVector2f *start, sfVector2f *end)
{
    sfVector2f direction;
    float resx = end->x - start->x;
    float resy = end->y - start->y;
    int signx = 1;
    int signy = 1;

    if (resx < 0) {
        resx = -resx;
        signx *= -1;
    }
    if (resy < 0) {
        resy = -resy;
        signy *= -1;
    }
    direction.x = (resx / (resx + resy) * signx);
    direction.y = (resy / (resx + resy) * signy);
    return (direction);
}
