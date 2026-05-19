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
    #define SHADOW_EFFECT_DIST 20
    #define NUM_TEXTURES_RAY 10
    #define M_PI 3.14159265358979323846
    #define FLASHLIGHT_RADIUS (M_PI / 1)
    #define SCREEN_W 1200
    #define SCREEN_H 800
    #define UNUSED [[maybe_unused]]
    #define MOVESPEED 2
    #define ROTATESPEED 90
    #define AUTHORIZED_CHARS "0123456789PBMT"
    #define INVENTORY_SIZE 25
    #define NUM_TEXTURES_ITEMS 4
    #define MAX_ENEMIES 64
    #define TEX_FLOOR 2
    #define TEX_CEIL 2



typedef struct buttons_s {
    sfRectangleShape *background;
    sfText *text;
    unsigned int char_size;
    bool hovered;
    void (*on_click)(void *);
    bool is_menu_button;
} button_t;

typedef struct item_s {
    char *name;
    sfSprite *sprite;
    sfRectangleShape *background;
    int uses;
    bool hovered;
    void (*on_use)(void *);
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

typedef struct ray_data_s {
    float rdx0;
    float rdy0;
    float rdx1;
    float rdy1;
    float half_proj;
} ray_data_t;

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
    sfRectangleShape *ui_bar;
    float rads;
    sfVector2f dir_v;
    item_t **inventory;
    stats_t *stats;
    float FOV;
} player_t;

typedef struct timers_s {
    float oldtime;
    float currenttime;
    sfTime time;
    float timeframe;
} timers_t;

typedef struct textures_s {
    sfTexture *ray_tex[NUM_TEXTURES_RAY];
    sfTexture *item_tex[NUM_TEXTURES_ITEMS];
} textures_t;

typedef struct game_s {
    sfImage *floor_image;
    sfTexture *floor_render_tex;
    sfSprite *floor_sprite;
    sfImage *floor_tex_img;
    sfImage *ceil_tex_img;
    player_t *player;
    sfSprite *bomb_sprite;
    textures_t *tex;
    sfRenderWindow *window;
    sfVector2i win_s;
    sfVector2i mouse_pos;
    sfVector2i map_size;
    sfEvent event;
    sfClock *key_clock;
    timers_t *timer;
    button_t **buttons;
    char **map;
    char *file_name;
    bool is_menu_open;
    bool is_inv_open;
    struct enemy_s **enemies;
    int enemy_count;
    float z_buffer[SCREEN_W];
    sfTexture *enemy_texture;
    ray_data_t *ray_data;
} game_t;

void init_floor_ceiling(game_t *game);
void render_floor_ceiling(game_t *game);

#endif /* !ENGINE_H_ */
