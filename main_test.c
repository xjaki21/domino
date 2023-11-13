#include <stdio.h>
#include <stdlib.h>

struct tessera
{
    int n1;
    int n2;
};

void init(struct tessera *tessera){
    
    int k=0;
    for(int i=0;i<6;i++){
        for(int j=i;j<6;j++){
            tessera[k].n1=i+1;
            tessera[k].n2=j+1;
            k++;
        }
    }
}


int main(){

    struct tessera tessera[21];
    init(tessera);

    for(int i=0;i<21;i++){
        printf("[%d|%d] ",tessera[i].n1,tessera[i].n2);
        if(i>0 && tessera[i].n1<tessera[i+1].n1){
            printf("\n");
        }
    }

    

    
}