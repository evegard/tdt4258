#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../scorched_land.h"

#define SLEEPY_TIME    4
#define CLEAR_SCREEN   "\033[2J"
#define C_GRASS        "\033[2;42;32m"
#define C_SCORCHED     "\033[0;31;43m"
#define C_MILITARY     "\033[2;30;42m"
#define C_END          "\033[0m"
#define C_ERROR        "\033[1;31m"
#define C_ERROR_NOBOLD "\033[0;31m"
#define C_SCORE        "\033[0;37;44m"

void print_map ( void )
{
    int x, y;
    printf(CLEAR_SCREEN C_SCORE " S: %d  --  T: %d " C_END "\n",
            game_soldier_score, game_tank_score);
    for (y = 0; y < GAME_HEIGHT; y++){
        for (x = 0; x < GAME_WIDTH; x++)
            if (game_player.x == x && game_player.y == y)
                printf(C_MILITARY "S");
            else if (y < GAME_TANK_SIZE &&
                     GAME_WIDTH - GAME_TANK_SIZE <= x)
                printf(C_MILITARY "T");
            else
                printf(game_is_scorched[y][x] ? C_SCORCHED "X"
                                              : C_GRASS    "," );
        printf(C_END "\n");
    }
}

int main ( void )
{
    printf ( "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );
    game_init ();
    char p_turn = 0;
    while ( TRUE )
    {
        if ( p_turn == 0 )
        {
            p_turn = 1;
            char s_dir[40] = {0};
            game_move_t s_move = GAME_MOVE_OK;
            game_direction_t p_direction;
            while ( TRUE )
            {
                print_map ();
                switch ( s_move )
                {
                    case GAME_MOVE_TANK:
                    case GAME_MOVE_OK:
                        if ( s_dir[0] != 0 )
                            printf ( C_ERROR "ERROR: " C_ERROR_NOBOLD
                              "%c is an illegal character input!" C_END
                              "\n", s_dir[0] );
                        else
                            printf ( "It is the soldier's turn:\n" );
                    break;

                    case GAME_MOVE_IS_SCORCHED:
                        printf ( C_ERROR "ERROR: " C_ERROR_NOBOLD
                                "The tile you're trying to "
                                "move to is scorched!" C_END "\n");
                        break;

                    case GAME_MOVE_OOB:
                        printf ( C_ERROR "ERROR: " C_ERROR_NOBOLD
                                "The tile you're trying to is out "
                                "of bounds!" C_END "\n" );
                        break;
                }
                printf ( "Soldier - choose a direction to go to:" 
                         "w, a, s, d\n" );
                scanf ( "%s", &s_dir[0] );
                switch ( s_dir[0] ) 
                {
                    case 'd': p_direction = GAME_EAST; break;
                    case 'a': p_direction = GAME_WEST; break;
                    case 'w': p_direction = GAME_NORTH; break;
                    case 's': p_direction = GAME_SOUTH; break;
                    default: continue;
                }
                s_move = game_move_player ( p_direction );
                switch ( s_move ) {
                    case GAME_MOVE_OK:
                        break;
                    case GAME_MOVE_TANK:
                        print_map ();
                        printf ( "The soldier managed to reach the tank!\n"
                                "We will now reset the game.\n" );
                        sleep ( SLEEPY_TIME );
                        game_reset ();
                        break;
                    case GAME_MOVE_IS_SCORCHED:
                    case GAME_MOVE_OOB:
                        continue;
                }
                break;
            }
        }

        if ( p_turn == 1 )
        {
            game_position_t shot_pos = GAME_SHOT_OOB;
            int t_dir, t_str;
            p_turn = 0;
            while ( TRUE )
            {
                print_map ();
                if ( game_position_equals(shot_pos,
                          GAME_SHOT_ILLEGAL_ARGUMENT) )
                    printf ( C_ERROR "ERROR: " C_ERROR_NOBOLD
                            "The arguments you've given is out "
                            "of the legal range!" C_END "\n" );
                else
                    printf ( "It is time for the tank to shoot.\n" );
                printf ( "Tanks, choose the direction (0-%d) "
                         "and strength (0-%d) on the shot:\n",
                          GAME_MAX_DIRECTION, GAME_MAX_STRENGTH );
                scanf ( "%d %d", &t_dir, &t_str );
                shot_pos = game_shoot_bullet ( t_dir, t_str );
                if ( game_position_equals ( shot_pos, GAME_SHOT_OOB ))
                {
                    print_map ();
                    printf ( "Your bullet went out of the map!\n"
                             "Better luck next round...\n" );
                    sleep ( SLEEPY_TIME );
                    break;
                }
                else if ( !game_position_equals(shot_pos,
                            GAME_SHOT_ILLEGAL_ARGUMENT ))
                    {
                    print_map ();
                    if ( shot_pos.x < 0 && shot_pos.y < 0 )
                    {
                        printf ( "The tanks has destroyed all chances "
                                 "for the\n soldier to reach the tank! "
                                 "(Hit at %d, %d) \n",
                                 ~shot_pos.x, ~shot_pos.y );
                        game_reset ();
                    }
                    else {
                        printf ( "The tanks hit at %d, %d!\n\n",
                                  shot_pos.x, shot_pos.y);
                    }
                    sleep ( SLEEPY_TIME );
                    break;
                }
            }
        }
    }
    print_map ();

    return 0;
}
