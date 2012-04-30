#include <math.h>
#include <stdlib.h>

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
int ui_play_point_sound = 1;

image_t *img_bg, *img_soldier, *img_tank, *img_grass, *img_dirt,
        *img_soldier_win, *img_tank_win;

#define UI_MAX_POINTS   2

#define UI_TILE_WIDTH   20
#define UI_TILE_HEIGHT  20
#define UI_Y_OFFSET     (SCREEN_HEIGHT - GAME_HEIGHT * UI_TILE_HEIGHT)

#define UI_DIRECTION_SPEED  5
#define UI_STRENGTH_SPEED   40

void ui_run(void)
{
    img_bg = image_load("images/tittel.tga");
    img_soldier = image_load("images/soldat.tga");
    img_tank = image_load("images/tanks.tga");
    img_grass = image_load("images/gress.tga");
    img_dirt = image_load("images/brent.tga");
    img_soldier_win = image_load("images/gameover-soldier.tga");
    img_tank_win = image_load("images/gameover-tank.tga");

    while (1)
    {
        switch (ui_state)
        {
            case UI_GAME_SOLDIER:
            case UI_GAME_DIRECTION:
            case UI_GAME_STRENGTH:
                ui_state_game(); break;

            case UI_SCOREBOARD: ui_state_scoreboard(); break;

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

        if ((btn_ignore = btn_read()) > 0) {
            ui_state = UI_GAME_SOLDIER;
            game_init();
            return;
        }
    }
}

void ui_state_game(void)
{
    int i, x, y, go_x, go_y, result;
    int aimline_x1 = SCREEN_WIDTH - UI_TILE_WIDTH / 2,
        aimline_y1 = UI_Y_OFFSET + UI_TILE_HEIGHT / 2,
        aimline_x2, aimline_y2, strengthbar_width;
    int play_explosion = 0;
    int tank_direction, tank_strength, meter_direction;
    double radians;
    game_position_t result_pos;
    image_t *tile;

    led_clear();
    for (i = 0; i < game_soldier_score; i++)
        led_set(7 - i, 1);
    for (i = 0; i < game_tank_score; i++)
        led_set(i, 1);

    if (game_soldier_score >= UI_MAX_POINTS ||
        game_tank_score >= UI_MAX_POINTS) {
        ui_state = UI_SCOREBOARD;
        return;
    }

    game_reset();

    while (1) {
        screen_clear(color_black);
        for (x = 0; x < GAME_WIDTH; x++)
            for (y = 0; y < GAME_HEIGHT; y++) {
                tile = game_is_scorched[y][x] ? img_dirt : img_grass;
                image_draw(x * UI_TILE_WIDTH, y * UI_TILE_HEIGHT + UI_Y_OFFSET, tile);
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
                        go_y * UI_TILE_HEIGHT + UI_Y_OFFSET,
                        UI_TILE_WIDTH,
                        UI_TILE_HEIGHT,
                        color_blue);
                }

                if (ui_play_point_sound)
                    snd_play("sounds/point.raw");
                else if (play_explosion)
                    snd_play("sounds/eksplosjon.raw");
                ui_play_point_sound = 0;
                play_explosion = 0;

                if (btn_is_pushed(7)) {
                    result = game_move_player(ui_player_direction);
                    if (result == GAME_MOVE_TANK) {
                        ui_play_point_sound = 1;
                        return;
                    }
                    if (result == GAME_MOVE_OK) {
                        tank_direction = GAME_MIN_DIRECTION;
                        meter_direction = UI_DIRECTION_SPEED;
                        ui_state = UI_GAME_DIRECTION;
                    }
                }

                if (btn_is_pushed(6)) {
                    ui_player_direction = ((int)ui_player_direction + 1) % 4;
                }

                break;

            case UI_GAME_DIRECTION:
                if (btn_is_pushed(0)) {
                    tank_strength = GAME_MIN_STRENGTH;
                    meter_direction = UI_STRENGTH_SPEED;
                    ui_state = UI_GAME_STRENGTH;
                    break;
                }

                radians = tank_direction * M_PI / 180;
                aimline_x2 = aimline_x1 - (int)(cos(radians) * UI_TILE_WIDTH * 3);
                aimline_y2 = aimline_y1 + (int)(sin(radians) * UI_TILE_HEIGHT * 3);
                screen_line(aimline_x1, aimline_y1, aimline_x2, aimline_y2, color_red);

                if (tank_direction >= GAME_MAX_DIRECTION)
                    meter_direction = -UI_DIRECTION_SPEED;
                if (tank_direction <= GAME_MIN_DIRECTION)
                    meter_direction = UI_DIRECTION_SPEED;
                tank_direction += meter_direction;
                tank_direction = MAX(GAME_MIN_DIRECTION, tank_direction);
                tank_direction = MIN(GAME_MAX_DIRECTION, tank_direction);

                break;

            case UI_GAME_STRENGTH:
                if (btn_is_pushed(0)) {
                    snd_play_wait("sounds/skyte.raw");
                    result_pos = game_shoot_bullet(tank_direction, tank_strength);
                    ui_state = UI_GAME_SOLDIER;
                    play_explosion = !game_position_equals(result_pos,
                        GAME_SHOT_OOB);
                    if (result_pos.x < 0 && result_pos.y < 0) {
                        ui_play_point_sound = 1;
                        return;
                    }
                    break;
                }

                screen_line(aimline_x1, aimline_y1, aimline_x2, aimline_y2, color_red);
                strengthbar_width = tank_strength *
                    (SCREEN_WIDTH - UI_TILE_WIDTH) / GAME_MAX_STRENGTH;
                screen_fill_rectangle(
                    SCREEN_WIDTH - UI_TILE_WIDTH / 2 - strengthbar_width,
                    UI_TILE_HEIGHT / 2,
                    strengthbar_width,
                    UI_TILE_HEIGHT,
                    color_red);

                if (tank_strength >= GAME_MAX_STRENGTH)
                    meter_direction = -UI_STRENGTH_SPEED;
                if (tank_strength <= GAME_MIN_STRENGTH)
                    meter_direction = UI_STRENGTH_SPEED;
                tank_strength += meter_direction;
                tank_strength = MAX(GAME_MIN_STRENGTH, tank_strength);
                tank_strength = MIN(GAME_MAX_STRENGTH, tank_strength);

                break;
        }

        image_draw(
            (GAME_WIDTH - 2) * UI_TILE_WIDTH,
            UI_Y_OFFSET,
            img_tank);
        image_draw(
            game_player.x * UI_TILE_WIDTH,
            game_player.y * UI_TILE_HEIGHT + UI_Y_OFFSET,
            img_soldier);

        screen_show_buffer();
    }
}

void ui_state_scoreboard(void)
{
    volatile int i;
    int x, y, dx, dy, w, h;
    image_t *bg, *sprite;

    ui_state = UI_TITLE;

    if (game_soldier_score == UI_MAX_POINTS) {
        bg = img_soldier_win;
        sprite = img_tank;
    } else {
        bg = img_tank_win;
        sprite = img_soldier;
    }

    w = sprite->width;
    h = sprite->height;

    snd_play_wait("sounds/point.raw");
    image_draw(0, 0, bg);

    x = rand() % 9 + 1; y = 0;
    dx = rand() % 3 + 1; dy = 1;

    while (1) {
        image_draw(x, y, sprite);
        screen_show_buffer();

        if (y + h == SCREEN_HEIGHT && dy >= 0) dy *= -0.8;
        if (x + w == SCREEN_WIDTH || x == 0) {
            x = rand() % 9 + 1; y = 0;
            dx = rand() % 3 + 1; dy = 1;
            if (rand() % 2) {
                x = SCREEN_WIDTH - w - x;
                dx *= -1;
            }
        }
        x += dx; x = MIN(x, SCREEN_WIDTH - w); x = MAX(x, 0);
        y += dy; y = MIN(y, SCREEN_HEIGHT - h);
        dy += 1;

        for (i = 0; i < 1000000; i++);

        if ((btn_ignore = btn_read()) > 0)
            return;
    }
}
