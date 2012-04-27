#ifndef SCORCHED_LAND
#define SCORCHED_LAND

#define GAME_WIDTH 16
#define GAME_HEIGHT 10

#define GAME_MAX_DIRECTION 90
#define GAME_MAX_STRENGTH  400

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif
/*
 * This integer contains the number of times the soldier has reached the
 * tank since the last time the game was initialised/reset.
 */
int game_soldier_score;

/*
 * This integer contains the number of times the soldier has been hit
 * and/or has no way of reaching the tank since the last time the game
 * was initialised/reset.
 */
int game_tank_score;

/* 
 * This array should only be read, not modified. To scorch a piece of
 * land, use game_shoot_bullet with the proper parameters.
 */
char game_is_scorched[GAME_HEIGHT][GAME_WIDTH];

/*
 * Enum which contains all the different directions the soldier can
 * move.
 */
typedef enum {
    GAME_NORTH, GAME_SOUTH, GAME_WEST, GAME_EAST
} game_direction_t;


/*
 * Enum which contains the different results from an attempt to move the
 * soldier - such as whether the move is ok, whether it is out of bounds
 * and so forth.
 */
typedef enum {
    GAME_MOVE_OK, GAME_MOVE_IS_SCORCHED, GAME_MOVE_OOB, GAME_MOVE_TANK
} game_move_t;

/*
 * Struct which contains the x and y coordinates of a tile.
 */
typedef struct {
    int x;
    int y;
} game_position_t;

/*
 * Checks whether two game_position_t elements are equal.
 */

char game_position_equals ( game_position_t a, game_position_t b );

/*
 * These values should only be read, not modified. To move a player, use
 * the function game_move_player with the proper parameters.
 */
game_position_t game_player;

/*
 * A constant returned from game_shoot_bullet if the shot is out of
 * bounds.
 */
extern const game_position_t GAME_SHOT_OOB;

/*
 * A constant returned from game_shoot_bullet if the input argument(s)
 * are outside of the valid range.
 */
extern const game_position_t GAME_SHOT_ILLEGAL_ARGUMENT;

/*
 * Initialise the game. Will destroy the current state of the game and
 * return the game to the start condition. Equivalent to calling
 * game_reset and setting the scores to zero.
 */
void game_init ( void );

/*
 * Resets the game, by moving the soldier back to start and removes all
 * the scorched land, but does not remove the score by each player.
 */

void game_reset ( void );

/*
 * Shoots a bullet with direction and strength given as input. Returns
 * the tile which was hit, or GAME_SHOT_OOB if the tile is out of
 * bounds.  Will return GAME_SHOT_ILLEGAL_ARGUMENT if the direction or
 * strength is out of the legal range. If the position is the same as
 * the position the soldier currently is at or it is impossible for the
 * soldier to reach the tank, then this function will return {-x, -y},
 * where x and y are the coordinates to the tile which was hit.  The
 * game_tank_score is then incremented by one.
 */
game_position_t game_shoot_bullet ( int direction, int strength );

/* 
 * Move the player in the direction given as parameter. Returns
 * GAME_MOVE_OK if the move is successful, GAME_MOVE_IS_SCORCHED if the
 * tile the player wants to move to is scorched, GAME_MOVE_OOB if the
 * tile is out of bounds, and GAME_MOVE_TANK if the tile we're moving to
 * is the tank. Will only change the player's position if the move is
 * successful (GAME_MOVE_OK). If the result is GAME_MOVE_TANK the score
 * of the soldier is incremented by one.
 */
game_move_t game_move_player ( game_direction_t dir );

#endif
