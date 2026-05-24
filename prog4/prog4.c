#include <stdio.h>

/* Structure with Bitfields */
struct BitField {
    unsigned int firstbit  : 1;
    unsigned int secondbit : 2;
    unsigned int thirdbit  : 3;
};

int main() {

    struct BitField a;

    /* Assign values */
    a.firstbit = 1;
    a.secondbit = 2;
    a.thirdbit = 5;

    /* Display values */
    printf("First Bit  = %u\n", a.firstbit);
    printf("Second Bit = %u\n", a.secondbit);
    printf("Third Bit  = %u\n", a.thirdbit);

    printf("\nSize of structure = %lu bytes\n",
           sizeof(a));

    return 0;
}