#ifndef UI_H
#define UI_H

/*
 * The five different UI states.
 */
#define UI_TITLE            1
#define UI_GAME_SOLDIER     2
#define UI_GAME_DIRECTION   3
#define UI_GAME_STRENGTH    4
#define UI_SCOREBOARD       5

/*
 * Entry point to the user interface main loop.
 */
void ui_run(void);

/*
 * The three functions implementing the UI states.
 */
void ui_state_title(void);
void ui_state_game(void);
void ui_state_scoreboard(void);

#endif
