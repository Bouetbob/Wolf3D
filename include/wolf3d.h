/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** wolf3d's .h file
*/

#include "engine.h"
#include "my.h"
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
#include "ui.h"
#include <stdbool.h>
#include <unistd.h>

#ifndef WOLF3D_H_
    #define WOLF3D_H_

//color

sfColor fade_color(sfColor *color, float distance);
sfColor change_color(sfColor *color);
sfColor get_wall_color(int tile);
sfColor apply_flashlight(sfColor *color, float ray_angle, float player_rads,
    float distance);

//init_game

void setup_time(game_t *game);
int init_all(game_t *game);
int load_window(game_t *game);
void free_ressource(game_t *game, ray_t *ray,
    sfVertexArray *vertexarr[NUM_TEXTURES_RAY]);
void check_exit_conditions(game_t *game, ray_t *ray, char **env);

//main

sfRenderWindow *create_window(int width, int heigth, char *name);
void main_game_loop(game_t *game, ray_t *ray);

//movement

void handle_movement(player_t *player, game_t *game);

//raycasting

void get_ray_distance(ray_t *ray, player_t *player, game_t *game);
void render_raycast(game_t *game, ray_t *ray, sfVertexArray **vertexarr);
int is_wall(float x, float y, game_t *game);

//utils

bool has_display(char **env);
void exit_with_message(char *exit_message, int message_channel,
    int exit_value);
void dir_giver(player_t *player);
void rad_giver(player_t *player);
void update_player(player_t *player);

//map

int get_number_value(char *string);
int check_size_validity(char *content, game_t *game);
int check_map_validity(char *cont, game_t *game);

#endif /* !WOLF3D_H_ */
