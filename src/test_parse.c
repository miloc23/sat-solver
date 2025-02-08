#include <stdio.h>

extern int parse(char *);


int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./parse STRING\n");
        return -1;
    }
    int err = parse(argv[1]);
    if (err) 
        printf("Failed to parse\n");
    else  
        printf("Parsed!\n");
    return 0;
}
