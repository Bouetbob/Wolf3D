/*
** EPITECH PROJECT, 2026
** wolf3d
** File description:
** wolf3d's .h file
*/

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
#include <stdbool.h>
#include <unistd.h>

#ifndef WOLF3D_H_
    #define WOLF3D_H_

    #define FORMER_FOV (M_PI / 3)
    #define NUM_RAYS 800
    #define SHADOW_EFFECT_DIST 8
    #define NUM_TEXTURES 12
    #define M_PI 3.14159265358979323846
    #define FLASHLIGHT_RADIUS (M_PI / 1)
    #define SCREEN_W 800
    #define SCREEN_H 600
    #define MAP_WIDTH 24
    #define MAP_HEIGHT 24
    #define UNUSED [[maybe_unused]]
    #define MOVESPEED 2
    #define ROTATESPEED 90

typedef struct item_s {
    char *name;
    sfSprite *sprite;
    sfVector2f *position;
} item_t;

typedef struct stats_s {
    int health;
    bool flashlight;
} stats_t;

typedef struct ray_s {
    sfVector2f side_dist;
    sfVector2f delta_dist;
    sfVector2f ray_direction;
    sfVector2f step;
    int side;
    float distance;
    int hit_tile;
    float wall_x;
    float current_angle;
} ray_t;

typedef struct quad_params_s {
    sfColor color;
    sfVector2u tex_size;
    float tex_x;
    float y_start;
    float y_end;
} quad_params_t;

typedef struct player_s {
    sfVector2f pos;
    float angle;
    float rads;
    sfVector2f direction_vec;
    stats_t *stats;
    float FOV;
} player_t;

typedef struct timers_s {
    float oldtime;
    float currenttime;
    sfTime time;
    float timeframe;
} timers_t;

typedef struct game_s {
    player_t *player;
    sfTexture *textures[NUM_TEXTURES];
    sfRenderWindow *window;
    sfEvent event;
    sfClock *key_clock;
    timers_t *timer;
} game_t;

//color

sfColor fade_color(sfColor *color, float distance);
sfColor change_color(sfColor *color);
sfColor get_wall_color(int tile);
sfColor apply_flashlight(sfColor *color, float ray_angle, float player_rads,
    float distance);

//init_game

void setup_time(game_t *game);
int init_all(game_t *game);
void free_ressource(game_t *game, ray_t *ray,
    sfVertexArray *vertexarr[NUM_TEXTURES]);
void check_exit_conditions(game_t *game, ray_t *ray, char **env);

//main

sfRenderWindow *create_window(int width, int heigth, char *name);
void analyse_events(sfRenderWindow *window, sfEvent event);
void main_game_loop(game_t *game, ray_t *ray,
    sfVertexArray *vertexarr[NUM_TEXTURES]);

//movement

void handle_movement(player_t *player, game_t *game);

//raycasting

void get_ray_distance(ray_t *ray, player_t *player);
void render_raycast(game_t *game, ray_t *ray, sfVertexArray **vertexarr);
int is_wall(float x, float y);

//utils

bool has_display(char **env);
void exit_with_message(char *exit_message, int message_channel,
    int exit_value);
void dir_giver(player_t *player);
void rad_giver(player_t *player);
void update_player(player_t *player);

#endif /* !WOLF3D_H_ */
