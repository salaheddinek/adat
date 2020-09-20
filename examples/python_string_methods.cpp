#include "adat/python_string_methods.hpp"
#include <iostream>

int main()
{
    std::string cent = psm::center("center me", 25);
    std::cout << "1. centered:        [" << cent << "] " <<std::endl;

    std::vector<std::string> vector = {"foo", "cat", "car"};
    std::cout << "2. joined vector:   [" << psm::join(vector, ", ") << "] " << std::endl;

    std::array<std::string, 3> array = {"foo", "cat", "car"};
    std::cout << "3. joined array:    [" << psm::join(array, ", ") << "] " << std::endl;

    std::string str ("There are two needles in this haystack with needles.");
    std::string str2 ("needles.");
    std::cout<< "4. does ends with:  " << psm::endswith(str, str2) << std::endl;

    std::cout<< "5. found index:     " << psm::find(str, str2) << std::endl;

    std::string str3 = "There are two needles  in this haystack with needles.";
    std::vector<std::string> words = psm::delempty(psm::split(str3, ' '));
    std::cout<< "6. split:           [" << psm::join(words, ", ") << "]" << std::endl;
    return (0);
}
