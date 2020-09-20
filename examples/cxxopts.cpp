#include "adat/cxxopts.hpp"


void parse(int argc, const char** argv)
{
    cxxopts::Options options("simple", "A brief description");

    options.add_options()
        ("b,bar", "Param bar (required)", cxxopts::value<std::string>())
        ("d,debug", "Enable debugging", cxxopts::value<bool>()->default_value("false"))
        ("f,foo", "Param foo", cxxopts::value<int>()->default_value("10"))
        ("h,help", "Print usage")
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
      std::cout << options.help() << std::endl;
      exit(0);
    }

    result.check_for_required_options({"bar"});



    bool debug = result["debug"].as<bool>();

    std::string bar;
    if (result.count("bar"))
      bar = result["bar"].as<std::string>();

    if(debug)
        std::cout << "Debug mode activated!\n";

    int foo = result["foo"].as<int>();
    std::cout << "foo = " << foo << std::endl;

}

int main(int argc, const char** argv)
{
    parse(argc, argv);
    return (0);
}

