/*
** EPITECH PROJECT, 2026
** engine
** File description:
** engine
*/

#ifndef ENGINE_H_
    #define ENGINE_H_

    #include "enemy.h"
    #include <SFML/Audio/Types.h>
    #include <SFML/Graphics.h>
    #include <SFML/Graphics/Color.h>
    #include <SFML/Graphics/PrimitiveType.h>
    #include <SFML/Graphics/Rect.h>
    #include <SFML/Graphics/RectangleShape.h>
    #include <SFML/Graphics/RenderWindow.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/Graphics/VertexArray.h>
    #include <SFML/System.h>
    #include <SFML/Audio.h>
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
    #define TEX_FLOOR 5
    #define TEX_CEIL 2

    #define MINI_TILE 5
    #define MINI_PADDING 1
    #define MINI_TILE_BASE 6

    #define SETTINGS 3
    #define INVENTORY 2
    #define MENU 1
    #define GAME 0

typedef struct buttons_s {
    sfRectangleShape *background;
    sfText *text;
    unsigned int char_size;
    bool hovered;
    void (*on_click)(void *);
    int is_menu_button;
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

typedef struct weapon_s {
    sfSprite *sprite;
    int damage;
    float rate;
    int ammo;
    sfSound *shoot;
    sfSoundBuffer *buff;
    int max_ammo;
    sfIntRect rect;
    float frame_time;
    int frame;
    float time_until_switch;
} weapon_t;

typedef struct player_s {
    sfVector2f pos;
    float angle;
    sfRectangleShape *ui_bar;
    float rads;
    sfText **ui_texts;
    sfVector2f dir_v;
    item_t **inventory;
    stats_t *stats;
    weapon_t **weapons;
    int curr_weapon;
    float FOV;
    int score;
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

typedef struct background_s {
    sfImage *floor_image;
    sfTexture *floor_render_tex;
    sfSprite *floor_sprite;
    sfImage *floor_tex_img;
    sfImage *ceil_tex_img;
} background_t;

typedef struct minimap_s {
    sfRenderTexture *minimap_tex;
    sfSprite *minimap_sprite;
    sfCircleShape *player_dot;
    sfRectangleShape *tile;
    bool need_map_render;
} minimap_t;

typedef struct floor_context_s {
    sfUint8 *out;
    const sfUint8 *ftex;
    const sfUint8 *ctex;
    sfVector2u ftex_s;
    sfVector2u ctex_s;
    int win_w;
    int win_h;
} floor_context_t;

typedef struct game_s {
    background_t *background;
    player_t *player;
    minimap_t *minimap;
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
    int scene_number;
    enemy_t **enemies;
    int enemy_count;
    float z_buffer[3000];
    sfTexture *enemy_texture;
    ray_data_t *ray_data;
    sfFont *font;
    sfSprite *menu_bg;
} game_t;

void init_background_and_minimap(game_t *game);
void render_floor_ceiling(game_t *game);
void init_minimap(game_t *game);
void render_minimap(game_t *game);
void clean_mini_map(game_t *game);
void resize_floor_ceiling(game_t *game);

void update_enemies(game_t *game);
bool has_line_of_sight(enemy_t *enemy, player_t *player, game_t *game);
void shoot_player(player_t *player, enemy_t *enemy, game_t *game);
void render_enemies(game_t *game);

void free_buttons(game_t *game);
void free_weapons(player_t *player);
void clean_player(player_t *player);
void init_ui_texts(game_t *game);
void init_player(game_t *game);

#endif /* !ENGINE_H_ */
