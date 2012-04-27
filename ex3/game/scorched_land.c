#include <stdlib.h>
#include <math.h>
#include "scorched_land.h"

const game_position_t GAME_SHOT_OOB = {GAME_WIDTH, GAME_HEIGHT};
const game_position_t GAME_SHOT_ILLEGAL_ARGUMENT = {GAME_WIDTH + 1, GAME_HEIGHT + 1};

static const double
GAME_STRENGTH_SCALE = sqrt ( GAME_WIDTH * GAME_WIDTH +
                             GAME_HEIGHT * GAME_HEIGHT ) /
                             GAME_MAX_STRENGTH;

static char path_exists ( void );

void game_init ( void )
{
    game_soldier_score = 0;
    game_tank_score = 0;
    game_reset ();
}

void game_reset ( void )
{
    int i, j;
    for (i = 0; i < GAME_HEIGHT; i++)
        for ( j = 0; j < GAME_WIDTH; j++)
            game_is_scorched[j][i] = FALSE;
    game_player.x = 0;
    game_player.y = GAME_HEIGHT-1;
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
    double radians = ( direction ) * ( M_PI / 180 ),
           x_multiplier = cos ( radians ),
           y_multiplier = sin ( radians ),
           scaled_strength = strength *  GAME_STRENGTH_SCALE;

    int    x = (int) ( x_multiplier * scaled_strength ),
           y = (int) ( y_multiplier * scaled_strength );
    /* Flip the x-position. */
    x = GAME_WIDTH - 1 - x;

    /* Boundary check on x and y */
    if (  x < 0 || y < 0
       || GAME_WIDTH <= x || GAME_HEIGHT <= y )
    {
        return GAME_SHOT_OOB;
    }

    /* Otherwise, we've hit a legal target. */
    game_position_t position = {x, y};
    game_is_scorched[y][x] = TRUE;

    if (( game_player.x == x && game_player.y == y)
        || ( path_exists () == FALSE ))
    {
        game_tank_score++;
        position.x *= -1;
        position.y *= -1;
        return position;
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
        game_soldier_score++;
        return GAME_MOVE_TANK;
    }
    else
    {
        return GAME_MOVE_OK;
    }
}

static char path_exists_dfs (char* visited, int x, int y )
{
    /* Boundary check and check if we've visited this node
     * before */
    if (   x < 0 || y < 0 
        || GAME_WIDTH <= x || GAME_HEIGHT <= y
        || visited[y * GAME_HEIGHT + x] == TRUE )
    {
        return FALSE;
    }
    visited[y * GAME_HEIGHT + x] = TRUE;

    if ( x == GAME_WIDTH - 1 && y == GAME_HEIGHT - 1)
        return TRUE;

    if ( game_is_scorched[y][x] == TRUE)
    {
        return FALSE;
    }
    else 
    {
        game_position_t d[4] = {{0,-1},{0,1},
                                {-1,0},{1,0}};
        int i;
        char res = FALSE;
        for ( i = 0; i < 4; i++ )
        {
            res +=
                 path_exists_dfs ( visited, x + d[i].x, y + d[i].y );
        }
        if ( res == FALSE )
        {
            return FALSE;
        }
        else 
        {
            return TRUE;
        }
    }
}

static char path_exists ( void )
{
    char visited[GAME_HEIGHT][GAME_WIDTH];
    int i, j;
    
    for ( i = 0; i < GAME_HEIGHT; i++ )
        for ( j = 0; j < GAME_WIDTH; j++ )
            visited[i][j] = FALSE;

    return path_exists_dfs ( &(visited[0][0]), game_player.x, game_player.y ) ;
}
