/*
 * Recursive descent parser to recognize input language for the SAT solver
 */

#include <stdio.h>
#include <stdbool.h>

#ifdef DEBUG
#define debug_print(s) printf s ;
#else
#define debug_print(s) do { } while (0);
#endif

bool error = false;
bool end_of_stream = false;

enum Symbol {lparen, rparen, variable, and, or, not, end, startsym};
char * sym_name[] = {"lparen", "rparen", "variable", "and", "or", "not", "end", "start"};
char variable_name[256] = {'\0'};


enum Symbol sym = startsym;
//char  input[] = "(NOT ((NOT X) AND Y))";
//char input[] = "(X AND Y)";
char * input;
char * cursor;
char next_token[256] = {'\0'};

int count = 0;
enum Symbol tokens[] = {lparen, not, variable, and, lparen, variable, or, variable, rparen, rparen};

void skip_whitespace()
{
    while (*cursor == ' ' && *cursor != '\0') {
        cursor++;
    }
}

bool nextsym()
{
    //debug_print(("Input is %s\n", cursor));
    // Make sure the cursor is not NULL/at the end of the string
    if (*cursor == '\0') {
        sym = end;
    }
    else if (*cursor == '(') {
        sym = lparen;
        cursor++;
    }
    else if (*cursor == ')') {
        sym = rparen;
        cursor++;
    }
    else if (*cursor == 'A') {
        sym = and;
        cursor += 4;
    }
    else if (*cursor == 'O') {
        sym = or;
        cursor += 3;
    }
    else if (*cursor == 'N') {
        sym = not;
        cursor += 4;
    }
    else {
        sym = variable;
        int idx = 0;
        while (*cursor != ' ' && *cursor != ')' && *cursor != '\0') {
            variable_name[idx] = *cursor;
            cursor++;
            idx++;
        }
        //if (*cursor == '\0') {

        if (*cursor != ')') {
            cursor++;
        }
        variable_name[idx] = '\0';
        //printf("Variable name %s\n", variable_name);
    }
    debug_print(("sym: %s\t Cursor is %s\n", sym_name[sym], cursor));
    skip_whitespace();

    //debug_print(("Symbol is %s\n", sym_name[sym]));
    if (sym == variable) {
        //debug_print(("Variable name %s\n", variable_name));
    }
    return true;
}

/*
 * This function allows us to check to see what token we have
 */
int accept(enum Symbol esym)
{
    if (sym == esym) {
        nextsym();
        return 1;
    }
    return 0;
}

int expect(enum Symbol esym)
{
    if (accept(esym)) {
        return 1;
    }
    //debug_print(("Error\n"));
    error = true;
    return 0;
    
}

void connective()
{
    if (accept(and))
       ;
    else if (accept(or))
       ;
    else {
        //debug_print(("Error\n"));
    }
}


void literal()
{
    if (accept(lparen)) {
        expect(not);
        expect(variable);
        expect(rparen);
    }
    else {
        expect(variable);
    }
}

void term()
{
    if (accept(not)) {
        expect(lparen);
        term();
        expect(rparen);
        return;
    }

    literal();
    if (accept(and)) {
        //debug_print(("AND\n"));
        if (accept(lparen)) {
            if (accept(not)) {
                term();
            }
            else {        
                term();
            }
            expect(rparen);
        }
        else {
            literal();
        }
    }
    else if (accept(or)) {
        if (accept(lparen)) {
            if (accept(not)) {
                term();
            }
            else {        
                term();
            }
            expect(rparen);
        }
        else {
            literal();
        }
    }
}

void start()
{
    nextsym(); // initialize the stream of symbols
    expect(lparen);
    term();
    expect(rparen);
    expect(end);
}

int parse(char * in)
{
    error = false;
    sym = startsym;
    input = in;
    cursor = in;
    start();
    if (error) {
        return 1;
    }
    else {  
        return 0;
    }
}
