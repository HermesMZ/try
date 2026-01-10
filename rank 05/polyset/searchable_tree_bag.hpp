#pragma once

#include "tree_bag.hpp"
#include "searchable_bag.hpp"

class searchable_tree_bag : public tree_bag, public searchable_bag {
public:
    // Forme canonique orthodoxe
    searchable_tree_bag();
    searchable_tree_bag(const searchable_tree_bag &);
    searchable_tree_bag &operator=(const searchable_tree_bag &);
    ~searchable_tree_bag();
    
    // Implémentation de searchable_bag
    virtual bool has(int) const;
};