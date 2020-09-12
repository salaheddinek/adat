# third-party-hpp
A set of permissive header only libraries to use as third party.

## fmtlib

```
add_definitions(-DFMT_HEADER_ONLY)
```


 ```c++
std::vector<float> v = {4, 3.55675f, 6.2f};
std::cout << fmt::format("Vector: [{:.2f}]\n", fmt::join(v, ", "));
// prints: "Vector: [4.00, 3.56, 6.20]"
 ```

## Indicators

```
class Iteration_progress_bar : public indicators::ProgressBar {
public:
    Iteration_progress_bar (const size_t size, const std::string prefix = ""):
        m_size(size)
    {
        std::string pre = prefix == ""? "Progress :": prefix;
        namespace iopt = indicators::option;
        this->set_option(iopt::BarWidth{50});
        this->set_option(iopt::ShowElapsedTime{true});
        this->set_option(iopt::ShowRemainingTime{true});
        this->set_option(iopt::PostfixText{"0/" + std::to_string(size)});
        this->set_option(iopt::PrefixText{pre});
        this->set_option(iopt::ForegroundColor{indicators::Color::green});
        this->set_option(iopt::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}});
        this->set_option(iopt::ShowPercentage{true});
    }

    void tick(){
        m_iter++;
        size_t internal_progress = static_cast<size_t>(m_iter * 100 / m_size);
        if(internal_progress == m_progress)
            return;
        if(internal_progress == 100 && m_iter <= m_size - 1)
            return;
        m_progress = internal_progress;
        this->set_option(indicators::option::PostfixText{
                             std::to_string(m_iter) + "/" + std::to_string(m_size)});
        this->set_progress(m_progress);


    }
private:
    size_t m_size {0};
    size_t m_iter {0};
    size_t m_progress {0};

};
```

example

```
int main(int argc, const char** argv)
{
    size_t size = 15;
    Iteration_progress_bar bar(size);
    for(uint i = 0; i < size; i++){
        bar.tick();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Update bar state
    return 0;
}

```


# tabluate

```
class Default_tabulate {
public:
    Default_tabulate(const uint num_columns):
        m_num_columns(num_columns)
    {

    }
    void set_first_row_as_title(const bool first_row_as_title)
    {
        m_first_row_as_title = first_row_as_title;
    }
    void set_add_padding_flag(const bool add_padding)
    {
        m_add_padding = add_padding;
    }
    void add_row(const std::vector<std::string>& row)
    {
        std::vector<variant<std::string, const char *, tabulate::Table>> line;
        for(uint i = 0; i < row.size(); i++){
            line.push_back(static_cast<variant<std::string, const char *, tabulate::Table>>(row.at(i)));
            if(i == (m_num_columns - 1))
                break;
        }
        m_table.add_row(line);
        m_num_rows++;
        if(!m_first_row_as_title || m_num_rows < 3)
            return;
        if(m_add_padding)
            m_table.row(m_num_rows - 1).format().padding_top(1);
        m_table.row(m_num_rows - 1).format().hide_border_top();

    }

    std::string str()
    {
        if(m_num_rows == 0)
            return "";

        m_table.row(0).format().font_align(tabulate::FontAlign::center);
        return m_table.str();
    }
private:
    tabulate::Table m_table;
    uint m_num_columns {0};
    uint m_num_rows {0};
    bool m_first_row_as_title {true};
    bool m_add_padding {false};
};
```

example 

```
    Default_tabulate table(3);
    table.add_row({"Company", "Contact", "Country"});
    table.add_row({"Alfreds Futterkiste", "Maria Anders", "Germany"});
    table.add_row({"Centro comercial Moctezuma" , "Francisco Chang", "Mexico", "mistake cell"});
    table.add_row({"Ernst Handel", "Roland Mendel", "Austria"});
    table.add_row({"Island Trading", "Helen Bennett", "UK"});
    table.add_row({"Laughing Bacchus Winecellars", "Yoshi Tannamuri"});
    table.add_row({"Magazzini Alimentari Riuniti", "Giovanni Rovelli", "Italy"});

    std::cout << table.str() << std::endl;
```

example 2 

```
    tabulate::Table table2;
    table2.add_row({"Company", "Contact", "Country"});
    table2.add_row({"Alfreds Futterkiste", "Maria Anders", "Germany"});
    table2.add_row({"Centro comercial Moctezuma" , "Francisco Chang", "Mexico"});
    table2.add_row({"Ernst Handel", "Roland Mendel", "Austria"});
    table2.add_row({"Island Trading", "Helen Bennett", "UK"});
    table2.add_row({"Laughing Bacchus Winecellars", "Yoshi Tannamuri", "spain"});
    table2.add_row({"Magazzini Alimentari Riuniti", "Giovanni Rovelli", "Italy"});
    table2.row(0).format()
            .font_color(tabulate::Color::yellow)
            .font_align(tabulate::FontAlign::center)
            .font_style({tabulate::FontStyle::bold, tabulate::FontStyle::underline});
    std::cout << table2 << std::endl;
```

#  nlohmann-json 


```
template<typename T>
bool get_value(const nlohmann::json& j, const std::string key, T& value)
{
    try {
        value = j[key];
    } catch (const nlohmann::json::exception& ex) {
        std::cerr << "key = [" << key << "]: " << ex.what() << std::endl;
        return false;
    }
    return true;
}
template<typename T>
bool get_value_v(const nlohmann::json& j,
                 const std::vector<std::string> key_sequence,
                 T& value)
{
    auto k = key_sequence;
    if(key_sequence.empty())
        return false;
    std::string key_str = "key = ['";
    for(uint i = 0; i < k.size() - 1; i++)
        key_str += k.at(i) + "']['";
    key_str += k.back() + "']: ";
    try {
        if(k.size() == 1)
            value = j[k.at(0)];
        if(k.size() == 2)
            value = j[k.at(0)][k.at(1)];
        if(k.size() == 3)
            value = j[k.at(0)][k.at(1)][k.at(2)];
        if(k.size() == 4)
            value = j[k.at(0)][k.at(1)][k.at(2)][k.at(3)];
        if(k.size() == 5)
            value = j[k.at(0)][k.at(1)][k.at(2)][k.at(3)][k.at(4)];
        if(k.size() > 5){
            std::cerr << key_str << "Too long key sequence > 5" << std::endl;
            return false;
        }
    } catch (const nlohmann::json::exception& ex) {
        std::cerr << key_str << ex.what() << std::endl;
        return false;
    }
    return true;
}
```

example

```
    nlohmann::json j;
    j["pi"] = 3.141;
    j["happy"] = true;
    j["name"] = "Niels";
    j["nothing"] = nullptr;
    j["answer"]["everything"] = 42;
    j["list"] = { 1, 0, 2 , 7};
    j["object"] = { {"currency", "USD"}, {"value", 42.99} };

    std::string json_data = j.dump(4);
    std::cout << json_data << std::endl;

    int test_int;
    get_value_v(j, {"answer", "everything"}, test_int);
    std::cout << test_int << std::endl;
```