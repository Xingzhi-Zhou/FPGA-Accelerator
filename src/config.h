/*
*   config.h
*   Created on: 2020.09.04
*   Author: Xingzhi Zhou
*/
#ifndef __CONFIG_H_
#define __CONFIG_H_

// data
#define DATA_WIDTH 16
#define DATA_INTEGER_BITS 8

#define BUS_WIDTH 512

#define BUS_LEN 32

// input image
#define C_1 1
#define H_1 28
#define W_1 28

// conv 1
#define K_2 1   // 1 --> 3*3; 2 --> 5*5;
#define C_2 6
#define H_2 28
#define W_2 28

// pooling 1
#define C_3 6
#define H_3 14
#define W_3 14

// conv 2
#define K_4 1   // 1 --> 3*3; 2 --> 5*5;
#define C_4 32
#define H_4 14
#define W_4 14

// pooling 2
#define C_5 32
#define H_5 7
#define W_5 7
#define RC_5 1568 // 32*7*7

// fc 1
#define C_6 512

// fc 2
#define C_7 10

#endif
