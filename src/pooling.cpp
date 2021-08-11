#include "pooling.h"

// #define DEBUG

#ifdef DEBUG
#include "iostream"
using namespace std;
#endif

data_t max_engine_2_2(data_t i0, data_t i1, data_t i2,  data_t i3){
    data_t temp0, temp1, temp2;

    temp0 = (i0<i1)? i1 : i0;
    temp1 = (i2<i3)? i3 : i2;

    temp2 = (temp0<temp1)? temp1 : temp0;

    return temp2;
}

void pooling_1(data_t input[C_2][H_2][W_2], data_t output[C_3][H_3][W_3]){
    int ih, iw;
    LOOP_OC: for(int oc=0; oc<C_3; oc++){
        ih = 0;
    	LOOP_OH: for(int oh=0; oh<H_3; oh++){
            iw = 0;
    		LOOP_OW: for(int ow=0; ow<W_3; ow++){
                output[oc][oh][ow] = max_engine_2_2(
                        input[oc][ih][iw], input[oc][ih][iw+1],
                        input[oc][ih+1][iw], input[oc][ih+1][iw+1] 
                    );
                iw += 2;
            }
            ih += 2;
        }
    }
}

void pooling_2(data_t input[C_4][H_4][W_4], data_t output[C_5][H_5][W_5]){
    int ih, iw;
    LOOP_OC: for(int oc=0; oc<C_5; oc++){
        ih = 0;
    	LOOP_OH: for(int oh=0; oh<H_5; oh++){
            iw = 0;
    		LOOP_OW: for(int ow=0; ow<W_5; ow++){
                output[oc][oh][ow] = max_engine_2_2(
                        input[oc][ih][iw], input[oc][ih][iw+1],
                        input[oc][ih+1][iw], input[oc][ih+1][iw+1] 
                    );
                iw += 2;
            }
            ih += 2;
        }
    }
}

