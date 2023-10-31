#include "rtos_api.hpp"
#include <cstdint>

int main()
{
    while(true) {
        Rtos::Api::yieldThread();
    }

    return 0;
}
