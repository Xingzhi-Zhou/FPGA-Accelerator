#include "mnist.h"
#include "iomanip"
#include "iostream"

using namespace std;

void mnist(str &str_in, str &str_out){
    bus_t str_temp;
    bus_t temp;
    data_t input_1[C_1][H_1][W_1];
    data_t input_2[C_2][H_2][W_2];
    data_t input_3[C_3][H_3][W_3];
    data_t input_4[C_4][H_4][W_4];
    data_t input_5[C_5][H_5][W_5];
    data_t input_6[C_6];
    data_t input_7[C_7];

    // load input image
    for(int ic=0; ic<C_1; ic++){
        for(int ih=0; ih<H_1; ih++){
            str_temp = str_in.read();
            for(int j=0; j<W_1; j++){
                input_1[ic][ih][j] = str_temp.data[j];
                // cout << input_1[ic][ih][j] << ", ";
            }
            // cout << endl;
        }
    }

    cout << "conv2d_1" << endl;
    conv2d_1(input_1, str_in, input_2);
//    for(int ic=0; ic<C_2; ic++){
//    	for(int ih=0; ih<H_2; ih++){
//    		for(int iw=0; iw<W_2; iw++){
//    			cout << input_2[ic][ih][iw] << ", ";
//    		}
//    		cout << endl;
//    	}
//    	cout << endl;
//    }

    cout << "pooling_1" << endl;
    pooling_1(input_2, input_3);
	for(int ic=0; ic<C_3; ic++){
		for(int ih=0; ih<H_3; ih++){
			for(int iw=0; iw<W_3; iw++){
				cout << input_3[ic][ih][iw] << ", ";
			}
			cout << endl;
		}
		cout << endl;
	}


    cout << "conv2d_2" << endl;
    conv2d_2(input_3, str_in, input_4);
    cout << "pooling_2" << endl;
    pooling_2(input_4, input_5);
//    for(int ic=0; ic<C_5; ic++){
//    	for(int ih=0; ih<H_5; ih++){
//    		for(int iw=0; iw<W_5; iw++){
//    			cout << input_5[ic][ih][iw] << ", ";
//    		}
//    		cout << endl;
//    	}
//    	cout << endl;
//    }
    cout << "fc_2d_1" << endl;
    fc_2d_1(input_5, str_in, input_6);
    cout << "fc_2" << endl;
    fc_2(input_6, str_in, input_7);

    cout << "Write output" << endl;
    for(int ic=0; ic<C_7; ic++){
    	temp.data[ic] = input_7[ic];
    }
    for(int i=C_7; i<BUS_LEN; i++){
    	temp.data[i] = 0;
    }
    str_out.write(temp);
}
