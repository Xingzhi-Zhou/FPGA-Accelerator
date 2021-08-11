/*
*   conv.h
*   Created on: 2020.09.04
*   Author: Xingzhi Zhou
*/
#ifndef __FC_H_
#define __FC_H_

#include "data.h"
#include "conv.h"

// data_t fc_engine(
//     data_t w0, data_t i0,
//     data_t w1, data_t i1,
//     data_t w2, data_t i2,
//     data_t w3, data_t i3,
//     data_t w4, data_t i4,
//     data_t w5, data_t i5,
//     data_t w6, data_t i6,
//     data_t w7, data_t i7,
//     data_t w8, data_t i8,
//     data_t w9, data_t i9,
//     data_t w10, data_t i10,
//     data_t w11, data_t i11,
//     data_t w12, data_t i12,
//     data_t w13, data_t i13,
//     data_t w14, data_t i14,
//     data_t w15, data_t i15,
//     data_t w16, data_t i16,
//     data_t w17, data_t i17,
//     data_t w18, data_t i18,
//     data_t w19, data_t i19,
//     data_t w20, data_t i20,
//     data_t w21, data_t i21,
//     data_t w22, data_t i22,
//     data_t w23, data_t i23,
//     data_t w24, data_t i24,
//     data_t w25, data_t i25,
//     data_t w26, data_t i26,
//     data_t w27, data_t i27,
//     data_t w28, data_t i28,
//     data_t w29, data_t i29,
//     data_t w30, data_t i30,
//     data_t w31, data_t i31
//     );

void fc_2d_1(data_t input[C_5][H_5][W_5], str &str_in, data_t output[C_6]);

void fc_2(data_t input[C_6], str &str_in, data_t output[C_7]);


#endif
