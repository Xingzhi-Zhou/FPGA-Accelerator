#include "layer.h"

#ifdef DEBUG
#include <iostream>
using namespace std;
#endif

void pe(stream_t &a_pre, stream_t &b_pre, stream_t &a_nxt, stream_t &b_nxt, data_t *c){
    data_t a_tmp, b_tmp;
    
    K_LOOP:
    for(int k=0; k<PE_K; k++){
#pragma HLS PIPELINE
        a_pre >> a_tmp;
        b_pre >> b_tmp;

        *c += a_tmp * b_tmp;

        a_nxt << a_tmp;
        b_nxt << b_tmp;
    }

}

void load_a(int m, data_t a[PE_M][PE_K], stream_t &a_nxt){
    for(int k=0; k<PE_K; k++){
        a_nxt << a[m][k];
    }
}

void load_b(int n, data_t b[PE_K][PE_N], stream_t &b_nxt){
    for(int k=0; k<PE_K; k++){
        b_nxt << b[k][n];
    }
}

void drain(stream_t &pre){
    data_t tmp;
    for(int k=0; k<PE_K; k++){
        pre >> tmp;
    }
}

void pe_array(data_t a[PE_M][PE_K], data_t b[PE_K][PE_N], data_t c[PE_M][PE_N]){
    stream_t a_inter[PE_M][PE_N+1];
#pragma HLS stream variable=a_inter
    stream_t b_inter[PE_M+1][PE_N];
#pragma HLS stream variable=b_inter

#pragma HLS DATAFLOW

    for(int m=0; m<PE_M; m++){
#pragma HLS UNROLL
        load_a(m, a, a_inter[m][0]);
    }
    
    for(int n=0; n<PE_N; n++){
#pragma HLS UNROLL
        load_b(n, b, b_inter[0][n]);
    }

    C_ROW:
    for(int m=0; m<PE_M; m++){
#pragma HLS UNROLL
        C_COL:
        for(int n=0; n<PE_N; n++){
#pragma HLS UNROLL
            pe(a_inter[m][n], b_inter[m][n], a_inter[m][n+1], b_inter[m+1][n], &(c[m][n]));
        }     
    }

    for(int m=0; m<PE_M; m++){
#pragma HLS UNROLL
        drain(a_inter[m][PE_N]);
    }
    
    for(int n=0; n<PE_N; n++){
#pragma HLS UNROLL
        drain(b_inter[PE_M][n]);
    }
}

void test(data_t *a_addr, data_t *b_addr, data_t *c_addr){
#pragma HLS INTERFACE m_axi depth=32 port=a_addr
#pragma HLS INTERFACE m_axi depth=32 port=b_addr
#pragma HLS INTERFACE m_axi depth=32 port=c_addr

    data_t a[PE_M][PE_K];
#pragma HLS array_partition variable=a complete dim=1
    data_t b[PE_K][PE_N];
#pragma HLS array_partition variable=b complete dim=2
    data_t c[PE_M][PE_N];
#pragma HLS array_partition variable=c complete dim=0

    for(int m=0; m<PE_M; m++){
#pragma HLS PIPELINE
        for(int ak=0; ak<PE_K; ak++){
            a[m][ak] = *(a_addr++);
        }
    }

    for(int bk=0; bk<PE_K; bk++){
#pragma HLS PIPELINE
        for(int n=0; n<PE_N; n++){
            b[bk][n] = *(b_addr++);
        }
    }

    for(int m=0; m<PE_M; m++){
#pragma HLS UNROLL
        for(int n=0; n<PE_N; n++){
            c[m][n] = 0;
        }
    }

    pe_array(a, b, c);

    for(int m=0; m<PE_M; m++){
#pragma HLS PIPELINE
        for(int n=0; n<PE_N; n++){
            *(c_addr++) = c[m][n];
        }
    }
}
