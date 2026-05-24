#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// Structure definition
struct Student {
    int roll;
    char name[50];
    float marks;
};

// Function declarations
void writeRecords(const char *filename, struct Student s[], int n);
int createIndex(const char *filename, long positions[]);
void displayRecord(const char *filename, long position);

int main() {
    struct Student students[MAX] = {
        {1, "Alice", 85.5},
        {2, "Bob", 90.0},
        {3, "Charlie", 78.2},
        {4, "David", 88.8},
        {5, "Emma", 92.1}
    };

    long positions[MAX];
    int count, choice;

    // Store records in ASCII format
    writeRecords("students.txt", students, MAX);

    // Create array of seek positions
    count = createIndex("students.txt", positions);

    printf("Seek positions of records:\n");
    for (int i = 0; i < count; i++) {
        printf("Record %d starts at position %ld\n", i + 1, positions[i]);
    }

    // Display record using seek position
    printf("\nEnter record number to display (1-%d): ", count);
    scanf("%d", &choice);

    if (choice >= 1 && choice <= count) {
        displayRecord("students.txt", positions[choice - 1]);
    } else {
        printf("Invalid record number.\n");
    }

    return 0;
}

// Function to write array of structures into file
void writeRecords(const char *filename, struct Student s[], int n) {
    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %s %.2f\n",
                s[i].roll,
                s[i].name,
                s[i].marks);
    }

    fclose(fp);
}

// Function to create array of record positions
int createIndex(const char *filename, long positions[]) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int count = 0;
    char line[100];

    while (1) {
        positions[count] = ftell(fp);

        if (fgets(line, sizeof(line), fp) == NULL)
            break;

        count++;
    }

    fclose(fp);
    return count;
}

// Function to display a record using seek position
void displayRecord(const char *filename, long position) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    struct Student s;

    fseek(fp, position, SEEK_SET);

    fscanf(fp, "%d %s %f",
           &s.roll,
           s.name,
           &s.marks);

    printf("\nRecord at position %ld:\n", position);
    printf("Roll No : %d\n", s.roll);
    printf("Name    : %s\n", s.name);
    printf("Marks   : %.2f\n", s.marks);

    fclose(fp);
}