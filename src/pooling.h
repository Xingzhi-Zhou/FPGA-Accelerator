/*
*   conv.h
*   Created on: 2020.09.04
*   Author: Xingzhi Zhou
*/
#ifndef __POOLING_H_
#define __POOLING_H_

#include "data.h"
#include "mnist.h"

data_t max_engine_2_2(data_t i0, data_t i1, data_t i2,  data_t i3);

void pooling_1(data_t input[C_2][H_2][W_2], data_t output[C_3][H_3][W_3]);

void pooling_2(data_t input[C_4][H_4][W_4], data_t output[C_5][H_5][W_5]);

#endif
