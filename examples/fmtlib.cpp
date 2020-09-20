#include "adat/fmt/format.h"
#include "adat/fmt/ranges.h"
#include "adat/fmt/color.h"
#include <iostream>


int main()
{
    std::vector<float> v = {4, 3.55675f, 6.27f};
    std::cout << fmt::format("Vector : [{:.2f}]\n", fmt::join(v, ", "));

    std::cout << fmt::format("float1: {}, float2: {:0.2f}, integer: {:d}, string: {:s}",
                             5.6791f, 5.6791f, 781, "example") << std::endl;

    std::array<int, 3> a = {1, 2, 3};
    fmt::print("{}\n", a);
    fmt::print("{}\n", fmt::join(a, " - "));

    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
               "Hello, {}!\n", "world");
    fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
               fmt::emphasis::underline, "Hello, {}!\n", "мир");
    fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
               "Hello, {}!\n", "世界");
    return (0);
}
