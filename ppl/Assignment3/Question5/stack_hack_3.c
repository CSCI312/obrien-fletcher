#include <stdio.h>
int main()
{
    int i;
    printf("The stack top is near %p\n", &i);
    int q;
    printf("The stack grew, new top at %p\n", &q);
    return 0;
}
