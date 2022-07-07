#pragma once
#ifndef COMPUTE_R
#define COMPUTE_R

#include "mul_vec.hpp"
#include "vector_handler.hpp"

template<float EPSILON>
void compute_r(
	VectorHandler<EPSILON> *q_vec, size_t nb_qs,
	VectorHandler<EPSILON> *p_vec, size_t nb_ps,
	VectorHandler<EPSILON> *r_vec, size_t &nb_rs
){
	auto current_r = std::map<int, float>();
	auto current_q = std::map<int, float>();
	auto current_p = std::map<int, float>();

	for (size_t q_index = 0; q_index < nb_qs; ++q_index)
	{
		current_r.clear();
		current_q.clear();

		q_vec->load(q_index, &current_q);

		const int r_row_index = q_index;

		for(size_t p_index = 0; p_index < nb_ps; ++p_index){
			current_p.clear();
			p_vec->load(p_index, &current_p);

			float r = mul_vec(&current_q, &current_p);
			const int r_col_index = p_index;
			current_r.emplace(std::make_pair(r_col_index, r));
		}

		++nb_rs;
		r_vec->save(r_row_index, &current_r);
	}
}

template<float EPSILON>
bool test_compute_r(void){
	auto q_vec = VectorHandler<EPSILON>("test_qs");
	auto p_vec = VectorHandler<EPSILON>("test_ps");
	auto r_vec = VectorHandler<EPSILON>("test_rs");
	
	size_t nb_qs = 4;
	size_t nb_ps = 3;
	size_t nb_rs = 0;

	auto robe = std::map<int, float>();
	robe.emplace(std::make_pair(0, 1));
	robe.emplace(std::make_pair(1, 1));
	robe.emplace(std::make_pair(4, 1));
	robe.emplace(std::make_pair(5, 1));
	q_vec.save(0, &robe);

	auto pull = std::map<int, float>();
	pull.emplace(std::make_pair(1, 1));
	pull.emplace(std::make_pair(2, 1));
	pull.emplace(std::make_pair(3, 1));
	pull.emplace(std::make_pair(4, 1));
	q_vec.save(1, &pull);

	auto t_shirt = std::map<int, float>();
	t_shirt.emplace(std::make_pair(0, 1));
	t_shirt.emplace(std::make_pair(1, 1));
	t_shirt.emplace(std::make_pair(2, 1));
	t_shirt.emplace(std::make_pair(3, 1));
	t_shirt.emplace(std::make_pair(4, 1));
	t_shirt.emplace(std::make_pair(5, 1));
	q_vec.save(2, &t_shirt);

	auto chapeau = std::map<int, float>();
	chapeau.emplace(std::make_pair(0, 1));
	chapeau.emplace(std::make_pair(1, 1));
	chapeau.emplace(std::make_pair(2, 1));
	chapeau.emplace(std::make_pair(4, 1));
	q_vec.save(3, &chapeau);

	auto tom = std::map<int, float>();
	tom.emplace(std::make_pair(0, 3));
	tom.emplace(std::make_pair(1, 3));
	tom.emplace(std::make_pair(2, 2));
	tom.emplace(std::make_pair(3, 1));
	tom.emplace(std::make_pair(4, 3));
	tom.emplace(std::make_pair(5, 2));
	p_vec.save(0, &tom);

	auto alice = std::map<int, float>();
	alice.emplace(std::make_pair(0, 2));
	alice.emplace(std::make_pair(1, 2));
	alice.emplace(std::make_pair(2, 1));
	alice.emplace(std::make_pair(4, 2));
	alice.emplace(std::make_pair(5, 1));
	p_vec.save(1, &alice);

	auto bob = std::map<int, float>();
	bob.emplace(std::make_pair(0, 1));
	bob.emplace(std::make_pair(1, 2));
	bob.emplace(std::make_pair(2, 2));
	bob.emplace(std::make_pair(3, 2));
	bob.emplace(std::make_pair(4, 2));
	bob.emplace(std::make_pair(5, 1));
	p_vec.save(2, &bob);

	compute_r(
		&q_vec, nb_qs,
		&p_vec, nb_ps,
		&r_vec, nb_rs
	);

	std::cout << "nb_rs = " << nb_rs << std::endl;

	return true;
}

#endif //COMPUTE_R