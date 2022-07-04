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
		std::ofstream file;
		file.open(path + std::to_string(index), std::ios::out | std::ios::trunc);
		if(!file.is_open()){
			std::cout << "error, could not open file in Q_vector.save" << std::endl;
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

	void load(int q_index, std::map<int, float> *q_out){
		//open file
		std::ifstream file;
		file.open(path + std::to_string(q_index), std::ios::in);
		if(!file.is_open()){
			std::cout << "error, could not open file in Q_vector.load" << std::endl;
			::exit(1);
		}

		//read file
		std::string line;
		std::getline(file, line);

		//parse
		float value = 0;
		float decimal = 0;
		int decimal_divider = 1;
		int index = 0;
		bool parsing_value = true;
		bool parsing_decimal = false;
		bool parsing_index = false; //yeah we could do without this one, but I'm tired and need the explicit-ness
		for (const char *c = line.c_str(); *c != '\0' && *c != '\n'; ++c)
		{
			const char current_char = *c;
			if(*c == '$'){
				if(parsing_value){
					q_out->emplace(std::make_pair(index, value));
					value = 0;
				} else if(parsing_decimal) {
					value += decimal * decimal_divider;
					q_out->emplace(std::make_pair(index, value));
					value = 0;
					decimal = 0;
					decimal_divider = 1;
				}
				index = 0;
				parsing_index = true;
				continue;
			}

			if(*c == ' '){
				if(parsing_value){
					q_out->emplace(std::make_pair(index, value));
					value = 0;
					index += 1;
				} else if(parsing_decimal){
					value += decimal * decimal_divider;
					q_out->emplace(std::make_pair(index, value));
					value = 0;
					decimal = 0;
					decimal_divider = 1;
					index += 1;
				} else if(parsing_index){
					parsing_index = false;
					parsing_value = true;
				}
				continue;
			}

			if(*c == '.' && parsing_value){
				parsing_value = false;
				parsing_decimal = true;
				decimal = 0;
				decimal_divider = 1;
				continue;
			}

			if('0' <= current_char && current_char <= '9'){
				auto current_value = current_char - '0';
				if (parsing_value){
					value *= 10;
					value += current_value;
				} else if (parsing_decimal){
					decimal *= 10;
					decimal += current_value;
					decimal_divider *= 10;
				} else if (parsing_index) {
					index *= 10;
					index += current_value;
				}
			}
		}

		//cleanup
		file.close();
	}
	~Q_vector(){}
};

#endif //Q_VECTOR