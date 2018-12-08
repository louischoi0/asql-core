#ifndef __MEM__
#define __MEM__

#include <stdlib.h>
#include <cstring>

typedef struct mem{
    char* ptr;
    uint size;
    uint lck;
}mem;

void* get_mem(const mem&);
int set_mem(mem* mi,char* v);

#endif
