//============================================================================
// Name        : BDEPlayground.cpp
// Author      : Shadow Walker
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <bsl_map.h>
#include <bdlb_variant.h>


#include <variant>
#include <string>
#include <cassert>

using namespace std;
using namespace BloombergLP;
using namespace std::literals;

class SwitchTable {
public:
    typedef bdlb::Variant<int, bool, double> switch_type;
    typedef int  id_type;

     // set switch value
     template<typename T>
     SwitchTable& set(id_type, T);

     // retrieve switch value. Throws if not found
     template<typename T>
     const T& get(id_type) const;
 private:
    bsl::map<id_type,  switch_type> m_switches;
};

int main(){
    std::variant<int, float> v, w;
    v = 12; // v contains int
    int i = std::get<int>(v);
    cout << i << endl;
    w = std::get<int>(v);
    w = std::get<0>(v); // same effect as the previous line
    w = v; // same effect as the previous line


//  std::get<double>(v); // error: no double in [int, float]
//  std::get<3>(v);      // error: valid index values are 0 and 1

    try {
      std::get<float>(w); // w contains int, not float: will throw
    }
    catch (const std::bad_variant_access&) {}

    std::variant<std::string> x("abc"); // converting constructors work when unambiguous
    x = "def"; // converting assignment also works when unambiguous

    std::variant<std::string, bool> y("abc"); // casts to bool when passed a char const *
    assert(std::holds_alternative<bool>(y)); // succeeds
    y = "xyz"s;
    assert(std::holds_alternative<std::string>(y)); //succeeds
}
