#include "adat/nlohmann/json.hpp"
#include <fstream>

int main(){

    nlohmann::json j;

    j["pi"] = 3.141;
    j["happy"] = true;
    j["name"] = "Niels";
    j["nothing"] = nullptr;
    j["answer"]["everything"] = 42;
    j["list"] = { 1, 0, 2 };
    j["object"] = { {"currency", "USD"}, {"value", 42.99} };

    std::string json_data = j.dump(4);
    std::cout << json_data << std::endl;

    std::ofstream outfile ("test.json");
    outfile << json_data << std::endl;
    outfile.close();

    nlohmann::json j_result = nlohmann::json::parse(json_data);

    std::cout << "\nRetrieving data...\n" << std::endl;

    bool is_happy = false;
    nlohmann::get_value(j_result, "happy", is_happy);
    std::cout << "value of ['happy']: " << is_happy << std::endl;

    std::array<int, 3> ints {-1, -1, -1};
    nlohmann::get_value(j_result, "list", ints);
    std::cout << "value of ['list']: [" << ints.at(0) << ", "
              << ints.at(1) << ", " <<ints.at(2) << "]" << std::endl;


    std::string name = "-1";
    nlohmann::get_value(j_result, "name", name);
    std::cout << "value of ['name']: " << name << std::endl;

    int one_int = -1;
    nlohmann::get_value_v(j_result, {"answer", "everything"}, one_int);
    std::cout << "value of ['answer']['everything']: " << one_int << std::endl;

    std::string wrong_key = "-1";
    nlohmann::get_value(j_result, "does_not_exists", wrong_key);

    return (0);
}
