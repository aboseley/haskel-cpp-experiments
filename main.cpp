// using a closure to simulate objects, and do compile time math

#include <algorithm>
#include <iostream>

// object constructor
auto createCup = [](int flOz) {
    // return a closure that captures the input data
    // and also allows us to apply a method to it
    return [flOz](auto && method) {
        return method(flOz);
    };
};

// object instance
auto constexpr coffeeCup = createCup(12);

// return function parameter as the function result
auto constexpr ident = [](auto x) { return x; };

// access the stored parameter in the closure
auto getOz = [](auto aCup) {
    return aCup( ident );
};

// operations
auto drink = [](auto aCup, auto flOz_drank){
    auto const flOz_cup = getOz(aCup) ;
    int const flOz_diff = flOz_cup - flOz_drank;
    int const remaining = std::max( 0, flOz_drank );
    return createCup( remaining );
};

auto constexpr full_coffee_size = getOz(coffeeCup);
auto constexpr after_sip_size = getOz(drink( coffeeCup, 2));

int main() {
    std::cout << "full coffee " << full_coffee_size << std::endl;
    std::cout << "after sip " << after_sip_size << std::endl;
}
