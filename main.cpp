// using closures to simulate objects, and do compile time operations

#include <functional>
#include <iostream>

// object constructor
auto const createCup = [](int flOz) {
    // return a closure that captures the input data
    // and also allows us to apply a method to it
    return [flOz](auto && method) {
        return method(flOz);
    };
};

// object instance
auto constexpr coffeeCup = createCup(12);

// access the stored parameter in the closure
auto const getOz = [](auto aCup) -> int {
    return aCup( std::identity{} );
};

// operations
auto const drink = [](auto aCup, auto flOz_drank){
    auto const flOz_cup = getOz(aCup) ;
    int const flOz_diff = flOz_cup - flOz_drank;
    int const remaining = std::max( 0, flOz_diff);
    return createCup( remaining );
};

int constexpr full_coffee_size = getOz(coffeeCup);
int constexpr after_sip_size = getOz(drink( coffeeCup, 2));


// something with more state
using RobotState = std::tuple<const char*, int, int>;

auto const create_robot= [](RobotState state) {
    return [state](auto && method) {
        return method(state);
    };
};

auto const get_robot_name = [](auto a_robot){
    auto const name = [](RobotState x) { return std::get<0>(x); };
    return a_robot(name);
};

auto const set_robot_name = [](auto a_robot, const char* new_name){
    auto const [name, hp, attack] = a_robot(std::identity{});
    return create_robot({new_name, hp, attack});
};

auto const get_robot_hp = [](auto a_robot){
    auto const robot_hp = [](RobotState x) { return std::get<1>(x); };
    return a_robot(robot_hp);
};

auto const set_robot_hp = [](auto a_robot, int new_hp){
    auto const [name, hp, attack] = a_robot(std::identity{});
    return create_robot({name, new_hp, attack});
};

auto const get_robot_attack= [](auto a_robot){
    auto const robot_attack = [](RobotState x) { return std::get<2>(x); };
    return a_robot(robot_attack);
};

auto const set_robot_attack = [](auto a_robot, int new_attack){
    auto const [name, hp, attack] = a_robot(std::identity{});
    return create_robot({name, hp, new_attack});
};

auto const show_robot =  []( auto a_robot) -> std::string {
    auto const [name, hp, attack] = a_robot(std::identity{});
    return "name : " + std::string{name} + ", hp : " + std::to_string(hp)  + ", attack : "  + std::to_string(attack);
};

auto constexpr killer_robot = create_robot({"killer", 42, 2});
auto constexpr another_killer = set_robot_name(killer_robot, "another_killer");
auto constexpr killer_hp = get_robot_hp(another_killer);

int main() {
    std::cout << "full coffee " << full_coffee_size << std::endl;
    std::cout << "after sip " << after_sip_size << std::endl;

    std::cout << "another killer robot hp " << killer_hp << std::endl;
    std::cout << "original kill -> " << show_robot(killer_robot) << std::endl;
}
