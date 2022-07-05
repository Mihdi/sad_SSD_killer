#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>

#include "feature.hpp"
#include "item.hpp"
#include "session.hpp"
#include "parse_items.hpp"
#include "parse_sessions.hpp"
#include "mul_vec.hpp"
#include "vector_handler.hpp"

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
	if(argc < 3){
		std::cout << "please give a filename for items/features and another for sessions" << std::endl;
		return 1;
	}
	
	//prepare for parsing
	auto features = new std::map<std::string, Feature>();
	auto items = new std::unordered_map<int, Item>();
	auto sessions = new std::map<int, Session>();
	
	//actual parsing
	if(parse_items(argv[1], features, items)){ return 1; }
	if(parse_sessions(argv[2], sessions)){ return 1; }

	auto item_28143 = items->find(28143);
	auto q_28143 = item_28143->second.convert_to_vector(features);

/*	auto q_vec_handler = VectorHandler<EPSILON>("qs/q_");
	q_vec_handler.save(0, q_28143);
	std::map<int, float> q_out;
	q_vec_handler.load(0, &q_out);
*/
	auto session_19 = sessions->find(19);
	auto p_19 = session_19->second.convert_to_vector(items, features);
	auto p_vec_handler = VectorHandler<EPSILON>("ps/p_");
	p_vec_handler.save(0, p_19);

	//std::cout << mul_vec(&q_out, &q_out) << std::endl;

    //cleanup
    delete p_19;
    delete q_28143;
    delete sessions;
	delete features;
	delete items;

	return 0;
}