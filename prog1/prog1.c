#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char name[50];
    float salary;
} Employee;

/* Function Prototypes */
void writeRecords(const char *filename, int n);
void displayRecord(const char *filename, int m);
void deleteRecord(const char *filename, int recordNo);

int main()
{
    int n, m, del;

    printf("Enter number of records: ");
    scanf("%d", &n);

    writeRecords("records.dat", n);

    printf("\nEnter record number to display: ");
    scanf("%d", &m);

    displayRecord("records.dat", m);

    printf("\nEnter record number to delete: ");
    scanf("%d", &del);

    deleteRecord("records.dat", del);

    printf("\nRecords after deletion:\n");

    for(int i = 1; i <= n - 1; i++)
    {
        displayRecord("records.dat", i);
    }

    return 0;
}

/* Function to write records into binary file */
void writeRecords(const char *filename, int n)
{
    FILE *fp;
    Employee emp;

    fp = fopen(filename, "wb");

    if(fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    for(int i = 0; i < n; i++)
    {
        printf("\nEnter details of Employee %d\n", i + 1);

        printf("Enter ID: ");
        scanf("%d", &emp.id);

        printf("Enter Name: ");
        scanf("%s", emp.name);

        printf("Enter Salary: ");
        scanf("%f", &emp.salary);

        fwrite(&emp, sizeof(Employee), 1, fp);
    }

    fclose(fp);
}

/* Function to display mth record using fseek */
void displayRecord(const char *filename, int m)
{
    FILE *fp;
    Employee emp;

    fp = fopen(filename, "rb");

    if(fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    /* Move file pointer to mth record */
    fseek(fp, (m - 1) * sizeof(Employee), SEEK_SET);

    if(fread(&emp, sizeof(Employee), 1, fp) == 1)
    {
        printf("\nRecord %d\n", m);
        printf("ID: %d\n", emp.id);
        printf("Name: %s\n", emp.name);
        printf("Salary: %.2f\n", emp.salary);
    }
    else
    {
        printf("Record not found.\n");
    }

    fclose(fp);
}

/* Function to delete a record */
void deleteRecord(const char *filename, int recordNo)
{
    FILE *fp, *temp;
    Employee emp;
    int count = 1;

    fp = fopen(filename, "rb");

    if(fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    while(fread(&emp, sizeof(Employee), 1, fp))
    {
        if(count != recordNo)
        {
            fwrite(&emp, sizeof(Employee), 1, temp);
        }

        count++;
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.dat", filename);

    printf("Record deleted successfully.\n");
}