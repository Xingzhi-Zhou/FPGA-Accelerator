/*
*   conv.h
*   Created on: 2020.09.04
*   Author: Xingzhi Zhou
*/
#ifndef __CONV_H_
#define __CONV_H_

#include "data.h"
#include "mnist.h"

data_t mul(data_t a, data_t b);
data_t filter_engine_3_3(
    data_t w0, data_t i0,
    data_t w1, data_t i1,
    data_t w2, data_t i2,
    data_t w3, data_t i3,
    data_t w4, data_t i4,
    data_t w5, data_t i5,
    data_t w6, data_t i6,
    data_t w7, data_t i7,
    data_t w8, data_t i8
    );
data_t relu(data_t a);

void conv2d_1(data_t input[C_1][H_1][W_1], str &str_in, data_t output[C_2][H_2][W_2]);

void conv2d_2(data_t input[C_3][H_3][W_3], str &str_in, data_t output[C_4][H_4][W_4]);

#endif
