#include "timer__.h"
#include <iostream>
#include <chrono>

struct GrantorDescriptor {
    uint32_t flags /*__attribute__((aligned(4)))*/;
    uint32_t fdIndex /*__attribute__((aligned(4)))*/;
    uint32_t offset /*__attribute__((aligned(4)))*/;
    uint64_t extent /*__attribute__((aligned(8)))*/;
};

int main()
{
    std::chrono::system_clock::now();
    std::chrono::Sunday;
    std::chrono::year_month_day ymd{ std::chrono::October / 21 / 2021 };
    auto x = ymd.month();


    constexpr uint32_t offset_1 = offsetof(GrantorDescriptor, extent);
    constexpr uint32_t size_1 = sizeof(GrantorDescriptor);
    constexpr uint32_t size_2 = __alignof(GrantorDescriptor);

    ModernCppTimer t;
    t.start(5 * 1000, []
        {
            std::cout << "Hello World!\n";
        });

    system("pause");
    return 0;
}

