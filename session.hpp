#pragma once
#ifndef SESSION
#define SESSION

#include <vector>

struct Session {
	int id;
	std::vector<int> item_ids;

	Session() : id(0){}
	std::map<int, float> *convert_to_vector(
		std::unordered_map<int, Item> *items,
		std::map<std::string, Feature> *feature_map
	){

		auto out = new std::map<int, float>();

		for (auto item_id = this->item_ids.begin(); item_id != this->item_ids.end(); ++item_id)
		{
			auto current_item = items->find(*item_id);
			auto current_item_as_vector = current_item->second.convert_to_vector(feature_map);

			for (
				auto feature = current_item_as_vector->begin();
				feature != current_item_as_vector->end();
				++feature
			){
				const auto feature_id = feature->first;
				const auto feature_value = feature->second;

				if(out->contains(feature_id)){
					out->find(feature_id)->second += feature_value;
				} else {
					out->emplace(std::make_pair(feature_id, feature_value));
				}
			}

			delete current_item_as_vector;
		}

		return out;
	}
};

#endif //SESSION