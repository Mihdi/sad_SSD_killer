#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>

#include "feature.hpp"
#include "item.hpp"
#include "parse.hpp"
#include "q_vector.hpp"
#include "mul_vec.hpp"

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
	constexpr float EPSILON = 0;

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

	auto item_28143 = items->find(28143);
	auto q_28143 = item_28143->second.convert_to_vector(features);
	auto q_vec_handler = Q_vector<EPSILON>("qs/q_");
	q_vec_handler.save(0, q_28143);

	// auto q = new std::map<int, float>;
	// auto p = new std::map<int, float>;
	// q->emplace(std::make_pair(1, 1));
	// q->emplace(std::make_pair(2, 1000));
	// q->emplace(std::make_pair(4, 10));
	// p->emplace(std::make_pair(1, 1));
	// p->emplace(std::make_pair(3, 100));
	// p->emplace(std::make_pair(4, 0.1f));


	// std::cout << mul_vec(q, p) << std::endl;

    //cleanup
	delete features;
	delete items;
	// delete p;
	// delete q;

	return 0;
}