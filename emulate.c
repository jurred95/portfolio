#include "emulate.h"
#include <stdio.h>
#include "except.h"
#include "stdbool.h"


/*****************************************************************************/

Except_T Bitpack_Overflow = { "Overflow packing bits" };

static inline uint64_t shl(uint64_t word, unsigned bits) {
  assert(bits <= 64);
  if (bits == 64)
    return 0;
  else
    return word << bits;
}

static inline uint64_t shr(uint64_t word, unsigned bits) { // shift R logical
  assert(bits <= 64);
  if (bits == 64)
    return 0;
  else
    return word >> bits;
}

static inline int64_t sra(uint64_t word, unsigned bits) { // shift R arith
  assert(bits <= 64);
  if (bits == 64)
    bits = 63; // will get all copies of sign bit, which is correct for 64
  return (int64_t) word >> bits;
}

bool Bitpack_fitsu(uint64_t n, unsigned width) {
  if (width >= 64)
    return true;
  /* thanks to Jai Karve and John Bryan */
  return shr(n, width) == 0; // clever shortcut instead of 2 shifts
}

static inline uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb) {
  unsigned hi = lsb + width; // one beyond the most significant bit
  assert(hi <= 64);
  return shr(shl(word, 64 - hi), 64 - width); // different type of right shift
}

static inline uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, uint64_t value) {
  unsigned hi = lsb + width; // one beyond the most significant bit
  assert(hi <= 64);
  if (!Bitpack_fitsu(value, width))
    RAISE(Bitpack_Overflow);
  return shl(shr(word, hi), hi)              // high part
       | shr(shl(word, 64 - lsb), 64 - lsb)  // low part
       | (value << lsb);                     // new part
}
/*****************************************************************************/


static inline T um_new(){

	T um = NEW(um);
	um -> mem = Segment_new();
	um -> reg = calloc(8, sizeof(uint32_t));
        um -> pro = 0;
	return um;	
}

static inline void um_free(T *um){

        Segment_free(&((*um)->mem));
        free((*um)->reg);
        free(*um);
}

static inline size_t get_file(const char * input){

   // assume file is a const char *
  struct stat buf; // file metadata
  int rc = stat(input, &buf);
  if (rc != 0) {
    perror(input);
    exit(1);
  }
  size_t len = buf.st_size; // bytes in file
  assert(len % 4 == 0);

  return len / 4;

}

static inline void load_file(T um, int size, const char *input){
        uint32_t w = 0;
        uint32_t word_num = size;
        unsigned char ch;
        FILE *fp = fopen(input, "rb");
        for(uint32_t i = 0; i < word_num; i++){
                ch = getc(fp);
                w = Bitpack_newu(w, 8, 24, (uint64_t) ch);
                ch = getc(fp);
                w = Bitpack_newu(w, 8, 16, (uint64_t) ch);
                ch = getc(fp);
                w = Bitpack_newu(w, 8, 8, (uint64_t) ch);
                ch = getc(fp);
                w = Bitpack_newu(w, 8, 0, (uint64_t) ch);

                Segment_store(um -> mem, 0, i, w);
        }

        fclose(fp);
}

void run(T um, const char *input){
	
	uint32_t current;
	int size = get_file(input);

	assert(Segment_map(um->mem, size) == 0);

	load_file(um, size, input);

	while(!false){
		current = Segment_load(um->mem, 0, um -> pro);
		run_dat_boi(um, current);
		um-> pro += 1;
	}
}



void run_dat_boi(T um, uint32_t instruct){

	short op = Bitpack_getu(instruct, op_len, op_lsb);
        short a_id = Bitpack_getu(instruct, id_len, A_LSB);
        short b_id = Bitpack_getu(instruct, id_len, B_LSB);
        short c_id = Bitpack_getu(instruct, id_len, C_LSB);
        uint32_t *a = &((um->reg)[a_id]);
        uint32_t *b = &((um->reg)[b_id]);
        uint32_t *c = &((um->reg)[c_id]);
        uint32_t val;

	switch(op){
		case 0:
			if(*c != 0){
               		 *a = *b;
       			 }
			break;
		case 1:
			
			*a = Segment_load(um->mem, *b, *c);
			break;
		case 2:
			
			Segment_store(um->mem, *a, *b, *c);
			break;
		case 3:
			*a = (*b + *c);
			break;
		case 4:
			 *a = (*b * *c);
			break;
		case 5:
			*a = (*b / *c);
			break;
		case 6:
			*a = ~(*b & *c);
			break;
		case 7:
			um_free(&um);
			 exit(EXIT_SUCCESS);
                         printf("this empty...YEET");
                         printf("Happy Holidays");
                         printf("PLEASE GIVE US AN A FOR THE COURSE");
			break;
		case 8:
			*b = Segment_map( um->mem, *c);
			break;
		case 9:
			Segment_unmap(um -> mem, *c);
	       		break;
		case 10:
			 fprintf(stdout, "%c", (char)(*c));
			break;
		case 11:
			*c = fgetc(stdin);
       			if( *c == (unsigned) EOF){
               			 *c  = ~0;
        		 }

			break;
		case 12:
			if(*b != 0){
               		 Segment_move(um -> mem, *b, 0);
     				   }
     
			um->pro = *c -1;
			break;
		case 13:
			
			val = Bitpack_getu(instruct, val_len, val_lsb);
			a_id = Bitpack_getu(instruct, id_len, op_lsb - id_len);
			a = &((um-> reg)[a_id]);
			 *a = val;
			break;	
		default:
			fprintf(stderr, "YEET YAH WRONG.\n");
			um_free(&um);
			exit(0);
	}
}


int main(int argc, char *argv[])
{
        if (argc > 2) {
                fprintf(stderr, "Error: too thicc\n");
                printf("EXITING NOW, HAPPY HOLIDAYS, JUST KIDDING :DEVIL FACE EMOJI:");
                exit(1);
        }
        else if (argc == 2) {
                UM um = um_new();
                run(um, argv[1]);
                um_free(&um);
        }
        else {
                fprintf(stderr, "Error: too thin\n");
                exit(1);
        }
        return 1;
}

