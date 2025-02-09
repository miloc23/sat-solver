#include <stdio.h>
#include <stdlib.h>

extern int parse(char *);

int read_test(FILE * tests, char * input, int * result, char *test_info)
{
    char res_buf[4];
    if (fgets(input, 1024, tests) == NULL)
        return -1;
    for (int i = 0; i < 1024; i++) {
        if (input[i] == '\n') {
            input[i] = '\0';
            break;
        }
    }
    if (fgets(res_buf, 4, tests) == NULL)
        return -1;
    *result = atoi(res_buf);
    if (fgets(test_info, 1024, tests) == NULL)
        return -1;
    return 0;
}

int run_test(char * input, int result) 
{
    return result == parse(input);
}

void print_test_result(int test_num, char * test_input, char * test_info, int test_result)
{
    if (test_result) {
        printf("Test %3d Passed\n%s\n%s\n", test_num, test_input, test_info);
    }
    else {
        printf("Test %3d Failed\n%s\n%s\n", test_num, test_input, test_info);
    }
}
        

int main(int argc, char *argv[])
{
    /*
     * Testing proceudre:
     * 1. open the file
     * 2. read 3 lines from the file - 1 is string 2 is result 3 is test info
     * 3. repeat for all lines
     */
    FILE * tests = fopen("parsing_tests.txt", "r");
    if (tests == NULL) {
        printf("Error opening tests\n");
        return -1;
    }

    // The input string
    char * input = calloc(1, 1024);
    // Does the string parse or not
    int result;
    //char * result = calloc(1, 1024);
    // Test description
    char * test_info = calloc(1, 1024);

    int test_result = 0;
    int test_num = 0;

    while (!feof(tests)) {
        // Read in the test
        if(read_test(tests, input, &result, test_info))
            break;
        // Run the test
        test_result = run_test(input, result);
        // Print test
        print_test_result(test_num, input, test_info, test_result);
        // Increment test number
        test_num++;
    }

    return 0;
}
