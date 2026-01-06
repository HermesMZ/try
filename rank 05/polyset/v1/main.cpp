#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "set.hpp"
#include <cstdlib>

#include <iostream>

int main(int argc, char **argv) {
  if (argc == 1)
    return 1;
  searchable_bag *t = new searchable_tree_bag;
  searchable_bag *a = new searchable_array_bag;

  for (int i = 1; i < argc; i++) {
    t->insert(atoi(argv[i]));
    a->insert(atoi(argv[i]));
  }
  t->print();
  a->print();

  for (int i = 1; i < argc; i++) {
    std::cout << t->has(atoi(argv[i])) << std::endl;
    std::cout << a->has(atoi(argv[i])) << std::endl;
    std::cout << t->has(atoi(argv[i]) - 1) << std::endl;
    std::cout << a->has(atoi(argv[i]) - 1) << std::endl;
  }

  t->clear();
  a->clear();

  const searchable_array_bag tmp(static_cast<searchable_array_bag &>(*a));
  tmp.print();
  tmp.has(1);

  set sa(*a);
  set st(*t);
  for (int i = 1; i < argc; i++) {
    st.insert(atoi(argv[i]));
    sa.insert(atoi(argv[i]));

    sa.has(atoi(argv[i]));
    sa.print();
    sa.get_bag().print();
    st.print();
    sa.clear();
    sa.insert(
        (int[]){
            1,
            2,
            3,
            4,
        },
        4);
    std::cout << std::endl;
  }

  // Après les tests existants, avant return 0:

std::cout << "\n=== Tests SET avec doublons 5 5 3 5 7 ===" << std::endl;
a->clear();
set test_set(*a);
test_set.insert(5);
test_set.insert(5);  // doublon
test_set.insert(3);
test_set.insert(5);  // doublon
test_set.insert(7);
test_set.print();  // devrait afficher: 3 5 7

std::cout << "\n=== Test constructeur de copie ===" << std::endl;
set copy_set(test_set);
copy_set.print();  // devrait être identique

std::cout << "\n=== Test opérateur d'affectation ===" << std::endl;
set assigned_set(*t);
assigned_set = test_set;
assigned_set.print();

std::cout << "\n=== Test has() sur set ===" << std::endl;
std::cout << "has(5): " << test_set.has(5) << std::endl;  // 1
std::cout << "has(99): " << test_set.has(99) << std::endl;  // 0

std::cout << "\n=== Test insert tableau ===" << std::endl;
set array_test(*a);
int vals[] = {10, 20, 10, 30, 20};
array_test.insert(vals, 5);
array_test.print();  // devrait afficher: 10 20 30

// Cleanup
delete t;
delete a;
  return 0;
}
