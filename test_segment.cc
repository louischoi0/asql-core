#include "my-redis.h"
#include <stdio.h>
#include <assert.h>

void getBlockBufferInfo(mbf& disc){
    printf("membuffer : %d/%d\n",disc.n_alloc,disc.t_alloc); 
};

void print_mem_values(const mbf& mbfi) {
    mem* m = (mem*)(mbfi.trnp) - 1;

    printf("memvalues : %d,%d\n",mbfi.t_elems,mbfi.t_alloc);

    for (int i =0; i < mbfi.t_elems; m--, i++){
        if (m->ptr == 0) continue;
        printf("v:%d,vv:%s\n",m->size,m->ptr);
    };

};

void test_ips(mbf* minstance) {
    const char* a0 = "abcd";
    const char* a1 = "bfgc";
    const char* a2 = "czyz";
    const char* a3 = "dzyz";

    mem* m0;
    mem* m1;
    mem* m2;
    mem* m3;
    
    printf("test\n");

    m0 = minstance->assign((char*)a0,4);
    m1 = minstance->assign((char*)a1,4);
    m2 = minstance->assign((char*)a2,4);
    m3 = minstance->assign((char*)a3,4);

    minstance->delete_mem(m1);

    m3 = minstance->assign((char*)a3,4);

    assert ( m1 == m3 );
    print_mem_values(*minstance);
};

int testSegment() {

    uint init_blocks = 20;
    uint t_size = init_blocks * 1024*1024*20;

    segment* seg; 
    makeSegment(&seg,init_blocks,t_size,0);
    printf("makeSegment\n"); 
    mbf* mbfd;

    printf("AddBlocks\n");
    
    seg->addBlock(1000,&mbfd);
    
    printf("hiroo");
    char* datas = mbfd->entry;

    mbf* check;
    mbf* check1;
    mbf* check2;
    mbf* check3;

    seg->getBlockInfo(&check,0);
    test_ips(check);
    //getBlockBufferInfo(*check);
    
};

int main(){
    testSegment();
    return 0;
};
