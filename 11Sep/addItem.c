#include <stdio.h>
#include <stdlib.h>

// defining the specifications of each record
struct item
{
    char itemName[20];
    float unitP;
    float itemQ;
};

int main(int argc, char* argv[])
{
    if (argc != 5) // Not the correct number of command line arguments
    {
        printf("Incorrect number of command line arguments\n");
        return 0;
    }
    FILE *fps;
    fps = fopen(argv[1], "ab"); // opening binary file in append mode
    if (fps == NULL) // Error: Unable to open file
    {
        printf("File could not be opened\n");
        return 0;
    }
    struct item record;
    int i;
    for (i = 0; argv[2][i] != '\0'; i++) // copying name of item to character array in the record
        record.itemName[i] = argv[2][i];
    record.itemName[i] = '\0'; // terminating name of item
    record.unitP = atof(argv[3]); // copying float value of unit price
    record.itemQ = atof(argv[4]); // copying float value of item quantity
    fwrite(&record, sizeof(record), 1, fps); // appending record to file
    fclose(fps); // closing the file
    return 0;
}
