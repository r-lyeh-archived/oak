oak  <a href="https://travis-ci.org/r-lyeh/oak"><img src="https://api.travis-ci.org/r-lyeh/oak.svg?branch=master" align="right" /></a>
===

- Oak is a lightweight tree container. Written in C++03.
- Oak is simple. Loosely modeled after `std::map<k,v>` interface with a few extras.
- Oak is tiny. Header-only.
- Oak is cross-platform.
- Oak is stand-alone. No dependencies.
- Oak is zlib/libpng licensed.

### API
- Oak is loosely modeled after `std::map<k,v>` interface with a few extras.
- Use `[k]` to read/create subtrees on demand (standard `std::map` behavior).
- Use `(k)` to read subtrees. Does not create subtrees on demand.
- Use `.empty(k)` to check subtree existence.
- Use `.get(v)/.set(v)` to get/set leaf values.
- Use `.setdown()/.setup()` to set children/parent values.

### Sample
```c++
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
```

### Possible output
```c++
.key=pigs; .tree {
[2] guinea (0)
[2] pink (0)
}
[2] animals (0)
        [1] pigs (0)
                [2] guinea (0)
                [2] pink (0)
[2] fruits (0)
        [3] lemons (12)
        [3] oranges (0)
        [3] pineapples (6)

/animals,0
/animals/pigs,0
/animals/pigs/guinea,0
/animals/pigs/pink,0
/fruits,0
/fruits/lemons,12
/fruits/oranges,0
/fruits/pineapples,6

All ok.
```

## @todoc
- rest of API, including `walk()`
