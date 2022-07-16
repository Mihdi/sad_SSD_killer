#pragma once
#ifndef MUL_VEC
#define MUL_VEC

#include <vector>

float mul_vec(std::map<int, float> *qTi, std::map<int, float> *pu)
{
    float r_ui = 0;
    auto qTi_f = qTi->begin();
    auto pu_f = pu->begin();
    while (qTi_f != qTi->end() && pu_f != pu->end())
    {
        if (qTi_f->first == pu_f->first)
        {
            r_ui += qTi_f->second * pu_f->second;
            qTi_f++;
            pu_f++;
        }
        else if (qTi_f->first > pu_f->first)
        {
            pu_f++;
        }
        else
        {
            qTi_f++;
        }
    }
    return r_ui;
};

#endif //MUL_VEC