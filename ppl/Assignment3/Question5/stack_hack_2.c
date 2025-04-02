#include <stdio.h>
#include <stdlib.h>

// Global (initialized) variable -> typically .data segment
int g_init = 42;

// Global (uninitialized) variable -> typically .bss segment
int g_uninit;

static int s_var = 100; // Static file-scope var, also .data if initialized

int main(void)
{
    // Local (automatic) variable on the stack
    int local_var = 123;

    // Dynamically allocated memory -> heap
    int *heap_var = malloc(sizeof(int));
    if (!heap_var) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }
    *heap_var = 456;

    // Print addresses
    printf("Address of main()    : %p (text segment)\n", (void *)&main);
    printf("Address of g_init    : %p (.data segment)\n", (void *)&g_init);
    printf("Address of g_uninit  : %p (.bss segment)\n", (void *)&g_uninit);
    printf("Address of s_var     : %p (.data segment)\n", (void *)&s_var);
    printf("Address of local_var : %p (stack)\n", (void *)&local_var);
    printf("Address of heap_var  : %p (heap pointer itself on stack)\n", (void *)&heap_var);
    printf("Address in heap_var  : %p (heap)\n", (void *)heap_var);

    free(heap_var);
    return 0;
}
