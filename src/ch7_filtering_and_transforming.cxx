//
// Created by bowman on 23/07/19.
//
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
// Notes on the deployment of ranges
// https://stackoverflow.com/a/56118997/338107
// this code is using ericniebler/range-v3 implementation.
#include <range/v3/all.hpp>
#include <chrono>
#include <ctime>

enum Gender{
    MALE, FEMALE, OTHER
};

class Person {

private:
    //attributes
    std::string     _name;
    Gender          _gender;
    bool            _selected;

public:
    Person(std::string name, Gender g)
            : _name(std::move(name)), _gender(g), _selected(false) {
    }

    bool is_female() const {
        return _gender == Gender::FEMALE;
    }

    std::string name() const {
        return _name;
    }

    bool selected() const {
        return _selected;
    }

    void select() { _selected = true; }
    void deselect() { _selected = false; }
};

void init_population(std::vector<Person>& pop_vec) {
    pop_vec.emplace_back(Person("Peter", Gender::MALE));
    pop_vec.emplace_back(Person("Martha", Gender::FEMALE));
    pop_vec.emplace_back(Person("Jane", Gender::FEMALE));
    pop_vec.emplace_back(Person("David", Gender::MALE));
    pop_vec.emplace_back(Person("Rose", Gender::FEMALE));
    pop_vec.emplace_back(Person("Tom", Gender::MALE));
}


int main(int argc, char** argv) {

    using namespace ranges;

    auto is_female = [](const Person& p) { return p.is_female(); };
    auto is_not_female = [](const Person& p) { return !p.is_female(); };
    auto name = [](const Person& p) { return p.name(); };

    std::vector<Person> bunch;
    init_population(bunch);


    std::cout << "ranges filter | transform" << std::endl;
    auto t0 = std::chrono::system_clock::now();
    std::vector<std::string> names;
    /*
    names =
            view::transform(
                    view::filter(bunch, is_female),
                    name);
    */
    names =
            bunch | view::filter(is_female) | view::transform(name);
    auto tf = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = tf - t0;
    std::time_t end_time = std::chrono::system_clock::to_time_t(tf);

    std::cout << "Finished computation at " << std::ctime(&end_time)
              << " elapsed time: " << elapsed.count() << "s\n";

    // collected names
    std::cout << "Collected names" << std::endl;
    for (const auto& n: names)
        std::cout << n << std::endl;

    bunch.clear();
    init_population(bunch);

    std::cout << "Old style" << std::endl;
    std::vector<std::string> names2;
    t0 = std::chrono::system_clock::now();
    {
        std::vector<Person> females;
        std::copy_if(bunch.cbegin(), bunch.cend(),
                     std::back_inserter(females),
                     is_female);

        // getting the names
        names2.resize(females.size());

        std::transform(females.cbegin(), females.cend(),
                       names2.begin(),
                       name);
    }
    tf = std::chrono::system_clock::now();
    elapsed = tf - t0;
    end_time = std::chrono::system_clock::to_time_t(tf);

    std::cout << "Finished computation at " << std::ctime(&end_time)
              << " elapsed time: " << elapsed.count() << "s\n";

    // collected names
    std::cout << "Collected names" << std::endl;
    for (const auto& n: names2)
        std::cout << n << std::endl;
    return 0;
}