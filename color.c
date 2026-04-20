/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** color file
*/

#include "my.h"
#include "wolf3d.h"

sfColor fade_color(sfColor *color, float distance)
{
    float intensity = 1.0 - (distance / SHADOW_EFFECT_DIST);

    if (intensity < 0.0)
        intensity = 0.0;
    if (intensity > 1.0)
        intensity = 1.0;
    color->r = (sfUint8) (color->r * intensity);
    color->g = (sfUint8) (color->g * intensity);
    color->b = (sfUint8) (color->b * intensity);
    return *color;
}

sfColor change_color(sfColor *color)
{
    color->r /= 2;
    color->g /= 2;
    color->b /= 2;
    return *color;
}

sfColor get_wall_color(int tile)
{
    switch (tile) {
        case 1:
            return sfColor_fromRGB(255, 0, 0);
        case 2:
            return sfColor_fromRGB(0, 255, 0);
        case 3:
            return sfColor_fromRGB(0, 0, 255);
        case 4:
            return sfColor_fromRGB(255, 255, 0);
        case 5:
            return sfColor_fromRGB(0, 255, 255);
        case 6:
            return sfColor_fromRGB(255, 0, 255);
        case 7:
            return sfColor_fromRGB(255, 128, 0);
        case 8:
            return sfColor_fromRGB(128, 128, 128);
        default:
            return sfWhite;
    }
}

float get_abs_diff(float diff)
{
    float abs_diff;

    while (diff > M_PI)
        diff -= 2 * M_PI;
    while (diff < -M_PI)
        diff += 2 * M_PI;
    abs_diff = fabs(diff);
    return abs_diff;
}

sfColor apply_flashlight(sfColor *color, float ray_angle, float player_rads,
    float distance)
{
    float diff = ray_angle - player_rads;
    float cone = FLASHLIGHT_RADIUS / 2.0;
    float abs_diff;
    float intensity;
    float dist_intensity;

    abs_diff = get_abs_diff(diff);
    if (abs_diff >= cone)
        return (sfColor) {0, 0, 0, 255};
    intensity = 1.0 - (abs_diff / cone);
    intensity *= intensity;
    dist_intensity = 1.0 - (distance / (SHADOW_EFFECT_DIST * 0.6));
    if (dist_intensity < 0.0)
        dist_intensity = 0.0;
    intensity *= dist_intensity;
    color->r = (sfUint8) (color->r * intensity);
    color->g = (sfUint8) (color->g * intensity);
    color->b = (sfUint8) (color->b * intensity);
    return *color;
}
