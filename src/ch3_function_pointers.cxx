//
// Created by mique on 22/07/2019.
//

#include <iostream>

int ask() { return 42; }

typedef decltype(ask)* function_ptr;

class convertible_to_function_ptr {
public:
    explicit operator function_ptr() const
    {
        return ask;
    }
};

int main(int argc, char* argv[])
{
    auto ask_ptr = &ask;
    std::cout << ask_ptr() << '\n';

    auto& ask_ref = ask;
    std::cout << ask_ref() << '\n';

    convertible_to_function_ptr ask_wrapper;
    std::cout << ask_wrapper() << '\n';

    return 0;
}
