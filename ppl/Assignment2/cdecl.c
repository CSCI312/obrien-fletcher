#define MAXTOKENLEN 64
#define MAXTOKENS 100

struct token { char type; char string[MAXTOKENLEN]; };
/* holds tokens we read before reaching first identifier */
struct token stack[MAXTOKENS];
/* holds the token just read */
struct token this; 