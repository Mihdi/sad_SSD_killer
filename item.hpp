#pragma once
#ifndef ITEM
#define ITEM

#include <string>
#include <map>

#include "feature.hpp"

struct Item {
	int id;
	std::vector<Feature *> features;

	Item(int id) : id(id) {}
	void convert_to_vector(std::map<int, float>& out){
		
	}
};

#endif //ITEM