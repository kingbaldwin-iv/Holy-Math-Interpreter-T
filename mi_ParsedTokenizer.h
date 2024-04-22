#include "mi_Tokenizer.h"
#include <string.h>

typedef struct ParsedTokenizer {
    Tokenizer* tokenizer;
    char** eval_vars;
    int* eval_ints;

    int parsed_token_count;
    char** parsed_tokenized;
} ParsedTokenizer;

ParsedTokenizer* initPT(Tokenizer* tokenizer, char** eval_vars, int* eval_ints,int eval_c);
ParsedTokenizer* initPT_E(char* tokenize, char** eval_vars, int* eval_ints,int eval_c);

ParsedTokenizer* initPT(Tokenizer* tokenizer, char** eval_vars, int* eval_ints, int eval_c) {
    if(tokenizer == NULL || tokenizer->tokenized == NULL)
        return NULL;

    
    ParsedTokenizer* pt = (ParsedTokenizer*)malloc(sizeof(ParsedTokenizer));
    pt->tokenizer = tokenizer;
    pt->eval_vars = eval_vars;
    pt->eval_ints = eval_ints;

    int tc = token_count(tokenizer);
    char* temp[tc];
    char** to_parse = pt->tokenizer->tokenized;
    for(int i = 0; i < tc; i++) {
        temp[i] = to_parse[i];
        for(int j = 0; j < eval_c; j++) {
            if(!strcmp(to_parse[i]+1,eval_vars[j])) {
                char* to_free = to_parse[i];
                char* n = num_to_char(eval_ints[j]);
                if(to_parse[i][0] == '-') n[0] = n[0] == '+' ? '-' : '+';
                temp[i] = n;
                free(to_free);
            }
        }  
    }
    int sum_int = 0;
    int ptc = 1;
    for(int i = 0; i < tc; i++) {
        if(!is_digit(temp[i][1])) ptc++;
    }
    pt->parsed_token_count = ptc;
    pt->parsed_tokenized = (char**) malloc(sizeof(char*) * ptc);
    ptc = 0;
    for(int i = 0; i < tc; i++) {
        if(is_digit(temp[i][1])){
            sum_int += atoi(temp[i]);
            free(temp[i]);
        }else{
            (pt->parsed_tokenized)[ptc++] = temp[i];
        }
    }

    (pt->parsed_tokenized)[ptc] = num_to_char(sum_int);
    return pt;    
}
ParsedTokenizer* initPT_E(char* tokenize, char** eval_vars, int* eval_ints,int eval_c) {
    return initPT(initT(tokenize),eval_vars,eval_ints,eval_c);
}



void print_parsed_tokens(ParsedTokenizer* pt) {
    printf("[");
    for(int i = 0; i < (pt->parsed_token_count)-1; i++) {
        printf("%s, ", (pt->parsed_tokenized)[i]);
    }
    printf("%s]", (pt->parsed_tokenized)[(pt->parsed_token_count)-1]);
}
