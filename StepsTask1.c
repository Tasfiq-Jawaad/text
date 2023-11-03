#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct
{
    char date[11];
    char time[6];
    int steps;
} FITNESS_DATA;

// Define any additional variables here

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps)
{
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);

    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL)
    {
        strcpy(date, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strcpy(time, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strcpy(steps, token);
    }

    // Free the duplicated string
    free(inputCopy);
}

// counting number of records to create structured array of appropiate size
int getNumOfRecord(char line_buffer[], char buffer_size, FILE *file)
{
    int record = 0;
    while (fgets(line_buffer, buffer_size, file) != NULL)
    {
        record++;
    }
    return record;
}

// Complete the main function
int main()
{
    char *filename = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening the file\n");
        return 1;
    }

    int buffer_size = 100, iterator = 0;

    char line_buffer[buffer_size], delimiter[] = {','};

    int record = getNumOfRecord(line_buffer, buffer_size, file);

    fclose(file);

    file = fopen(filename, "r");

    FITNESS_DATA data[record];

    while (fgets(line_buffer, buffer_size, file) != NULL)
    {
        char steps[8];
        tokeniseRecord(line_buffer, delimiter, data[iterator].date, data[iterator].time, steps);
        data[iterator].steps = atoi(steps);
        iterator++;
    }

    printf("Number of records in file: %d", record);
    for (int i = 0; i < 3; i++)
    {
        printf("\n%s/%s/%d", data[i].date, data[i].time, data[i].steps);
    }

    fclose(file);
    return 0;
}
