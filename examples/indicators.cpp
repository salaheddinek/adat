#include "adat/indicators.hpp"

int main(){
    size_t size = 15;
    Iteration_progress_bar bar(size);
    for(uint i = 0; i < size; i++){
        bar.tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return(0);
}
