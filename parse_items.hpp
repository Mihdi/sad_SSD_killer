#pragma once
#ifndef PARSE_ITEMS
#define PARSE_ITEMS
#include <fstream>

int parse_items(
	const char *file_str,
	std::map<std::string, Feature> *features,
	std::map<int, Item> *items
){
	//open given file
	std::ifstream file;
	file.open(file_str, std::ios::in);
	if(!file.is_open()){
		std::cout << "couldn't open file" << std::endl;
		return 1;
	}

	//SKIP FIRST LINE
	std::string line;
	std::getline(file, line);

	//init item
	auto current_item = new Item(0);

	while(std::getline(file, line)){
		//init input
		int item_id = 0;
		int feature_category_id = 0;
		int feature_value_id = 0;

		//parsing input
		const char *s = line.c_str();
		for (; *s != ','; ++s)
		{
			if('0' <= *s && *s <= '9'){
				item_id *= 10;
				item_id += *s - '0';
			}
		}
		++s;
		for (; *s != ','; ++s)
		{
			if('0' <= *s && *s <= '9'){
				feature_category_id *= 10;
				feature_category_id += *s - '0';
			}
		}
		++s;
		for (; *s != '\n' && *s != '\0'; ++s)
		{
			if('0' <= *s && *s <= '9'){
				feature_value_id *= 10;
				feature_value_id += *s - '0';
			}
		}

		//change item
		if(current_item->id != item_id){
			if(current_item->features.size() != 0){
				items->emplace(current_item->id, *current_item);
				current_item->id = item_id;
				current_item->features.clear();
			}else {
				current_item->id = item_id;
			}
		}

		//creating identifier
		std::string identifier = std::to_string(feature_category_id);
		identifier += "_";
		identifier += std::to_string(feature_value_id);

		//put features in map
		if(!features->contains(identifier)){
			features->emplace(
				std::make_pair(
					identifier,
					Feature(identifier, feature_category_id, feature_value_id)
				)
			);
		}
		current_item->features.emplace_back(&(features->find(identifier)->second));
	}
	//file is read
	file.close();

	//puting last item & getting rid of it
	if(current_item->features.size() > 0){
		items->emplace(current_item->id, *current_item);
	}
	delete current_item;
	return 0;
}

#endif //PARSE_ITEMS