#include <iostream>
#include <string>
#include "oak.hpp"

int main() {
    oak::tree<std::string, int> t;

    // create trees on demand. read-write access [] operator
    t["fruits"]["oranges"];
    t["fruits"]["pineapples"] = 6;
    t["fruits"]["lemons"] = 12;
    t["animals"]["pigs"]["pink"] = 0;
    t["animals"]["pigs"]["guinea"] = 0;

    assert( 2 == t.size() );
    assert( 3 == t("fruits").size() );

    // read-only access () operator
    t("fruits")("operator () should never create on demand");
    assert( 3 == t("fruits").size() );

    // print some:
    for( auto &k : t("animals") ) {
        std::cout << ".key=" << k.first << "; .tree {\n" << k.second << "}" << std::endl;
    }

    // or also:
    std::cout << t << std::endl;

    std::cout << "All ok." << std::endl;
}
