#include "adat/timers_for_benchmark.hpp"
#include <thread>
#include <iostream>


int main(){
    tfb::mini_timer read_file("file reading");
    tfb::mini_timer process_data("data processing");
    tfb::mini_timer save_file("saving to file");
    tfb::Multi_timer multi_timer({&read_file, &process_data, &save_file});

    for(size_t i = 0; i < 30; i++){
        multi_timer.activate_timer(read_file);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        multi_timer.activate_timer(process_data);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        multi_timer.activate_timer(save_file);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
    multi_timer.pause_current_timer();

    std::cout << multi_timer.get_timers_formatted_elapsed_time() << std::endl;
    return (0);
}
