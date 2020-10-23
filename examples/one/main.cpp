#include <iostream>

#include "../../include/Beacon/beacon.h"

void add(const int a_x, const int a_y)
{
    std::cout << a_x + a_y << std::endl;
}

int main()
{
    Beacon::Event<int, int> e;
    e.addListener(add);

    e.call(5, 5);

    return 0;
}
