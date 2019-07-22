//
// Created by bowman on 19/07/19.
//

//
// Created by bowman on 19/07/19.
//
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>

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
            : _name(name), _gender(g), _selected(false) {
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

    auto is_female = [](const Person& p) { return p.is_female(); };
    auto is_not_female = [](const Person& p) { return !p.is_female(); };
    auto name = [](const Person& p) { return p.name(); };

    std::vector<Person> bunch;
    init_population(bunch);

    // remove non-female persons from bunch
    bunch.erase(std::remove_if(bunch.begin(), bunch.end(), is_not_female), bunch.end());

    std::cout << "Removed non females" << std::endl;
    for (const Person& p: bunch)
        std::cout << p.name() << std::endl;

    // no modification of original
    bunch.clear();
    init_population(bunch);

    std::vector<Person> females;
    std::copy_if(bunch.cbegin(), bunch.cend(),
            std::back_inserter(females),
            is_female);

    std::cout << "Filtered females" << std::endl;
    for (const Person& p: females)
        std::cout << p.name() << std::endl;

    // getting the names
    std::vector<std::string> names(females.size());

    std::transform(females.cbegin(), females.cend(),
            names.begin(),
            name);

    // collected names
    std::cout << "Collected names" << std::endl;
    for (const auto& n: names)
        std::cout << n << std::endl;

    return 0;
}