//
// Created by bowman on 19/07/19.
//
#include <iostream>
#include <algorithm>
#include <iterator>

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
    pop_vec.emplace_back(Person("Peter", MALE));
    pop_vec.emplace_back(Person("Martha", FEMALE));
    pop_vec.emplace_back(Person("Jane", FEMALE));
    pop_vec.emplace_back(Person("David", MALE));
    pop_vec.emplace_back(Person("Rose", FEMALE));
    pop_vec.emplace_back(Person("Tom", MALE));
}


int main(int argc, char** argv) {

    std::vector<Person> bunch;
    init_population(bunch);

    std::cout << "std::partition():" << std::endl;
    std::partition(bunch.begin(), bunch.end(), [](const Person& p){ return p.is_female();} );
    for(const Person& p : bunch){
        std::cout << p.name() << std::endl;
    }

    bunch.clear();
    init_population(bunch);

    std::cout << "std::stable_partition():" << std::endl;
    std::stable_partition(bunch.begin(), bunch.end(), [](const Person& p){ return p.is_female();} );
    for(const Person& p : bunch){
        std::cout << p.name() << std::endl;
    }

    bunch.clear();
    init_population(bunch);
    bunch[3].select();

    std::cout << "Moving selected items to specific point" << std::endl;
    for(const Person& p : bunch){
        std::cout << p.name() << std::endl;
    }
    std::cout << bunch[3].name() << " selected, move to first position" << std::endl;

    auto is_selected = [](const Person& p) { return p.selected();};
    auto is_not_selected = [](const Person& p) { return !p.selected(); };

    auto destination = bunch.begin();

    std::stable_partition(bunch.begin(), destination, is_not_selected);
    std::stable_partition(destination, bunch.end(),  is_selected);

    for(const Person& p : bunch){
        std::cout << p.name() << std::endl;
    }

    return 0;
}