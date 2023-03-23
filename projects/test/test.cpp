
#include <iostream>
#include <atomic>

class UUU
{
public:

    char x = '\0';
    std::atomic_int32_t v1;
    char y = '\0';
};

int main()
{
    UUU u;
    u.v1 = 0xFFFFFFFFFF;

    std::atomic_int32_t io;
    io.fetch_add( 2 );
    constexpr int x = sizeof( std::atomic_int32_t );
    constexpr int y = sizeof( std::atomic_int64_t );
    std::cout << "Hello World!\n";
}

