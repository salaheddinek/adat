#include "adat/tabulate.hpp"

int main(){
    Default_tabulate table(3);
    table.add_row({"Company", "Contact", "Country"});
    table.add_row({"Alfreds Futterkiste", "Maria Anders", "Germany"});
    table.add_row({"Centro comercial Moctezuma" , "Francisco Chang", "Mexico", "mistake cell"});
    table.add_row({"Ernst Handel", "Roland Mendel", "Austria"});
    table.add_row({"Island Trading", "Helen Bennett", "UK"});
    table.add_row({"Laughing Bacchus Winecellars", "Yoshi Tannamuri"});
    table.add_row({"Magazzini Alimentari Riuniti", "Giovanni Rovelli", "Italy"});

    std::cout << table.str() << std::endl;

    std::cout << "\nTable2\n"<< std::endl;

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

    return(0);
}
