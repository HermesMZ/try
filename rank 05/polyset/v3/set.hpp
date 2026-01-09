#pragma once

#include "searchable_bag.hpp"

class set {
	private:
		searchable_bag *bag;
	public:
		set();
		~set();
		set(const set&);
		set& operator=(const set&);

		set(searchable_bag&);
		void insert(int);
		void insert(int*, int);
		bool has(int)const;
		void print()const;
		searchable_bag& get_bag() ;
		void clear();
};