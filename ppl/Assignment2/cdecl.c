#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKENLEN 64
#define MAXTOKENS 100

int ind = -1; //index track position 

struct token { 
    char type;
    char string[MAXTOKENLEN]; 
};
/* holds tokens we read before reaching first identifier */
struct token stack[MAXTOKENS];
/* holds the token just read */
struct token this;

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
    if (scanf(" %99[^A-Za-z0-9 \t\n]", this.string) == 1){

        if (strlen(this.string) >= 1){
            this.type = *this.string; //this.type = the token itself
            this.string[0] = '\0'; //terminate with a nul
            ind++;
            return 0;
        }
    }

    if (scanf("%[A-Za-z0-9_]", this.string) == 1){

        if (strlen(this.string) == 1){
            this.type = *this.string; //this.type = the token itself
            this.string[0] = '\0'; //terminate with a nul
        } else {
            classify_string();
        }
        ind++;
    }
}

int read_to_first_identifier(void){
    gettoken(); //get first token

    while (this.type != 'i'){ //until first identifier
        stack[ind] = this; //push onto stack
        gettoken();
    }

    printf("identifier is %s", this.string);

    gettoken;
}

//parsing routines

//read past closing ')' and print out
int deal_with_function_args(void){
    if (this.type == ')'){
        printf("function returning");
    }
}

//while you've got "[size]", print it and read past
int deal_with_arrays(void){
    if (this.type == '['){
        printf("[%d]", gettoken());
        gettoken();
    }
}

/*1.get current token
2. set this.string equal to token
3. classify it, set this.type
4. if not identifier, push onto stack
5. */
int main(void){
    read_to_first_identifier();
}