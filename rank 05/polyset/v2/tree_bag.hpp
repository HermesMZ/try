/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_bag.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:21:12 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/06 17:21:13 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "bag.hpp"

class tree_bag : virtual public bag {
protected:
  struct node {
    node *l;
    node *r;
    int value;
  };
  node *tree;

public:
  tree_bag();
  tree_bag(const tree_bag &);
  tree_bag  &operator=(const tree_bag &);
  ~tree_bag();

  node *extract_tree();
  void set_tree(node *);

  virtual void insert(int);
  virtual void insert(int *array, int size);
  virtual void print() const;
  virtual void clear();

private:
  static void destroy_tree(node *);
  static void print_node(node *);
  node *copy_node(node *);
};
