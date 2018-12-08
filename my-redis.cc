#include <assert.h>
#include "my-redis.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

#define ERR_OOM -1
#define EMPTY_LIST -100 


/* To free is up to caller */

int pop_front(list* li, node** ni) {

    if ( li->head == 0 ) return 1;

    *ni = li->head;
    li->head = li->head->next;

    if (li->head) li->head->prev = 0;

    return 0;
};

/*
node* pop_back(){
    
    if ( li->tail == 0 ) return 1;

    node* to_pop = li->tail;

    if ( li->tail == li->head ) {
        li->tail = 0;
        li->head = 0;
        return to_pop;
    };

    li->tail->prev->next = 0;
    li->tail = li->tail->prev;

    return to_pop;

};
*/

int ofind(char** pv,list* list, uint offset) {
    if ( list->n_elems - 1 < offset ) return EMPTY_LIST; 
    int i = 0;
    node* n;

    for (n = list->head; i < offset ;n = n->next);
    *pv = (char*)n->value;
};

int find(listIter** iter,list* elist,mObj* obj){

    char* v = obj->value; 
    uint size = obj->size;

    listIter* new_iter = (listIter*)malloc(sizeof(listIter));
    new_iter->plist = elist; 
    
    int offset = 0;

    for ( node* enode = elist->head; enode != 0; enode = enode->next,offset++) {
        
        new_iter->now = enode;
        new_iter->offset = offset;

        if ( size != enode->size ) continue;

        if (!strncmp(v,(char*)enode->value,size)){
            *iter = new_iter; 
            return 0;
        };

    };

    return -1;

};


int makeList(list** elist){
    list* new_list = (list*) malloc(sizeof(list));

    if ( new_list == 0 ) return ERR_OOM;

    new_list->head = 0;  
    new_list->tail = 0;
    new_list->n_elems = 0;

    *elist = new_list;
    return 0;
};

int appendNode(list* elist, node* enode) {
    assert( elist != 0 );

    if (elist->head == 0) {
        elist->head = enode;
        elist->tail = elist->head;
        elist->n_elems = 1;
        return 0;
    }

    else {
        node* temp = elist->tail;
        enode->prev = temp;
        enode->next = 0;

        temp->next = enode;

        elist->tail = enode;
        elist->n_elems++;

        return 0;
    }
};

int append(list* list,mObj* obj) {
    node* enode = new node();

    enode->value = obj->value;
    enode->size = obj->size;
    appendNode(list,enode);

    return 0;
};

int insertNode(list* list, listIter* iter,node* inode,int dir) {

    assert( list == iter->plist );

    if ( dir == 0 ) {
        node* n = iter->now;
        
        inode->prev = n->prev;

        inode->prev->next = inode;
        inode->next = n;
        
        n->prev = inode;
         
        return 0;
    }

    else {
        node* n = iter->now;
        
        if (n->next != 0) {
           n->next->prev = inode; 
           inode->next = n->next;
        };

        n->next = inode;
        inode->prev = n;

        return 0;
    }
};

int printList(list* list) {

    for(node* node = list->head; node != 0; node=node->next) {
        printf("%s",(char*)node->value);
        printf("\n");
    };

};

