#include "stdafx.h"
#include <inex/engine/sources/engine_device.h>

#include <time.h>

namespace inex {
namespace engine {

void    update_world ( )
{
    printf( "update_world\n" );
                                    // 5 px for 1 frame // (~1 second)
    // float some_movement             = 5 * m_delta;
}

float round(float f) {
    double t = (double)f + 6755399441055744.0;
    return (float)*((int *)(&t));
}

float   get_time   ( )
{
    // these returns epoch time
    // timespec            spec;
    // clock_gettime       ( CLOCK_PROCESS_CPUTIME_ID, &spec );
    // return              spec.tv_sec + ( spec.tv_nsec / 1.0e6 );

    // tms tm;
    // clock_t time            = times(&tm);
    // long res                = sysconf(_SC_CLK_TCK);
    // double f                = ( (float)time/(float)res );
    return                  ( float )clock( ) / ( float )CLOCKS_PER_SEC;
}

/***
*
* void engine_device::run ( )
*
* m_delta makes the changing of game time for game logic, rendering etc
* regardless of the frame rate. if game's on 30 fps, some_movement
* will be 150 per sec. if it's 60, some_movement will move 2 times slower
* (2.5 per frame)
*
****************************************************/

void    device::run ( )
{
    float last_frame_time               = get_time( );
    for ( ; ; )
    {    
        float current                   = get_time( );
        float delta                     = current - last_frame_time;
        printf (    "last frame: %f; current: %f; delta: %f",
        last_frame_time, current, delta );
        // process input;
        // update ( delta )
        // render ( )
        // sleep ( 10 );
        last_frame_time                 = current;
    }









// #   define NS_IN_S                  1E9
//     s32 const frames_per_second     = 25,
//         skip_ticks                  = 1000 / frames_per_second;
//     u32 application_active          = 1;
//     timespec delta_pack             ;
//     ASSERT_S( !clock_gettime                   ( CLOCK_PROCESS_CPUTIME_ID, &delta_pack ) );
//     u64 next_game_tick              = delta_pack.tv_sec + delta_pack.tv_nsec / NS_IN_S;
//     s32 sleep_time                  = 0;
//     printf( "next_game_tick:\t%d\n", next_game_tick );

//     while ( application_active )
//     {
//         update_world                ( );
//         // render_wordl                ( );

//         next_game_tick              += skip_ticks ;
//         printf( "next_game_tick:\t%d; ", next_game_tick );
//                                                     // clock_monotonic
//         ASSERT_S( !clock_gettime                   ( CLOCK_PROCESS_CPUTIME_ID, &delta_pack ) );
//         sleep_time                  = next_game_tick - ( delta_pack.tv_sec + delta_pack.tv_nsec / NS_IN_S );
//         printf( "sleepTime:\t%d\n", sleep_time );
//         if ( sleep_time >= 0 )
//         {
//             sleep                   ( sleep_time / 1000 /* / 1000 */ );
//         }

//         if ( sleep_time > 300 ) exit( 1 );

    //}
}

} // namespace inex
} // namespace engine
