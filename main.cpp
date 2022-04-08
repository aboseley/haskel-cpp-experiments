// using a closure to simulate objects

// object constructor
auto createCup = [](auto flOz) {
    // return a closure that captures the input data
    // and also allows us to later apply a method to this data
    return [flOz](auto && method) {
        return method(flOz);
    };
};

// object instance
auto constexpr coffeeCup = createCup(12u);

// accessor for the stored parameter
auto getOz = [](auto&& aCup) {
    auto constexpr ident = [](auto x) { return x; };
    return aCup( ident );
};

auto constexpr coffee_size = getOz(coffeeCup);

int main() {
    return coffee_size;
}
