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
			file << 'i' << index;
			file << 'v' << component_value;
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
		bool encountered_value = false;
		float value = 0;
		int decimal = 0;
		double decimal_divider = 1;
		int index = 0;
		bool parsing_value = true;
		bool parsing_decimal = false;
		bool parsing_index = false; //yeah we could do without this one, but I'm tired and need the explicit-ness
		
		for (const char *c = line.c_str(); *c != '\0' && *c != '\n'; ++c)
		{
			const char current_char = *c;
			if(*c == 'i'){
				parsing_index = true;
				parsing_value = parsing_decimal = false;

				if(!encountered_value){
					encountered_value = true;
				} else {
					float component = decimal / decimal_divider;
					component += value;
					q_out->emplace(std::make_pair(index, value));
				}
				index = 0;
				value = 0;
				continue;
			}
			if(*c == 'v'){
				parsing_value = true;
				parsing_index = parsing_decimal = false;
				continue;
			}

			if(*c == '.'){
				parsing_decimal = true;
				parsing_value = parsing_index = false;
				continue;	
			}

			auto current_digit = current_char - '0';
			if(parsing_value){
				value *= 10;
				value += current_digit;
			} else if(parsing_decimal){
				decimal *= 10;
				decimal += current_digit;
				decimal_divider *= 10;
			} else if(parsing_index){
				index *= 10;
				index += current_digit;
			}
		}
		q_out->emplace(std::make_pair(index, value + decimal / decimal_divider));

		//cleanup
		file.close();
	}
	~Q_vector(){}
};

#endif //Q_VECTOR