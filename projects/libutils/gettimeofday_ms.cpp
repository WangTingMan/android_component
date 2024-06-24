/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <time.h> 
#include <windows.h>
#include <chrono>

#include <utils/Timers.h>

namespace
{

#define FILETIME_1970 \
    116444736000000000ull /* seconds between 1/1/1601 and 1/1/1970 */
#define HECTONANOSEC_PER_SEC 10000000ull

typedef  VOID( CALLBACK* SystemTime )( LPFILETIME );

// This is a poor resolution timer, but at least it
// is available on Win7 and older. System.cpp will install
// a better one.
static SystemTime getSystemTime = &GetSystemTimeAsFileTime;

int getntptimeofday( struct timespec*, struct timezone* );

int getntptimeofday( struct timespec* tp, struct timezone* z )
{
    int res = 0;
    union
    {
        unsigned long long ns100; /*time since 1 Jan 1601 in 100ns units */
        FILETIME ft;
    } _now;
    TIME_ZONE_INFORMATION TimeZoneInformation;
    DWORD tzi;

    if( z != NULL )
    {
        if( ( tzi = GetTimeZoneInformation( &TimeZoneInformation ) ) !=
            TIME_ZONE_ID_INVALID )
        {
            z->tz_minuteswest = TimeZoneInformation.Bias;
            if( tzi == TIME_ZONE_ID_DAYLIGHT )
                z->tz_dsttime = 1;
            else
                z->tz_dsttime = 0;
        }
        else
        {
            z->tz_minuteswest = 0;
            z->tz_dsttime = 0;
        }
    }

    if( tp != NULL )
    {
        getSystemTime( &_now.ft ); /* 100-nanoseconds since 1-1-1601 */
        /* The actual accuracy on XP seems to be 125,000 nanoseconds = 125
         * microseconds = 0.125 milliseconds */
        _now.ns100 -= FILETIME_1970; /* 100 nano-seconds since 1-1-1970 */
        tp->tv_sec =
            _now.ns100 / HECTONANOSEC_PER_SEC; /* seconds since 1-1-1970 */
        tp->tv_nsec = ( long )( _now.ns100 % HECTONANOSEC_PER_SEC ) *
            100; /* nanoseconds */
    }
    return res;
}

}

#ifdef __cplusplus
extern "C" {
#endif

int gettimeofday(struct timeval* p, struct timezone* z)
{
    struct timespec tp;

    if (getntptimeofday(&tp, z))
        return -1;
    p->tv_sec = tp.tv_sec;
    p->tv_usec = (tp.tv_nsec / 1000);
    return 0;
}

#if defined(_MSC_VER)
static void localtime_r( const time_t* secs, struct tm* time )
{
    (void)localtime_s( time, secs );
}
#endif

#define MS_PER_SEC      1000ULL     // MS = milliseconds
#define US_PER_MS       1000ULL     // US = microseconds
#define HNS_PER_US      10ULL       // HNS = hundred-nanoseconds (e.g., 1 hns = 100 ns)
#define NS_PER_US       1000ULL

#define HNS_PER_SEC     (MS_PER_SEC * US_PER_MS * HNS_PER_US)
#define NS_PER_HNS      (100ULL)    // NS = nanoseconds
#define NS_PER_SEC      (MS_PER_SEC * US_PER_MS * NS_PER_US)

int clock_gettime_monotonic( struct timespec* tv )
{
    static LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER ticks;

    if( !ticksPerSec.QuadPart )
    {
        QueryPerformanceFrequency( &ticksPerSec );
        if( !ticksPerSec.QuadPart )
        {
            errno = ENOTSUP;
            return -1;
        }
    }

    QueryPerformanceCounter( &ticks );

    tv->tv_sec = (long)( ticks.QuadPart / ticksPerSec.QuadPart );
    tv->tv_nsec = (long)( ( ( ticks.QuadPart % ticksPerSec.QuadPart ) * NS_PER_SEC ) / ticksPerSec.QuadPart );

    return 0;
}

int clock_gettime_realtime( struct timespec* tv )
{
    FILETIME ft;
    ULARGE_INTEGER hnsTime;

    GetSystemTimePreciseAsFileTime( &ft );

    hnsTime.LowPart = ft.dwLowDateTime;
    hnsTime.HighPart = ft.dwHighDateTime;

    // To get POSIX Epoch as baseline, subtract the number of hns intervals from Jan 1, 1601 to Jan 1, 1970.
    hnsTime.QuadPart -= ( 11644473600ULL * HNS_PER_SEC );

    // modulus by hns intervals per second first, then convert to ns, as not to lose resolution
    tv->tv_nsec = (long)( ( hnsTime.QuadPart % HNS_PER_SEC ) * NS_PER_HNS );
    tv->tv_sec = (long)( hnsTime.QuadPart / HNS_PER_SEC );

    return 0;
}

int clock_gettime_monotonic_raw( struct timespec* tv )
{
    auto now_ = std::chrono::high_resolution_clock::now()
        - std::chrono::high_resolution_clock::time_point();
    uint64_t seconds = std::chrono::duration_cast<std::chrono::seconds>( now_ ).count();
    uint64_t nano_seconds_part = std::chrono::duration_cast<std::chrono::nanoseconds>( now_ ).count();
    nano_seconds_part = nano_seconds_part -
        std::chrono::duration_cast<std::chrono::nanoseconds>( std::chrono::seconds(seconds) ).count();
    tv->tv_sec = seconds;
    tv->tv_nsec = nano_seconds_part;
    return 0;
}

int clock_gettime(int type, struct timespec* time)
{
    switch( type )
    {
    case CLOCK_MONOTONIC:
        return clock_gettime_monotonic( time );
    break;
    case CLOCK_REALTIME:
        return clock_gettime_realtime( time );
    break;
    case CLOCK_MONOTONIC_RAW:
    case CLOCK_BOOTTIME:
        return clock_gettime_monotonic_raw( time ); 
    break;
    }

    return timespec_get(time, TIME_UTC);
}

#ifdef __cplusplus
} // extern "C"
#endif

int64_t GetSystemInternal()
{
    timeval t = {};
    gettimeofday( &t, nullptr );
    return nsecs_t( t.tv_sec ) * 1000000000LL + nsecs_t( t.tv_usec ) * 1000LL;
}
