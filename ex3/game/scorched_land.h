#ifndef SCORCHED_LAND
#define SCORCHED_LAND

#define GAME_WIDTH 10
#define GAME_HEIGHT 10
/* 
 * These values should only be read, not modified. To scorch a piece of
 * land, use game_shoot_bullet with the proper parameters.
 */
char game_is_scorched[GAME_HEIGHT][GAME_WIDTH];

/*
 * Enum which contains different directions the soldier can move.
 */
typedef enum {
    GAME_NORTH, GAME_SOUTH, GAME_WEST, GAME_EAST
} game_direction_t;


/*
 * Struct which contains the x and y coordinates of a tile.
 */
typedef struct {
    int x;
    int y;
} game_position_t;


/*
 * These values should only be read, not modified. To move a player, use
 * the function game_move_player with the proper parameters.
 */
game_position_t game_player;


/* 
 * Initialize/reset the game. Will destroy the current state of the
 * game and return the game to the start condition.
 */
void game_init ( void );

/*
 * Shoots a bullet with direction and strength given as input. Returns
 * the tile which was hit, or {-1, -1} if the tile is out of bounds.
 * Will return {-2, -2} if the direction or strength is out of the legal
 * range.
 */
game_position_t game_shoot_bullet ( int direction, int strength );

/* 
 * Move the player in the direction given as parameter. Returns 0 if the
 * move is successful, -1 if the tile the player wants to move to is
 * scorched, -2 if the tile is out of bounds, and 1 if the tile we're
 * moving to is the tank. Will only change the player's position if the
 * move is successful (i.e. the function return 0).
 */
int game_move_player ( game_direction_t dir );

#endif
