#include "key_pair.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

/* kp must be allocated in mbf->data */

int make_key_pair(void* ptr,uint size,key_pair* kp){

    uint split_pos = get_split_pos((char*)ptr,size);
       
    kp->key = (void*)kp + sizeof(key_pair);
    kp->value = kp->key + split_pos;

    kp->k_size = split_pos;
    kp->v_size = size - split_pos;

    /* for delimiter */
    kp->v_size--;
};

uint get_split_pos(char* s,uint size){
    char* ss = s;

    for ( uint i = 0; i < size; i++ ){

        if ( strncmp( ss, KEY_PAIR_DELIMITER, 1) == 0 ){
            return i;
            
        };

        ss++;
    };
}

void print_key_pair(key_pair* kp ){
    printf("%s,%s,%d,%d\n", kp->key, kp->value, kp->k_size,kp->v_size);
};


int main(){

    const char* strings = "key@value\0";

    key_pair* kp = (key_pair*)malloc(10000);

    memcpy( (char*)kp + sizeof(key_pair), strings, 9);

    char* p = (char*)kp + sizeof(key_pair);


    uint pos = get_split_pos((char*)p,9);

    make_key_pair(p,9,kp);
    print_key_pair(kp);

    return 0;
};
