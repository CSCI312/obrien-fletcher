#include <stdio.h>

char ga[] = "abcdefghijklmnopqrtsuvwxyz";

void one(char ca[]){
        printf("ca: %p\n", (void *)&ca);
        printf("ca[0]: %p\n", (void *)&ca[0]);
        printf("ca[1]: %p\n", (void *)&ca[1]);
}
void two(char *pa) {
    printf("pa: %p\n", (void *)&pa);
    printf("pa[0]: %p\n", (void *)&pa[0]);
    printf("pa[1]: %p\n", (void *)&pa[1]);

    pa++;
    printf("++pa:%p\n", (void *)pa);
}


int main() {
        char ca[2] = {'a', 'b'};
        one(ca);
        char *pa = "abc";
        two((void *)pa);
	one(ga);
	two(ga);
	printf("ga: %p\n", (void *)&ga);
        printf("ga[0]: %p\n", (void *)&ga[0]);
        printf("ga[1]: %p\n", (void *)&ga[1]);
        return 0;
}
