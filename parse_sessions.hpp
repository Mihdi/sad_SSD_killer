#pragma once
#ifndef PARSE_SESSIONS
#define PARSE_SESSIONS

#include <fstream>
#include <map>

#include "session.hpp"

int parse_sessions(
	const char *file_str,
	std::map<int, Session> *out
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

	auto current_session = new Session();

	while(std::getline(file, line)){
		int id = 0;
		int item_id = 0;

		//parsing input
		const char *s = line.c_str();
		for (; *s != ','; ++s)
		{
			if('0' <= *s && *s <= '9'){
				id *= 10;
				id += *s - '0';
			}
		}
		++s;
		for (; *s != ','; ++s)
		{
			if('0' <= *s && *s <= '9'){
				item_id *= 10;
				item_id += *s - '0';
			}
		}
		++s;

		if(current_session->id != id){
			if(current_session->item_ids.size() > 0){
				out->emplace(std::make_pair(current_session->id, *current_session));
				current_session->item_ids.clear();
			}
			current_session->id = id;
		}
		
		current_session->item_ids.emplace_back(item_id);
	}
	if(current_session->item_ids.size() > 0){
		out->emplace(std::make_pair(current_session->id, *current_session));
	}
	delete current_session;
	file.close();
	return 0;
}

#endif // PARSE_SESSIONS