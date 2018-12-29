#ifndef EMULATE_H_
#define EMULATE_H_

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "seg.h"
#include <assert.h>
#define A_LSB 6
#define B_LSB 3
#define C_LSB 0
#define op_lsb 28
#define val_lsb 0
#define op_len 4
#define w_len 32
#define id_len 3
#define val_len 25
#define T UM

struct T{
        Segment_T mem;
        uint32_t *reg;
        uint32_t pro;
};

typedef struct T *T;


void run(T um, const char *input);
void run_dat_boi(T um, uint32_t instruct);

#endif
