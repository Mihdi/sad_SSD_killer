#pragma once
#ifndef Q_VECTOR
#define Q_VECTOR
#include <string>
#include <fstream>
#include <vector>

template<float EPSILON>
class Q_vector
{
private:
	static constexpr float LOWER_BOUND = -1 * EPSILON;
	static constexpr float UPPER_BOUND = +1 * EPSILON;

	std::string path;
public:
	Q_vector(std::string path) :  path(std::move(path)){}

	void save(int index, const std::map<int, float> *qvec){
		std::fstream file;
		file.open(path + std::to_string(index), std::ios::out | std::ios::trunc);
		if(!file.is_open()){
			std::cout << "error, could not open file in Q_vector" << std::endl;
			::exit(1);
		}
		bool skip_mode = false;
		int prev = 0;
		for (auto q_i = qvec->begin(); q_i != qvec->end(); q_i++)
		{
			const int index = q_i->first;
			const float component_value = q_i->second;

			if(index != (prev + 1)){ // be careful, I'm assuming no duplicates in qvec
				file << " $ ";
				skip_mode = true;
			}

			if(LOWER_BOUND < component_value && component_value < UPPER_BOUND){
				if(!skip_mode){
					file << " $ ";
					skip_mode = true;
				}
				continue;
			}

			if(skip_mode){
				file << index;
				file << ' ';
				skip_mode = false;
			}

			file << component_value;
			file << ' ';
			prev = index;
		}
		file << '\n';
		file.close();
	}
	~Q_vector(){}
};

#endif //Q_VECTOR