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
	std::map<int, float> *convert_to_vector(std::map<std::string, Feature> *feature_map){
		auto out = new std::map<int, float>();
		for (auto feature = this->features.begin(); feature != this->features.end(); ++feature)
		{
			//no indexes on a map, instead we get an abstraction of a pointer... which we can haxx to be an index >:)
			int index = std::distance(feature_map->begin(), feature_map->find((*feature)->identifier));
			out->emplace(std::make_pair(index, 1));
		}
		return out;
	}
};

#endif //ITEM