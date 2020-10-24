#include <iostream>
#include "layer.h"
#include "data.h"

using namespace std;

int main(){
    int err = 0;
    data_t A[PE_M][PE_K];
    data_t B[PE_K][PE_N];
    data_t A1[PE_M*PE_K];
    data_t B1[PE_K*PE_N];
    data_t C1[PE_M*PE_N];
    data_t C_ref[PE_M][PE_N];

    for(int m=0; m<PE_M; m++){
        for(int k=0; k<PE_K; k++){
            A[m][k] = (m+k)%3;
            A1[m*PE_K+k] = (m+k)%3;
        }
    }

	for(int k=0; k<PE_K; k++){
        for(int n=0; n<PE_N; n++){
            B[k][n] = (n+k)%4;
            B1[k*PE_N+n] = (n+k)%4;
        }
    }


    data_t acc;
    for(int m=0; m<PE_M; m++){
        for(int n=0; n<PE_N; n++){
            acc = 0;
            for(int k=0; k<PE_K; k++){
                acc += A[m][k] * B[k][n];
            }
            C_ref[m][n] = acc;
        }
    }

#ifdef DEBUG
    for(int m=0; m<PE_M; m++){
        for(int n=0; n<PE_N; n++){
            cout << C_ref[m][n]<< ", ";
        }
        cout << endl;
    }
#endif

    test(A1, B1, C1);

#ifdef DEBUG
    for(int m=0; m<PE_M; m++){
        for(int n=0; n<PE_N; n++){
            cout << C1[m*PE_N+n] << ", ";
        }
        cout << endl;
    }
#endif

    for(int m=0; m<PE_M; m++){
        for(int n=0; n<PE_N; n++){
            if(C_ref[m][n] != C1[m*PE_N+n]){
                err++;
            }
        }
    }

	if(err){
		cout << "Test failed!" << endl;
		return -1;
	}
	else{
		cout << "Test success!" << endl;
		return 0;
	}
}
