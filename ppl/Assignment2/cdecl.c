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
    if (strcmp(this.string, "example")){
        return 'q';
    }
}

int gettoken(void) {
    this.string = stack[1].string;
}