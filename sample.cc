#include <iostream>
#include <string>
#include "oak.hpp"

int main() {
    oak::tree<std::string, int> t;

    // read-write access [] operator (creates trees on demand)
    t["fruits"]["oranges"];
    t["fruits"]["pineapples"] = 6;
    t["fruits"]["lemons"] = 12;
    t["animals"]["pigs"]["pink"] = 0;
    t["animals"]["pigs"]["guinea"] = 0;

    assert( 2 == t.size() );
    assert( 3 == t["fruits"].size() );

    // read-only access () operator (does not create tree on demand)
    t("fruits")("operator () should never create on demand");
    assert( 3 == t("fruits").size() );

    // print some subtrees
    for( auto &k : t("animals") ) {
        std::cout << ".key=" << k.first << "; .tree {\n" << k.second << "}" << std::endl;
    }

    // more printing
    std::cout << t << std::endl;
    std::cout << t.as_csv() << std::endl;

    std::cout << "All ok." << std::endl;
}
