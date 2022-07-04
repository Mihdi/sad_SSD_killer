#pragma once
#ifndef FEATURE
#define FEATURE

#include <string>

struct Feature
{
	std::string identifier;
	int category;
	int feature;
	Feature(std::string identifier, int category, int feature) : 
		identifier(std::move(identifier)),
		category(category),
		feature(feature)
	{}
	~Feature(void){}
};

#endif //FEATURE