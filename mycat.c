//mycat
/*
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]) 
{
    FILE *fp;
    char ch;
    int i;

    if (argc < 2) 
    {
        printf("Usage: <file1> [<file2> <file3> ...]\n");
        return 1;  
    }

    for (i = 1; i < argc; i++)
     {
        fp = fopen(argv[i], "r");
        if (fp == NULL) 
        {
            perror("Error");
            continue;  
        }

        printf("Contents of %s:\n", argv[i]);
        while ((ch = fgetc(fp)) != EOF) 
        {
            printf("%c", ch);
        }

        fclose(fp);
        printf("\n");
    }

    return 0;
}



*/
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    FILE *fp;
    char buffer[BUFFER_SIZE];
    int i;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return 1;
    }

    for (i = 1; i < argc; i++)
    {
        printf("Contents of %s:\n", argv[i]);
        fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            perror("Error opening file");
            continue; // Move to the next file
        }

        while (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            printf("%s", buffer);
        }

        fclose(fp);
        printf("\n");
    }

    return 0;
}


































