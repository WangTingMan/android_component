#include "timer_test.h"
#include <utils/Timers.h>

#include <base/logging.h>

uint32_t timer1 = 0;
uint32_t timer2 = 0;

void timer_test()
{
    timer1 = create_timer( nullptr, "" );
    set_timer_option( timer1, 1000, []()
    {
        LOG( ERROR ) << "timer1 triggered. timer2 remain "
            << get_timer_remaining_ms( timer2 )
            << "ms";
    } );

    timer2 = create_timer( nullptr, "" );
    set_timer_option( timer2, 2000, []()
    {
        LOG( ERROR ) << "timer2 triggered. timer1 remain "
            << get_timer_remaining_ms( timer1 )
            << "ms";
    } );
}

