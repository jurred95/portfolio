#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "mem.h"
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include "array.h"
#include "seq.h"
#include "arrayrep.h"
#ifndef SEG_H_
#define SEG_H_


#define ID uint32_t
#define INSTR uint32_t
#define REG uint32_t
#define T Segment_T
typedef struct T *T;

struct T{
        Seq_T unknown;
        Seq_T segment;
};

T Segment_new();
void Segment_free(T *);
ID Segment_map(T, uint32_t);
void Segment_unmap(T, uint32_t);
REG Segment_load(T, REG , REG );
void Segment_store(T, REG, REG, REG);
void Segment_move(T, REG, REG);

#undef T
#endif
