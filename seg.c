#include "seg.h"
#define T Segment_T


T Segment_new(){
	
	T mem = NEW(mem);
	Seq_T ids = Seq_new(2500);
	Seq_T segments = Seq_new(2500);
	
	for(INSTR i = 0; i < 2500; i++){
		Seq_addhi(ids, (void *) (uintptr_t) i);
	}
	mem -> unknown = ids;
	mem -> segment = segments;
	return mem;

}

void Segment_free(T * mem){
	int len = Seq_length((*mem) -> segment);
	for(int i = 0; i < len; i++){
		free(Seq_get((*mem) -> segment, i));
	}
	Seq_free(&((*mem) -> segment));
	Seq_free(&((*mem) -> unknown));
	free(*mem);
}

ID Segment_map(T mem, uint32_t size){
	
	uint32_t *segmentu = malloc(sizeof(uint32_t) * (size + 1));
	uint32_t i = 0;
	while( i <= size){
		segmentu[i] = 0;
		i++;
	}
	segmentu[0] = size;
	ID id;
	Seq_T segs = mem -> segment;
	Seq_T umap = mem -> unknown;
	ID umap_len = Seq_length(umap);
	ID segments_len = Seq_length(segs);

	if(umap_len == 0){
		for(ID i = segments_len; i < (segments_len + 2500); i++){
			Seq_addhi(umap, (void *) (uintptr_t) i);
		}
	}

	id = (ID)(uintptr_t)Seq_remlo(umap);
	if(id >= segments_len){
		Seq_addhi(segs, segmentu);
	} else {
	
		Seq_put(segs, id, segmentu);
	}
	return id;
}

void Segment_unmap(T ids, ID size){

	Seq_addlo(ids -> unknown, (void *)(uintptr_t) size);
     	
	INSTR *word = Seq_get( ids -> segment, size);
	free(word);
	Seq_put(ids-> segment, size, NULL);
}

REG Segment_load(T mem, REG b, REG c){
	
	REG *seg = Seq_get(mem -> segment, b);
        return seg[c + 1];
}

void Segment_store(T  mem, ID id, REG off, INSTR word){
	
	REG *segment = Seq_get(mem -> segment, id);
	segment[off + 1] = word;
}

void Segment_move(T mem,  REG src, REG target){
	REG *source = Seq_get(mem -> segment, src);
	REG size = source[0];
	Segment_unmap(mem, target);
	assert(Segment_map(mem, size) == target);
	REG *targ = Seq_get(mem -> segment, target);
	memcpy(targ, source, ((size + 1) * sizeof(INSTR)));
}




