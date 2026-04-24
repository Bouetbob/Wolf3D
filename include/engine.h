/*
** EPITECH PROJECT, 2026
** engine
** File description:
** engine
*/

#ifndef ENGINE_H_
    #define ENGINE_H_

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
    #include <SFML/Window/Types.h>
    #include <stdbool.h>


    #define FORMER_FOV (M_PI / 3)
    #define NUM_RAYS 800
    #define SHADOW_EFFECT_DIST 8
    #define NUM_TEXTURES 10
    #define M_PI 3.14159265358979323846
    #define FLASHLIGHT_RADIUS (M_PI / 1)
    #define SCREEN_W 800
    #define SCREEN_H 600
    #define UNUSED [[maybe_unused]]
    #define MOVESPEED 2
    #define ROTATESPEED 90
    #define AUTHORIZED_CHARS "0123456789"




typedef struct buttons_s {
    sfRectangleShape *background;
    sfText *text;
    sfVector2f scale;
    sfVector2f original_scale;
    unsigned int char_size;
    bool hovered;
    void (*on_click)(void *);
    bool is_menu_button;
} button_t;

typedef struct item_s {
    char *name;
    sfSprite *sprite;
    sfVector2f *position;
} item_t;

typedef struct stats_s {
    int health;
    bool flashlight;
    int move_speed;
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
    float proj_plane;
} ray_t;

typedef struct quad_params_s {
    sfColor color;
    sfVector2u tex_size;
    float tex_x;
    float y_start;
    float y_end;
    float proj_plane;
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
    sfVector2i mouse_pos;
    sfVector2i map_size;
    sfEvent event;
    sfClock *key_clock;
    timers_t *timer;
    button_t **buttons;
    char **map;
    bool is_menu_open;
} game_t;

int map_filler(game_t *game, char *filename);


#endif /* !ENGINE_H_ */
