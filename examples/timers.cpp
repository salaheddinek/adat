#include "adat/timers_for_benchmark.hpp"
#include <thread>
#include <iostream>


int main(){

    tfb::Multi_timer multi_timer;

    for(size_t i = 0; i < 30; i++){
        multi_timer.activate_timer("file reading");
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        multi_timer.activate_timer("data processing");
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        multi_timer.activate_timer("saving to file");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
    multi_timer.pause_current_timer();

    std::cout << multi_timer.get_timers_formatted_elapsed_time() << std::endl;
    return (0);
}
