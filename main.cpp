#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>

#include "feature.hpp"
#include "item.hpp"
#include "parse.hpp"
#include "q_vector.hpp"

void print_items(std::map<int, Item> *items){
	for (auto i = items->begin(); i != items->end(); ++i)
	{
		std::cout << i->second.id << std::endl;
		for (auto j = i->second.features.begin(); j != i->second.features.end(); ++j)
		{
			std::cout << "\t" << (*j)->identifier << std::endl;
		}
	}
}

int main(int argc, char const *argv[])
{
	//try checking if given file
	if(argc < 2){
		std::cout << "please give a filename" << std::endl;
		return 1;
	}
	
	//prepare for parsing
	auto features = new std::map<std::string, Feature>();
	auto items = new std::unordered_map<int, Item>();
	
	//actual parsing
	if(parse(argv[1], features, items)){ return 1; }

    //cleanup
	delete features;
	delete items;

	return 0;
}