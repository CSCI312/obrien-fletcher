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

/* Classify string looks at the current token and
return a value of "type" "qualifier" or "indentifier"*/
char classify_string(void){
    return this.type;
}

int gettoken(void) {
    
}