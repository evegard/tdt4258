#include <stdlib.h>
#include <math.h>
#include "scorched_land.h"

static const double 
GAME_STRENGTH_SCALE = sqrt ( GAME_WIDTH * GAME_WIDTH +
                             GAME_HEIGHT * GAME_HEIGHT ) /
                             GAME_MAX_STRENGTH;

static void game_reset ( void );
static char flood_fill ( void );

void game_init ( void )
{
    game_soldier_score = 0;
    game_tank_score = 0;
    game_reset ();
}

static void game_reset ( void )
{
    int i, j;
    for (i = 0; i < GAME_HEIGHT; i++)
        for ( j = 0; j < GAME_WIDTH; j++)
            game_is_scorched = GAME_TILE_UNSCORCHED;
    game_player.x = 0;
    game_player.y = 0;
}

game_position_t game_shoot_bullet ( int direction, int strength )
{
    /* Boundary check on input */
    if ( ( direction < 0 ) || ( GAME_MAX_DIRECTION < direction )
      || ( strength  < 0 ) || ( GAME_MAX_STRENGTH  < strength  ))
    {
        return GAME_SHOT_ILLEGAL_ARGUMENT;
    }

    /* Calculate x and y-positions */
    double radians = ( dir + 2 * GAME_MAX_DIRECTION ) * M_PI /
                     ( 2 * GAME_MAX_DIRECTION ),
           x_multiplier = cos ( radians ),
           y_multiplier = sin ( radians ),
           scaled_strength = strength *  GAME_STRENGTH_SCALE;

    int    x = (int) (( GAME_WIDTH - 1)  - x_multiplier * scaled_strength ),
           y = (int) (( GAME_HEIGHT - 1) - y_multiplier * scaled_strength );

    /* Boundary check on x and y */
    if (  x < 0 || y < 0
       || GAME_WIDTH <= x || GAME_HEIGHT <= y )
    {
        return GAME_SHOT_OOB;
    }

    /* Otherwise, we've hit a legal target. */
    game_position_t position = {x, y};
    game_is_scorched[y][x] = GAME_TILE_SCORCHED;

    if (( game_player.x == x && game_player.y == y)
        || flood_fill())
    {
        game_tank_score++;
        game_reset ();
        return 
    }
    else 
    {
        return position;
    }
}

game_move_t game_move_player ( game_direction_t dir )
{
    int dx = 0, dy = 0;
    switch ( dir )
    {
        case GAME_NORTH: dy = -1; break;
        case GAME_SOUTH: dy =  1; break;
        case  GAME_WEST: dx = -1; break;
        case  GAME_EAST: dx =  1; break;
    }
    /* Boundary check */
    if (   (( game_player.x + dx ) < 0 )
        || (( game_player.y + dy ) < 0 )
        || ( GAME_WIDTH <= ( game_player.x + dx ))
        || ( GAME_HEIGHT <= ( game_player.y + dy )))
    {
        return GAME_MOVE_OOB;
    }

    if ( game_is_scorched[game_player.y + dy][game_player.x + dx] )
    {
        return GAME_MOVE_IS_SCORCHED;
    }
    
    /* Otherwise, legal move. */
    game_player.x += dx;
    game_player.y += dy;
    
    if (   ( GAME_WIDTH - 1 <= game_player.x )
       && ( GAME_HEIGHT - 1 <= game_player.y ))
    {
        game_reset ();
        game_soldier_score++;
        return GAME_MOVE_TANK;
    }
    else
    {
        return GAME_MOVE_OK;
    }
}

static char flood_fill ( void )
{
    /* TODO */
    return -1;
}