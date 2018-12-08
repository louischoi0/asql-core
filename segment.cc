#include "my-redis.h"
#include "algorithms.h"
#include <stdio.h>
#include <cstring>
#include <assert.h>

int segment::initialize(int tsize) {
    makeList(&this->mbfds);
    makeList(&this->entries);

    this->data = (char*)malloc(tsize); 
    this->bdata = (char*)malloc(sizeof(mbf)*INIT_BLOCK_SIZE);
    this->bf_entry = this->bdata;

    if (this->data == 0 or this->bdata == 0) return -1;
    else return 0;
};

int segment::addBlock(uint bsize,mbf** ret) {
    mbf* disc = (mbf*)(this->bf_entry);
    this->bf_entry += sizeof(mbf);
    mObj obj;

    obj.value = (char*)disc;
    obj.size = sizeof(mbf);

// to initialize of mbf
    disc->entry = (char*)(this->data + this->n_alloc);
    
    disc->t_alloc = bsize;
    this->n_alloc += bsize;

    disc->bentry = disc->entry + bsize - 1;
    disc->trnp = disc->bentry;

    append(this->mbfds,&obj);
// end 

    if ( ret != 0 ) *ret = disc;
    
    return 0;
};

int segment::getBlockInfo(mbf** discp, uint offset){
    *discp = (mbf*)(this->bdata + (offset * sizeof(mbf)));
};

int makeSegment(segment** sinstance,uint init_blocks, uint t_size,finalizer notuse){

    segment* ninstance = new segment(); 
    uint rc =  ninstance->initialize(t_size);

    assert ( rc == 0 );
    
    *sinstance = ninstance;
    return 0;
};

int mbf::add_element(uint size) {
    mem memi;

    if (this->n_alloc + size > this->t_alloc) return 1;

    this->n_alloc += size;

    memi.ptr = this->entry;
    memi.size = size;
    memi.lck = 0;

    this->entry += size;
    this->bentry -= sizeof(mem); 

    memcpy(this->bentry,&memi,sizeof(mem));
    return 0; 
};

mem* mbf::assign(char* v, uint size){

    assert(this->n_elems <= MAX_ELEM); 
    mem* new_m; 

    if (this->ips != 0 and this->ips->n_elems > 0 ) new_m = this->get_mem_free();

    else {

        if ( this->n_elems == MAX_ELEM ) return 0;

        this->add_element(size);
        new_m = (mem*)this->bentry;

    };

    new_m->size = size;
    memcpy(new_m->ptr,v,size); 
    
    this->n_elems++;
    this->t_elems++;
    this->entry += size;

    return new_m;
};

mem* mbf::get_mem_free() {
    node* ni;
    uint rc;

    rc = pop_front(this->ips,&ni);

    assert( rc == 0 );
    assert ( ni->size == sizeof(mem) );

    mem* mi = (mem*)(ni->value);  
    delete ni;

    return mi;
};

int mbf::delete_mem(mem* to_delete){

    assert( to_delete->size != -1);
    assert( (char*)to_delete <= this->trnp - sizeof(mem) );
    assert( (char*)to_delete >= this->bentry );

    this->n_elems--;  
    this->n_alloc -= to_delete->size;

    this->adips(to_delete);

    to_delete->size = -1;

    return 0;
};

int mbf::adips(mem* m){
    if ( this->ips == 0 ) this->ips = new list();

    node* ni = new node(); 
    ni->value = (void*)m;  
    ni->size = sizeof(mem);

    return appendNode(this->ips,ni);
};

int mbf::checkOverFlow(){
    if ( this->entry >= this->bentry ) return 1; 
    return 0;
};

