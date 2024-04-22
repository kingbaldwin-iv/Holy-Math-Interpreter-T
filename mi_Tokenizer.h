#include "mi_helpers.h"

typedef struct Tokenizer {
    char* tokenize;

    int token_count;
    char** tokenized;
} Tokenizer;

Tokenizer* initT(char* tokenize);
int token_count(Tokenizer* t);
void print_tokens(Tokenizer* t);


Tokenizer* initT(char* tokenize) {
    if(tokenize == NULL || *tokenize == '\0') 
        return NULL;

    Tokenizer* t = (Tokenizer*) malloc(sizeof(Tokenizer));

    t->tokenize = tokenize;
    t->token_count = -1;
    t->token_count = token_count(t);

    t->tokenized = (char**) malloc(sizeof(char*) * (t->token_count));

    char** p = &(t->tokenize);
    int index = 0;
    while(*p != NULL && **p != '\0') {
        char* a = parse(p);
        if(a) (t->tokenized)[index++] = a;
    }
    return t;
}


int token_count(Tokenizer* t) {
    if(t->token_count != -1) return t->token_count;
    char* expression = t->tokenize;
    unsigned count = 0x1<<31;
    while(*expression != '\0' && expression != NULL) {
        if(!(count & (0x1<<31))) {
            if((is_space(*expression) || is_operation(*expression)) && (is_digit(*(expression-1)) || is_letter(*(expression-1)))) count++; 
            if((is_digit(*expression) || is_letter(*expression)) && (expression + 1 == NULL || *(expression + 1) == '\0')) count++;
        }else count = 0x0;
        expression++;
    }
    t->token_count = count;
    return t->token_count;
}

void print_tokens(Tokenizer* t) {
    printf("[");
    for(int i = 0; i < (t->token_count)-1; i++) {
        printf("%s, ", (t->tokenized)[i]);
    }
    printf("%s]", (t->tokenized)[(t->token_count)-1]);
}
