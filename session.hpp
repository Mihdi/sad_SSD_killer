#pragma once
#ifndef SESSION
#define SESSION

#include <vector>

struct Session {
	int id;
	std::vector<int> item_ids;

	Session() : id(0){}
};

#endif //SESSION