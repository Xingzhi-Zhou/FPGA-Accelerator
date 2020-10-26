/*
*   data.h
*   Created on: 2020.09.04
*   Author: Xingzhi Zhou
*/
#ifndef __DATA_H_
#define __DATA_H_

#include "config.h"

// HLS library
#include "ap_int.h"
#include "ap_fixed.h"
#include "hls_stream.h"

using namespace hls;

// typedef int data_t;
typedef ap_fixed<DATA_WIDTH, DATA_INTEGER_BITS, AP_RND_CONV, AP_SAT> data_t;

typedef stream<data_t> stream_t;


#endif
