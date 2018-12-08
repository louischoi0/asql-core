#ifndef __MEDIS__
#define __MEDIS__

#include "mem.h"
#include <stdlib.h>
#include <cstring>
#include <stdio.h>

typedef unsigned int uint;
typedef signed int sint;

typedef struct node {
    node* next;
    node* prev;
    void* value;
    uint size;

    node() :
        next(0),
        prev(0),
        value(0),
        size(0) 
    {
    

    };

}node;

typedef struct list{
    node* head;   
    node* tail;
    
    uint n_elems; 
   
    list() :
        head(0),
        tail(0),
        n_elems(0) {};

}list;

typedef struct listIter{
    node* now;
    uint offset;
    list* plist;
}listIter;

typedef struct mObj{
    uint size;
    char* value;
}mObj;

#define BLOCK_INFO_SIZE 2048
#define INIT_BLOCK_SIZE 20 
#define MAX_SEG 1024*1024*1024*4 

#define INIT_IPS 24 
#define MAX_ELEM 2048 


class mbf{
public:
    friend class segment;

    uint t_alloc;
    uint n_alloc;

    char* entry;
    char* bentry;

    char* trnp;
    
    char* mdata;

    list* ips;

    char* aps;
    
    int a;
    int b;
    
    uint n_elems;
    uint t_elems;
    uint max_elems;
        
    mbf() :
        t_alloc(-1),
        trnp(0),
        entry(0),
        ips(0){
        };
    
    
    int set_ipts(uint, uint*);
    void update_stddv(uint add_size);
    int atnf(uint esize,char*);

    int add_element(uint size);

    mem* assign(char*,uint);
    mem* get_mem_free();

    int delete_mem(mem*);

    int adips(mem*);
    int checkOverFlow();

};

class segment{
public:
    uint n_alloc;

    char* data;
    char* bdata;

    list* entries;
    list* mbfds;

    char* bf_entry;

    sint* stdv;

public :
    segment() : 
        n_alloc(0),
        data(0),
        entries(0){
    
        };
    
    int initialize(int);
    int sgalloc(char** p,int size);
    int evalEtryPoints(int size);    
    int getBlockInfo(mbf**,uint);    
    int addBlock(uint bsize,mbf**);
    int addtinfo(int esize);
};

typedef int (*finalizer)(void**,int,list** out);
typedef int (*excutor)(void**,int,list** out);

int makeSegment(segment**,uint,uint,finalizer);

int find(listIter**,list*,mObj*);
int ofind(char**,list*,uint);

int pop_front(list* ,node**);

int makeList(list**);
int appendNode(list*,node*);
int append(list*,mObj*);

int insertNode(list*,listIter*,int,node*);
int printList(list* list);


void getBlockBufferInfo(mbf&);
void print_mem_values(const mbf&);

#endif

