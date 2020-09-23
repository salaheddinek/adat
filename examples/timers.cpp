#include "adat/timers_for_benchmark.hpp"
#include <thread>
#include <iostream>
#include <algorithm>


void instance1()
{
    auto mutli_timer = Multi_timer_singleton::get_instance();
    mutli_timer->activate_timer("Process 1");
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

void instance2()
{
    auto mutli_timer = Multi_timer_singleton::get_instance();
    mutli_timer->activate_timer("Process 2");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}


void instance3()
{
    auto mutli_timer = Multi_timer_singleton::get_instance();
    mutli_timer->activate_timer("Process 3");
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void print_timer()
{
    auto mutli_timer = Multi_timer_singleton::get_instance();
    std::cout << mutli_timer->get_timers_formatted_elapsed_time() << std::endl;
}

int main(){

    tfb::Multi_timer multi_timer ;

    for(size_t i = 0; i < 10; i++){

        multi_timer.activate_timer("file reading");
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        multi_timer.activate_timer("data processing");
        std::this_thread::sleep_for(std::chrono::milliseconds(190));

        multi_timer.activate_timer("saving to file");
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    multi_timer.pause_current_timer();

    std::cout << multi_timer.get_timers_formatted_elapsed_time() << std::endl;



    for(size_t i = 0; i < 10; i++){

        instance1();
        instance2();
        instance3();
    }
    print_timer();

    return (0);
}
