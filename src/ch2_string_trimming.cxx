//
// Created by bowman on 19/07/19.
//

#include <iostream>
#include <string>
#include <algorithm>

bool is_not_space(char c) {
    return !std::isspace(c);
}

std::string trim_left(std::string s) {

    s.erase(s.begin(),
            std::find_if(s.begin(), s.end(), is_not_space));
    return s;
}

std::string trim_right(std::string s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), is_not_space).base(),
            s.end());
    return s;
}

std::string trim(std::string s)
{
    return trim_left(trim_right(std::move(s)));
}


int main(int argc, char** argv) {

    std::string test_string = "    djksjka     \t";

    std::string trimmed = trim(test_string);

    std::cout << "Original string:" << std::endl << test_string << std::endl;
    std::cout << "Trimmed:" << std::endl << trimmed << std::endl;

    return 0;
}