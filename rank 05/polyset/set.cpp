#include "set.hpp"

set::set(searchable_bag &b) {
    bag_ptr = &b;
}

set::set(const set &src) {
    bag_ptr = src.bag_ptr;
}

set &set::operator=(const set &src) {
    if (this != &src) {
        bag_ptr = src.bag_ptr;
    }
    return *this;
}

set::~set() {
    // On ne détruit PAS le bag - on ne le possède pas
}

void set::insert(int item) {
    // Vérifier d'abord si l'élément existe déjà
    if (!bag_ptr->has(item)) {
        bag_ptr->insert(item);
    }
}

void set::insert(int *items, int count) {
    for (int i = 0; i < count; i++) {
        insert(items[i]);  // Utilise la version qui vérifie les doublons
    }
}

bool set::has(int item) const {
    return bag_ptr->has(item);
}

void set::print() const {
    bag_ptr->print();
}

void set::clear() {
    bag_ptr->clear();
}

searchable_bag &set::get_bag() const {
    return *bag_ptr;
}