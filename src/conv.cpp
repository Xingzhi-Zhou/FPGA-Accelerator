#include "conv.h"

data_t mul(data_t a, data_t b){
	return a*b;
}

data_t relu(data_t a){
    if(a>=0){
        return a;
    }
    else{
        return 0;
    }
}

// data_t filter_engine_3_3(
//     data_t w0, data_t i0,
//     data_t w1, data_t i1,
//     data_t w2, data_t i2,
//     data_t w3, data_t i3,
//     data_t w4, data_t i4,
//     data_t w5, data_t i5,
//     data_t w6, data_t i6,
//     data_t w7, data_t i7,
//     data_t w8, data_t i8
//     )
// {
//     data_t mul0, mul1, mul2, mul3, mul4, mul5, mul6, mul7, mul8;
//     data_t add00, add01, add02, add03;
//     data_t add0, add1;

//     mul6 = w6*i6;
//     mul7 = w7*i7;
//     mul8 = w8*i8;
//     mul0 = w0*i0;
//     mul1 = w1*i1;
//     mul2 = w2*i2;
//     mul3 = w3*i3;
//     mul4 = w4*i4;
//     mul5 = w5*i5;


//     add00 = mul0+mul1;
//     add01 = mul2+mul3;
//     add02 = mul4+mul5;
//     add03 = mul6+mul7+mul8;

//     add0 = add00+add01;
//     add1 = add02+add03;

//     return add0+add1;
// }

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
    )
{
    data_t mul0, mul1, mul2, mul3, mul4, mul5, mul6, mul7, mul8;
    data_t add00, add01, add02, add03;
    data_t add0, add1;

    mul6 = mul(w6, i6);
    mul7 = mul(w7, i7);
    mul8 = mul(w8, i8);
    mul0 = mul(w0, i0);
    mul1 = mul(w1, i1);
    mul2 = mul(w2, i2);
    mul3 = mul(w3, i3);
    mul4 = mul(w4, i4);
    mul5 = mul(w5, i5);


    add00 = mul0+mul1;
    add01 = mul2+mul3;
    add02 = mul4+mul5;
    add03 = mul6+mul7+mul8;

    add0 = add00+add01;
    add1 = add02+add03;

    return add0+add1;
}

void conv2d_1(data_t input[C_1][H_1][W_1], str &str_in, data_t output[C_2][H_2][W_2]){
    data_t acc = 0;
    data_t zero = 0;
    bus_t str_temp;

    data_t weight[C_2][C_1][9];
    data_t bias[C_2];
    // load weight and bias
    for(int i=0; i<C_2; i+=3){
        str_temp = str_in.read();
        for(int j=0; j<9; j++){
            weight[i][0][j] = str_temp.data[j];
            weight[i+1][0][j] = str_temp.data[j+9];
            weight[i+2][0][j] = str_temp.data[j+18];
        }
    }
    str_temp = str_in.read();
    for(int j=0; j<C_2; j++){
        bias[j] = str_temp.data[j];
    }

    // with padding
    LOOP_OC: for(int oc=0; oc<C_2; oc++){
        LOOP_OH: for(int oh=0; oh<H_2; oh++){
            LOOP_OW: for(int ow=0; ow<W_2; ow++){
                acc = 0;
                LOOP_IC: for(int ic=0; ic<C_1; ic++){
                    acc += filter_engine_3_3(
                        weight[oc][ic][0], (((oh-K_2)>=0 && (ow-K_2)>=0) ? input[ic][oh-K_2][ow-K_2] : zero),
                        weight[oc][ic][1], (((oh-K_2)>=0) ? input[ic][oh-K_2][ow] : zero),
                        weight[oc][ic][2], (((oh-K_2)>=0 && (ow+K_2)<W_1) ? input[ic][oh-K_2][ow+K_2] : zero),
                        weight[oc][ic][3], (((ow-K_2)>=0) ? input[ic][oh][ow-K_2] : zero),
                        weight[oc][ic][4], input[ic][oh][ow],
                        weight[oc][ic][5], (((ow+K_2)<W_1) ? input[ic][oh][ow+K_2] : zero),
                        weight[oc][ic][6], (((oh+K_2)<H_1 && (ow-K_2)>=0) ? input[ic][oh+K_2][ow-K_2] : zero),
                        weight[oc][ic][7], (((oh+K_2)<H_1) ? input[ic][oh+K_2][ow] : zero),
                        weight[oc][ic][8], (((oh+K_2)<H_1 && (ow+K_2)<W_1) ? input[ic][oh+K_2][ow+K_2] : zero)
                        );
                }
                output[oc][oh][ow] = relu(acc + bias[oc]);
            }
        }
    }
}

void conv2d_2(data_t input[C_3][H_3][W_3], str &str_in, data_t output[C_4][H_4][W_4]){
    data_t acc = 0;
    data_t zero = 0;
    bus_t str_temp;

    data_t weight[C_4][C_3][9];
    data_t bias[C_4];
    // load weight and bias
    for(int i=0; i<C_4; i++){
        for(int t=0; t<C_3; t+=3){
            str_temp = str_in.read();
            for(int j=0; j<9; j++){
                weight[i][t][j] = str_temp.data[j];
                weight[i][t+1][j] = str_temp.data[j+9];
                weight[i][t+2][j] = str_temp.data[j+18];
            }
        }
    }
    str_temp = str_in.read();
    for(int j=0; j<C_4; j++){
        bias[j] = str_temp.data[j];
    }

    // with padding
    LOOP_OC: for(int oc=0; oc<C_4; oc++){
        LOOP_OH: for(int oh=0; oh<H_4; oh++){
            LOOP_OW: for(int ow=0; ow<W_4; ow++){
                acc = 0;
                LOOP_IC: for(int ic=0; ic<C_3; ic++){
                    acc += filter_engine_3_3(
                        weight[oc][ic][0], (((oh-K_4)>=0 && (ow-K_4)>=0) ? input[ic][oh-K_4][ow-K_4] : zero),
                        weight[oc][ic][1], (((oh-K_4)>=0) ? input[ic][oh-K_4][ow] : zero),
                        weight[oc][ic][2], (((oh-K_4)>=0 && (ow+K_4)<W_3) ? input[ic][oh-K_4][ow+K_4] : zero),
                        weight[oc][ic][3], (((ow-K_4)>=0) ? input[ic][oh][ow-K_4] : zero),
                        weight[oc][ic][4], input[ic][oh][ow],
                        weight[oc][ic][5], (((ow+K_4)<W_3) ? input[ic][oh][ow+K_4] : zero),
                        weight[oc][ic][6], (((oh+K_4)<H_3 && (ow-K_4)>=0) ? input[ic][oh+K_4][ow-K_4] : zero),
                        weight[oc][ic][7], (((oh+K_4)<H_3) ? input[ic][oh+K_2][ow] : zero),
                        weight[oc][ic][8], (((oh+K_4)<H_3 && (ow+K_4)<W_3) ? input[ic][oh+K_4][ow+K_4] : zero)
                        );
                }
                output[oc][oh][ow] = relu(acc + bias[oc]);
            }
        }
    }
}
