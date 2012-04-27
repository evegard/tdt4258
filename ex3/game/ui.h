#ifndef UI_H
#define UI_H

#define UI_TITLE            1
#define UI_GAME_SOLDIER     2
#define UI_GAME_DIRECTION   3
#define UI_GAME_STRENGTH    4
#define UI_SCOREBOARD       5

void ui_run(void);

void ui_state_title(void);
void ui_state_game(void);
void ui_state_scoreboard(void);

#endif
