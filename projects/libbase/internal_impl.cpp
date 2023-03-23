
#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <android-base\unique_fd.h>
#include <corecrt_io.h>
#include <iostream>

extern "C"
int posix_strerror_r( int errnum, char* buf, size_t buflen )
{
    return 0;
}


namespace android
{
namespace base
{

void DefaultCloser::Close( int fd )
{
    close( fd );
}

}
}
