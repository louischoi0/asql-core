#include "mem.h"

void* get_mem(const mem& mi ){
    while(mi.lck) continue;
    return mi.ptr;
};

int set_mem(mem* mi,char* v){
    while(mi->lck) continue;
    memcpy(mi->ptr,v,mi->size); 
};
