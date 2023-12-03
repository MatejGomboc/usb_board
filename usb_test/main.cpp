#include "rtos/threads.hpp"
#include <cstdint>

int main()
{
    while (true) {
        Rtos::Threads::yieldThread();
    }

    return 0;
}
