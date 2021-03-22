#include <stdio.h>
#include <stdlib.h>

// defining specifications of each record in the struct
struct item
{
    char itemName[20];
    float unitP;
    float itemQ;
};

int main(int argc, char* argv[])
{
    if (argc != 3) // expected number of command line arguments not found
    {
        printf("Incorrect number of command line arguments\n");
        return 0;
    }
    FILE *fps;
    fps = fopen(argv[1], "rb"); // opening binary file in read mode
    if (fps == NULL) // error: file could not be opened
    {
        printf("File could not be opened\n");
        return 0;
    }
    struct item record;
    int i = atoi(argv[2]); // copying int value of item number
    if (i < 1)
    {
        printf("Input must be a positive number\n");
        return 0;
    }
    fseek(fps, (i - 1) * sizeof(record), SEEK_SET); // setting pointer to item number position in file
    int f = fread(&record, sizeof(record), 1, fps); // reading item name, unit price and quantity
    if (f)
        printf("%s\t%f\t%f\n", record.itemName, record.unitP, record.itemQ); // display
    else
        printf("Could not read the record\n");
    fclose(fps); // closing file
    return 0;
}
