#ifndef __KEY_PAIR__ 
#define __KEY_PAIR__

typedef unsigned int uint;

typedef struct key_pair{
    void* key;
    void* value;

    uint k_size;
    uint v_size;

}key_pair;

#define KEY_PAIR_DELIMITER "@"

    uint get_split_pos(char*,uint);
    int make_key_pair(void*,uint );

#endif

