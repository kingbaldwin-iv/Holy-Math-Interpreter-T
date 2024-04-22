#include <stdlib.h> 

int printf (__const char *__restrict __format, ...);

#define MAX_TOKEN_LENGTH 100

int is_digit(char a) { return a >= '0' && a <= '9'; }
int is_space(char a) { return a == ' '; }
int is_letter(char a) { return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'); }
int is_operation(char a) { return a >= '*' && a <= '/'; }

char* parse(char** exp) {
    while(is_space(**exp) && *exp != NULL && **exp != '\0') (*exp)++;
    if(*exp == NULL || **exp == '\0') return NULL;
    // 4 LSBs [--26--,is_mult set,sign set, is_char set,is_mult, sign, is_char] 
    int flags = 0x0; 
    while(**exp == '+' || **exp == '-') {
        if(flags & (0x1<<4)) {
            if(!(flags & (0x1<<1) ^ (**exp == '+' ? (0x1<<1) : 0x0))) flags |= (0x1<<1);
            else flags &= ~(0x1<<1);
        }else flags |= (0x1<<4) | (**exp == '+' ? (0x1<<1) : 0x0);
        (*exp)++;
        while(is_space(**exp) && *exp != NULL && **exp != '\0') (*exp)++;
    }
    if(is_digit(**exp) || is_letter(**exp)) {
        if(!(flags & (0x1<<4))) flags |= (0x1<<4) | (0x1<<1);
        flags |= (0x1<<3) | (is_letter(**exp) ? 0x1 : 0x0);
    }
    if(is_digit(**exp)) flags |= (0x1<<3);
    if(is_letter(**exp)) flags |= (0x1) | (0x1<<3);
    char* r = (char*)malloc(MAX_TOKEN_LENGTH * sizeof(char));
    if (r == NULL) return NULL;
    int it = 0; 
    if(!(flags & (0x1<<1))) r[it++] = '-';
    else r[it++] = '+';
    while(*exp != NULL && **exp != '\0' && (is_digit(**exp) || is_letter(**exp))) {
        if((is_digit(**exp) && (flags & 0x1)) || (is_letter(**exp) && !(flags & 0x1))) {
            free(r); 
            return NULL;
        }
        if(it == MAX_TOKEN_LENGTH) return NULL;
        r[it++] = **exp;
        (*exp)++;
    }
    r[it] = '\0';
    return r;
}



char* num_to_char(int x) {
    if(!x) return 0;
    char s = (0x1<<31 & x) ? '-' : '+';
    x = x > 0 ? x : -x;
    int c = 1;
    int x2 = x;
    while(x/=10) c++;
    char* r = (char*)malloc(c * sizeof(char) + 1);
    r[0] = s;
    while(x2) {
        r[c--] = (x2 % 10) + '0';
        x2 /= 10;
    }
    return r;
}