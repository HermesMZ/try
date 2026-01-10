#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag() : array_bag() {
    // array_bag() initialise déjà tout
}

searchable_array_bag::searchable_array_bag(const searchable_array_bag &src) 
    : array_bag(src) {
    // array_bag fait la copie profonde
}

searchable_array_bag &searchable_array_bag::operator=(const searchable_array_bag &src) {
    if (this != &src) {
        array_bag::operator=(src);
    }
    return *this;
}

searchable_array_bag::~searchable_array_bag() {
    // array_bag se détruit tout seul
}

bool searchable_array_bag::has(int item) const {
    // Recherche linéaire dans le tableau
    for (int i = 0; i < size; i++) {
        if (data[i] == item) {
            return true;
        }
    }
    return false;
}
