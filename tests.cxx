#include <iostream>
#include <string>
#include "oak.hpp"

int main()
{
    oak::tree<std::string> t;

    t("fruits");
    t("fruits")("oranges");
    t("fruits")("lemons");
    t("fruits")("grapes");
    t("animals")("pigs")("guinea");
    t("animals")("pigs")("thai");
    t("animals")("wombats");
    t("world");
    t("work");
    t("omg");
    t("oh noes");

    assert( !t.has("fruits") );
    assert( !t("fruits") );
    assert( t.size() == 0 );

    t["fruits"];
    t["fruits"]["oranges"];
    t["fruits"]["lemons"];
    t["fruits"]["grapes"];
    t["animals"]["pigs"]["guinea"];
    t["animals"]["pigs"]["thai"];
    t["animals"]["wombats"];
    t["omg"];
    t["oh noes"];

    assert( t.has("fruits") );
    assert( t["fruits"] );
    assert( t.size() == 4 );

    t["animals"]["pigs"].set( 1 );
    assert( t["animals"]["pigs"].get() == 1 );
    std::cout << t << std::endl;
    t["animals"]["pigs"].setdown( 2 );
    std::cout << t << std::endl;
    t["animals"]["pigs"].setup( 3 );
    std::cout << t << std::endl;

    t.erase("omg");
    assert( t.size() == 3 ); // t has 3 children

    assert( t("fruits") );
    assert( t("fruits")("oranges") );
    assert( !t("fruits")("watermelons") );

    assert( t("fruits").size() == 3 );
    assert( t("animals")("pigs").size() == 2 );

    std::cout << t << std::endl;
    std::cout << t("this should never create a new entry") << std::endl;
    std::cout << t("oh noes") << std::endl;
    std::cout << t << std::endl;

    // translate
#if 1
    {
        oak::tree<size_t> stree;
        std::map< std::string, size_t > translation_map;
        translation_map["fruits"] = 0;
        translation_map["oranges"] = 1;
        translation_map["lemons"] = 2;
        translation_map["grapes"] = 3;
        translation_map["animals"] = 4;
        translation_map["pigs"] = 5;
        translation_map["guinea"] = 6;
        translation_map["thai"] = 7;
        translation_map["wombats"] = 8;
        translation_map["omg"] = 9;
        translation_map["oh noes"] = 10;

        stree = t.rekey(translation_map);
        std::cout << stree << std::endl;
    }

    {
        oak::tree<size_t> stree;
        std::map< size_t, std::string > translation_map;
        translation_map[ 0] = "fruits";
        translation_map[ 1] = "oranges";
        translation_map[ 2] = "lemons";
        translation_map[ 3] = "grapes";
        translation_map[ 4] = "animals";
        translation_map[ 5] = "pigs";
        translation_map[ 6] = "guinea";
        translation_map[ 7] = "thai";
        translation_map[ 8] = "wombats";
        translation_map[ 9] = "omg";
        translation_map[10] = "oh noes";

        stree = t.rekey(translation_map);
        std::cout << stree << std::endl;
    }
#endif

    // working on leaves

    t["fruits"].clear();
    std::cout << t << std::endl;

    t["fruits"] = t["animals"]["pigs"];
    std::cout << t << std::endl;

    std::cout << "All ok." << std::endl;
    return 0;
}
