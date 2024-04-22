#include "mi_ParsedTokenizer.h"

int main(){
    char* expression =  "--a-   op -++-+ -  8 -    7 - -a + s --abc - a + d-s";
    char* evalvars[] = {"a", "op", "s","c"};
    int evalints[] = {12,32,-9,0};

    ParsedTokenizer* pt = initPT_E(expression,evalvars,evalints,4);
    print_parsed_tokens(pt);
    return 0;
}
