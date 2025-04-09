#include <stdio.h>

void one(char ca[]){
        printf("ca: %p\n", (void *)&ca);
        printf("ca[0]: %p\n", (void *)&ca[0]);
        printf("ca[1]: %p\n", (void *)&ca[1]);
}

int main() {
        char ca[2] = {'a', 'b'};
        one(ca);
        return 0;
}
