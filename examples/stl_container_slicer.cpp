#include "adat/stl_container_slicer.hpp"
#include "adat/fmt/format.h"
#include "adat/fmt/ranges.h"
#include <array>
#include <vector>

int main(){
    std::vector<char> vec = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    std::string str = "012345678";

    std::vector<char> example1 = scs::slice(vec)[0_start & 2_step]; // equivlant to vec[0::2]
    std::cout << fmt::format("1: result=[{}]\n", fmt::join(example1, ", "));

    std::vector<char> example2 = scs::slice(vec)[-1_step];  // equivlant to vec[::-1]
    std::cout << fmt::format("2: result=[{}]\n", fmt::join(example2, ", "));

    std::vector<char> example3 = scs::slice(vec)[-1_start & 1_end & -1_step];  // equivlant to vec[-1:1:-1]
    std::cout << fmt::format("3: result=[{}]\n", fmt::join(example3, ", "));

    std::string example4 = scs::slice(str)[2_start & -2_step & -2_end]; // str[2:-2:-2]
    std::cout << fmt::format("4: result={:s}\n", example4); // displays nothing

    std::string example5 = scs::slice(str)[-3_end]; // str[:-3]
    std::cout << fmt::format("5: result={:s}\n", example5);

    char example6 = scs::slice(str)[-2]; // str[-2]
    std::cout << fmt::format("6: result={}\n", example6);

    std::string example7 = scs::slice(str).start(3).step(2).end(17).get(); // equivlant to  str[3:17:2]
    std::cout << fmt::format("7: result={}\n", example7);
    return (0);
}
