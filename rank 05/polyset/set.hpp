#pragma once

#include "searchable_bag.hpp"

class set {
private:
    searchable_bag *bag_ptr;
    
public:
    // Forme canonique orthodoxe
    set(searchable_bag &);
    set(const set &);
    set &operator=(const set &);
    ~set();
    
    // Méthodes du set
    void insert(int);
    void insert(int *, int);
    bool has(int) const;
    void print() const;
    void clear();
    
    // Accesseur
    searchable_bag &get_bag() const;
};