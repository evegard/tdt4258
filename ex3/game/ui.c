#include <math.h>

#include "ui.h"
#include "image.h"
#include "screen.h"
#include "led.h"
#include "button.h"
#include "sound.h"
#include "scorched_land.h"

#ifndef MIN
#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#endif

int ui_state = UI_TITLE;

game_direction_t ui_player_direction = GAME_EAST;

image_t *img_bg, *img_soldier, *img_tank, *img_grass, *img_dirt;

#define UI_TILE_WIDTH   20
#define UI_TILE_HEIGHT  20

void ui_run(void)
{
    img_bg = image_load("images/tittel.tga");
    img_soldier = image_load("images/soldat.tga");
    img_tank = image_load("images/tanks.tga");
    img_grass = image_load("images/gress.tga");
    img_dirt = image_load("images/brent.tga");

    while (1)
    {
        switch (ui_state)
        {
            case UI_GAME_SOLDIER:
            case UI_GAME_DIRECTION:
            case UI_GAME_STRENGTH:
                ui_state_game(); break;

            //case UI_SCOREBOARD: ui_state_scoreboard(); break;

            default:
            case UI_TITLE:      ui_state_title(); break;
        }
    }
}

void ui_state_title(void)
{
    int x = 0, y = 0, dx = 1, dy = 1, w = 20, h = 20, i = 0;

    snd_play("sounds/intro-valkyrie.raw");

    while (1) {
        image_draw(0, 0, img_bg);
        image_draw(x, y, img_soldier);
        screen_show_buffer();

        if (y + h == SCREEN_HEIGHT && dy == 1) dy = -1;
        if (y == 0 && dy == -1) dy = 1;
        if (x + w == SCREEN_WIDTH && dx == 1) dx = -1;
        if (x == 0 && dx == -1) dx = 1;
        x += dx; y += dy;

        led_setup = (i++ / 10) % 2 ? 0xaa : 0x55;
        led_update();

        if (btn_read() > 0) {
            ui_state = UI_GAME_SOLDIER;
            game_init();
            return;
        }
    }
}

void ui_state_game(void)
{
    int i, x, y, y_off, go_x, go_y, result;
    int tank_direction, tank_strength, meter_direction;
    double radians;
    game_position_t result_pos;
    image_t *tile;

    y_off = SCREEN_HEIGHT - GAME_HEIGHT * UI_TILE_HEIGHT;

    led_clear();
    for (i = 0; i < game_soldier_score; i++)
        led_set(7 - i, 1);
    for (i = 0; i < game_tank_score; i++)
        led_set(i, 1);

    if (game_soldier_score >= 4 || game_tank_score >= 4) {
        ui_state = UI_SCOREBOARD;
        return;
    }

    game_reset();

    while (1) {
        screen_clear(color_black);
        for (x = 0; x < GAME_WIDTH; x++)
            for (y = 0; y < GAME_HEIGHT; y++) {
                tile = game_is_scorched[y][x] ? img_dirt : img_grass;
                image_draw(x * UI_TILE_WIDTH, y * UI_TILE_HEIGHT + y_off, tile);
            }

        go_x = game_player.x; go_y = game_player.y;
        switch (ui_player_direction) {
            case GAME_NORTH: go_y--; break;
            case GAME_SOUTH: go_y++; break;
            case GAME_WEST: go_x--; break;
            case GAME_EAST: go_x++; break;
        }

        switch (ui_state) {
            case UI_GAME_SOLDIER:
                if (go_x >= 0 && go_x < GAME_WIDTH &&
                    go_y >= 0 && go_y < GAME_HEIGHT) {
                    screen_rectangle(
                        go_x * UI_TILE_WIDTH,
                        go_y * UI_TILE_HEIGHT + y_off,
                        UI_TILE_WIDTH,
                        UI_TILE_HEIGHT,
                        color_blue);
                }

                if (btn_is_pushed(7)) {
                    result = game_move_player(ui_player_direction);
                    if (result == GAME_MOVE_TANK)
                        return;
                    if (result == GAME_MOVE_OK) {
                        tank_direction = 0;
                        meter_direction = 5;
                        ui_state = UI_GAME_DIRECTION;
                    }
                }

                if (btn_is_pushed(6)) {
                    ui_player_direction = ++ui_player_direction % 4;
                }

                break;

            case UI_GAME_DIRECTION:
                radians = tank_direction * M_PI / 180;
                x = SCREEN_WIDTH - UI_TILE_WIDTH / 2;
                y = y_off + UI_TILE_HEIGHT / 2;
                go_x = -(int)(cos(radians) * UI_TILE_WIDTH * 3);
                go_y =  (int)(sin(radians) * UI_TILE_HEIGHT * 3);
                screen_line(x, y, x + go_x, y + go_y, color_red);
                if (tank_direction >= GAME_MAX_DIRECTION)
                    meter_direction = -5;
                if (tank_direction <= 0)
                    meter_direction = 5;
                tank_direction += meter_direction;
                tank_direction = MAX(0, MIN(GAME_MAX_DIRECTION, tank_direction));

                if (btn_is_pushed(0)) {
                    tank_strength = 40;
                    meter_direction = 20;
                    ui_state = UI_GAME_STRENGTH;
                }

                break;

            case UI_GAME_STRENGTH:
                radians = tank_direction * M_PI / 180;
                x = SCREEN_WIDTH - UI_TILE_WIDTH / 2;
                y = y_off + UI_TILE_HEIGHT / 2;
                go_x = -(int)(cos(radians) * UI_TILE_WIDTH * 3);
                go_y =  (int)(sin(radians) * UI_TILE_HEIGHT * 3);
                screen_line(x, y, x + go_x, y + go_y, color_red);
                screen_fill_rectangle(
                    SCREEN_WIDTH - UI_TILE_WIDTH / 2 -
                        tank_strength * (SCREEN_WIDTH - UI_TILE_WIDTH) / GAME_MAX_STRENGTH,
                    UI_TILE_HEIGHT / 2,
                    tank_strength * (SCREEN_WIDTH - UI_TILE_WIDTH) / GAME_MAX_STRENGTH,
                    UI_TILE_HEIGHT,
                    color_red);
                if (tank_strength >= GAME_MAX_STRENGTH)
                    meter_direction = -20;
                if (tank_strength <= 40)
                    meter_direction = 20;
                tank_strength += meter_direction;
                tank_strength = MAX(40, MIN(GAME_MAX_STRENGTH, tank_strength));

                if (btn_is_pushed(0)) {
                    result_pos = game_shoot_bullet(tank_direction, tank_strength);
                    ui_state = UI_GAME_SOLDIER;
                    if (result_pos.x < 0 && result_pos.y < 0)
                        return;
                }

                break;
        }

        image_draw(
            (GAME_WIDTH - 2) * UI_TILE_WIDTH,
            y_off,
            img_tank);
        image_draw(
            game_player.x * UI_TILE_WIDTH,
            game_player.y * UI_TILE_HEIGHT + y_off,
            img_soldier);

        screen_show_buffer();
    }
}
