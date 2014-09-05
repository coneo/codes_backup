#include <iostream>
#include <memory>
#include <functional>
#include <chrono>
using namespace std;

void performance ( void (*pfun)(), uint32_t times )
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

    start = std::chrono::system_clock::now();
    for(int i = 0; i < times; ++i)
        (*pfun)();
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << std::dec << std::fixed << "1 finished computation at " << std::ctime(&end_time)
    << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
