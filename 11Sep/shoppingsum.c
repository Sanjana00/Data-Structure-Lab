#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc != 2) // incorrect number of command line arguments, expected 2
    {
        printf("Incorrect number of command line arguments\n");
        return 0;
    }
    FILE *fps;
    fps = fopen(argv[1], "r"); // opening shopping list file for reading
    if (fps == NULL) // error: file could not be opened
    {
        printf("File could not be opened\n");
        return 0;
    }
    float sum = 0.0, price, quantity;
    char item[20];
    int inp; // number of valid inputs in file
    while ((inp = fscanf(fps, "%s%f%f", item, &price, &quantity)) == 3) // while file contains three valid fields
    {
        sum += (price * quantity);
    }
    if (inp != -1) // inp = -1 when EOF reached (loop has not been terminated prematurely)
    {
        printf("File is not a valid shopping list\n");
        return 0;
    }
    // display
    printf("Rs. %.2f\n", sum);
    return 0;
}
