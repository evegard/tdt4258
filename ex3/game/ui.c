#include "ui.h"
#include "image.h"
#include "screen.h"
#include "led.h"
#include "button.h"
#include "sound.h"
#include "scorched_land.h"

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
            case UI_GAME:       ui_state_game(); break;
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
            ui_state = UI_GAME;
            game_init();
            return;
        }
    }
}

void ui_state_game(void)
{
    int i, x, y, y_off, go_x, go_y, result;
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

        image_draw(
            (GAME_WIDTH - 2) * UI_TILE_WIDTH,
            y_off,
            img_tank);
        image_draw(
            game_player.x * UI_TILE_WIDTH,
            game_player.y * UI_TILE_HEIGHT + y_off,
            img_soldier);
        if (go_x >= 0 && go_x < GAME_WIDTH &&
            go_y >= 0 && go_y < GAME_HEIGHT) {
            screen_rectangle(
                go_x * UI_TILE_WIDTH,
                go_y * UI_TILE_HEIGHT + y_off,
                UI_TILE_WIDTH,
                UI_TILE_HEIGHT,
                color_blue);
        }

        screen_show_buffer();

        if (btn_is_pushed(6))
            ui_player_direction = ++ui_player_direction % 4;
        if (btn_is_pushed(7)) {
            result = game_move_player(ui_player_direction);
            if (result == GAME_MOVE_TANK)
                return;
        }
    }
}
