#include <stdio.h>

/* Function Prototypes */
void printBitsInt(int num);
int countOneBits(int num);
void checkEndian();
void printFloatBits(float num);

int main() {
    int num;
    float fnum;

    printf("Enter an integer: ");
    scanf("%d", &num);

    printf("\nBits of Integer %d:\n", num);
    printBitsInt(num);

    printf("\nNumber of 1 bits = %d\n", countOneBits(num));

    printf("\nEndian Check:\n");
    checkEndian();

    printf("\nUnderstanding Negative Integer:\n");
    printf("Bits of %d:\n", -num);
    printBitsInt(-num);

    printf("\nEnter a floating point number: ");
    scanf("%f", &fnum);

    printf("\nBits of Floating Point Number %.2f:\n", fnum);
    printFloatBits(fnum);

    printf("\nBits of Negative Floating Point Number %.2f:\n", -fnum);
    printFloatBits(-fnum);

    return 0;
}

/* Function to print bits of an integer */
void printBitsInt(int num) {
    int i;

    for(i = sizeof(int) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);

        if(i % 8 == 0)
            printf(" ");
    }

    printf("\n");
}

/* Function to count number of 1 bits */
int countOneBits(int num) {
    int count = 0;

    while(num) {
        count += num & 1;
        num >>= 1;
    }

    return count;
}

/* Function to check endian type */
void checkEndian() {
    int x = 1;
    char *c = (char*)&x;

    if(*c == 1)
        printf("System is Little Endian\n");
    else
        printf("System is Big Endian\n");
}

/* Function to print bits of float */
void printFloatBits(float num) {
    int *ptr;
    int i;

    ptr = (int*)&num;

    for(i = sizeof(float) * 8 - 1; i >= 0; i--) {
        printf("%d", (*ptr >> i) & 1);

        if(i % 8 == 0)
            printf(" ");
    }

    printf("\n");
}