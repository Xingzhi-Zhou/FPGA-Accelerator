#include "fc.h"

// #define DEBUG

#ifdef DEBUG
#include "iostream"
using namespace std;
#endif

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
//     )
// {
//     data_t t1, t2, t3, t4;
//     data_t t11, t12;
//     data_t zero = 0;
//     t1 = filter_engine_3_3(
//         w0, i0,
//         w1, i1,
//         w2, i2,
//         w3, i3,
//         w4, i4,
//         w5, i5,
//         w6, i6,
//         w7, i7,
//         w8, i8
//         );
//     t2 = filter_engine_3_3(
//         w9, i9,
//         w10, i10,
//         w11, i11,
//         w12, i12,
//         w13, i13,
//         w14, i14,
//         w15, i15,
//         w16, i16,
//         w17, i17
//         );
//     t3 = filter_engine_3_3(
//         w18, i18,
//         w19, i19,
//         w20, i20,
//         w21, i21,
//         w22, i22,
//         w23, i23,
//         w24, i24,
//         w25, i25,
//         w26, i26
//         );
//     t4 = filter_engine_3_3(
//         w27, i27,
//         w28, i28,
//         w29, i29,
//         w30, i30,
//         w31, i31,
//         zero, zero,
//         zero, zero,
//         zero, zero,
//         zero, zero
//         );
//     t11 = t1 + t2;
//     t12 = t3 + t4;
//     return t11+t12;
// }

void fc_2d_1(data_t input[C_5][H_5][W_5], str &str_in, data_t output[C_6]){
    data_t input_reshape[RC_5];
    int ti = 0;
    for(int ic=0; ic<C_5; ic++){
        for(int ih=0; ih<H_5; ih++){
            for(int iw=0; iw<W_5; iw++){
                input_reshape[ti] = input[ic][ih][iw];
                ti++;
            }
        }
    }

    bus_t str_temp;
    int i, j;
    i = 0;
    j = 0;

    // i=0
    for(j=0; j<C_6; j+=BUS_LEN){
        str_temp = str_in.read();
        for(int index=0; index<BUS_LEN; index++){
        	if((j+index)<C_6){
        		output[j+index] = input_reshape[i] * str_temp.data[index];
        	}
        }
    }

    for(i=1; i<RC_5; i++){
        for(j=0; j<C_6; j+=BUS_LEN){
            str_temp = str_in.read();
            for(int index=0; index<BUS_LEN; index++){
				if((j+index)<C_6){
					output[j+index] += input_reshape[i] * str_temp.data[index];
				}
			}
        }
    }

    // bias
    data_t temp;
    for(j=0; j<C_6; j+=BUS_LEN){
        str_temp = str_in.read();
        for(int index=0; index<BUS_LEN; index++){
			if((j+index)<C_6){
				temp = output[j+index] + str_temp.data[index];
				output[j+index] = relu(temp);
			}
		}
    }
}

void fc_2(data_t input[C_6], str &str_in, data_t output[C_7]){
    bus_t str_temp;
    int i, j;
    i = 0;
    j = 0;

    // i=0
    for(j=0; j<C_7; j+=BUS_LEN){
        str_temp = str_in.read();
        for(int index=0; index<BUS_LEN; index++){
        	if((j+index)<C_7){
        		output[j+index] = input[i] * str_temp.data[index];
        	}
        }
    }

    for(i=1; i<C_6; i++){
        for(j=0; j<C_7; j+=BUS_LEN){
            str_temp = str_in.read();
            for(int index=0; index<BUS_LEN; index++){
				if((j+index)<C_7){
					output[j+index] += input[i] * str_temp.data[index];
				}
			}
        }
    }

    // bias
    data_t temp;
    for(j=0; j<C_7; j+=BUS_LEN){
        str_temp = str_in.read();
        for(int index=0; index<BUS_LEN; index++){
			if((j+index)<C_7){
				temp = output[j+index] + str_temp.data[index];
				output[j+index] = temp;
			}
		}
    }
}
