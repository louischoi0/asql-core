#include "algorithms.h"

int printArr(uint* arr,uint size){
    uint* p = arr; 
    for (int i = 0; i < size; i++,p++) printf("%d,",*p);
    printf("\n");
};

int swap(uint* a, uint* b){
    uint temp = *a;
    *a = *b;
    *b = temp;

    return 0;
};

uint* aa = (uint*)malloc(sizeof(uint)*20);

int find(uint f, uint* arr, uint size){
    uint* p = arr;
    for (int i = 0; i < size; i++,p++ ){
        if (*p == f ) return i;
    };
    
    return -1;
};

int quick(uint* arr,uint* l, uint* r ) {

    uint* i = l;
    uint* j = r;
    uint temp;
    uint pivot = *(l + ( j - i ) / 2);

    do{

        while( *i < pivot ) i++;
        while( *j > pivot ) j--;

        if( i <= j ){
            temp = *i;
            *i = *j;
            *j = temp;
            i++;
            j--;
        };

    }while(i <= j);
    
    if ( l < j ) quick(arr,l,j);
    if ( i < r ) quick(arr,i,r);

};

int testSort() {
    uint a[13] = { 11,5,10,3,9,7,12,6,13,2,1,4,8 }; 

    uint* p = aa;
    
    for (int i =0;i<13;i++,p++) *p = a[i]; 

    quick(aa,aa,aa+12);
    printArr(aa,13);

    printf("\n");
    p = aa;
};
