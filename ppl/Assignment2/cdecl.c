#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKENLEN 64
#define MAXTOKENS 100

struct token { 
    char type;
    char string[MAXTOKENLEN]; 
};
/* holds tokens we read before reaching first identifier */
struct token stack[MAXTOKENS];
/* holds the token just read */
struct token this;

/*1.get current token
2. set this.string equal to token
3. classify it, set this.type
4. if not identifier, push onto stack
5. */

/* Classify string looks at the current token and
return a value of "type" "qualifier" or "indentifier"
Need to look at this.string so we can set this.type*/
char classify_string(void){
    if (strcmp(this.string, "restrict") == 0 ||
        strcmp(this.string, "volatile") == 0 ||
        strcmp(this.string, "const") == 0){
            this.type = 'q';
            return 'q';
    }

    if (strcmp(this.string, "void") == 0 ||
        strcmp(this.string, "char") == 0 ||
        strcmp(this.string, "short") == 0 ||
        strcmp(this.string, "int") == 0 ||
        strcmp(this.string, "long") == 0 ||
        strcmp(this.string, "float") == 0 ||
        strcmp(this.string, "double") == 0 ||
        strcmp(this.string, "signed") == 0 ||
        strcmp(this.string, "unsigned") == 0){
            this.type = 't';
            return 't';
    }

    this.type = 'i';
    return 'i';
}

int gettoken(void) {
    //read the next token into this.string
    //if it is alphanumeric, classify_string
    if (scanf("%[A-Za-z0-9_]", this.string) == 1){

        if (strlen(this.string) == 1){
            this.type = this.string;
            this.string[0] = '\0';
        } else {
            classify_string();
        }
    }
}