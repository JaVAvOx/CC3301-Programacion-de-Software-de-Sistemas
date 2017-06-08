#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "concat.h"

uint bits2uint(char *s) {
    uint suma = 0;
    char *j = s + strlen(s) - 1; // j apunta al ultimo elemento de s
    for (int i = 0; i < strlen(s); ++i) {
        suma += (*j - 48) << i; //(*j) retorna la representacion es ASCII
        --j;
    }
    return suma;
}

char *uint2bits(uint x){
    if (x == 0){
        char *bits = malloc(2);
        char *p = bits + 1;
        *p = '\0';
        --p;
        *p = '0';
        return bits;
    }
    else{
        int count = 0;
        char *aux = malloc(32);
        char *p = aux + 31;
        while(x!=0){
            if ((x&1) == 1){
                *p = '1';
                --p;
                x >>= 1;
                count++;
            }
            else if ((x&1) == 0){
                *p = '0';
                --p;
                x >>= 1;
                count++;
            }
        }
        p += 1;
        char *bits = malloc(strlen(p) + 1);
        char *aux2 = bits + strlen(p);
        char *aux3 = p + strlen(p) - 1;
        *aux2 = '\0';
        --aux2;
        for (int q = 0; q<count;++q){
            *aux2 = *aux3;
            --aux2;
            --aux3;
        }
        return bits;
    }
}



uint concat_bits(uint x, int n, uint y, int m){
    char *dec1 = uint2bits(x);
    char *dec2 = uint2bits(y);
    int largo1 = (int) strlen(dec1);
    int largo2 = (int) strlen(dec2);
    char *decimal1 = malloc(32 + 1); //sizeof(char) es 1, por lo que solo ponemos 32 en lugar de sizeof(char)*32
    char *decimal2 = malloc(32 + 1);
    char *o = decimal1 + 32;
    *o = '\0';
    char *u = decimal2 + 32;
    *u = '\0';
    char *i = decimal1 + 32 - 1;
    char *j = decimal2 + 32 - 1;
    for (int h = 0; h < 32; h++){
        *i = '0';
        *j = '0';
        --i;
        --j;
    }
    i = decimal1 + 32 - 1; // i apunta al ultimo elemento de decimal1
    j = decimal2 + 32 - 1; // j apunta al ultimo elemento de decimal2
    char *a = dec1 + largo1 -1;
    char *b = dec2 + largo2 -1;
    for (int h =0; h<largo1; ++h){
        *i = *a;
        --i;
        --a;
    }
    for (int h =0; h<largo2; ++h){
        *j = *b;
        --j;
        --b;
    }
    i = decimal1 + 32 - 1; // i apunta al ultimo elemento de decimal1
    j = decimal2 + 32 - 1; // j apunta al ultimo elemento de decimal2
    char *conc = malloc((size_t) (n + m) + 1);
    char *r = conc + (size_t) (n + m);
    *r = '\0';
    char *p = conc + n + m - 1; // p apunta al ultimo elemento de concat
    for (int h = 0; h < m; ++h){
        *p = *j;
        --p;
        --j;
    }
    for(int h = 0; h < n; ++h){
        *p = *i;
        --p;
        --i;
    }
    uint numero = bits2uint(conc);
    return numero;
}
