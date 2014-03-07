oak
===
- A simple and lightweight tree container. Written in C++11.
- Easy to use. Loosely modelled after `std::map<k,v>` interface with a few extras.
- Tiny. Header-only.
- Cross platform.
- No dependencies.
- MIT licensed.

### Sample
```c++
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
```

### API
- Oak is loosely modelled after `std::map<k,v>` interface with a few extras.
- Use `[k]` to create subtrees on demand. Like `std::map` already does for values.
- Use `(k)` to read subtrees. Do not create on demand.
- Use `.empty(k)` to check subtree existence.
- Use `.get(v)/.set(v)` to get/set leaf values.
- Use `.setdown()/.setup()` to set children/parent values.

## @todoc
- rest of API
