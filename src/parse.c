/*
 * Recursive descent parser to recognize input language for the SAT solver
 */

#include<stdio.h>

#ifdef DEBUG
#define debug_print(s) printf s ;
#else
#define debug_print(s) do { } while (0);
#endif


enum Symbol {lparen, rparen, variable, and, or, not};
char * sym_name[] = {"lparen", "rparen", "variable", "and", "or", "not"};
char variable_name[256] = {'\0'};


enum Symbol sym;
char  input[] = "(X AND Y)";
char * cursor = input;
char next_token[256] = {'\0'};

int count = 0;
enum Symbol tokens[] = {lparen, not, variable, and, lparen, variable, or, variable, rparen, rparen};

void skip_whitespace()
{
    
    while (*cursor == ' ') {
        cursor++;
    }
}
void nextsym()
{
    debug_print(("Input is %s\n", cursor));
    // Make sure the cursor is not NULL/at the end of the string
    if (*cursor == '\0') {
        debug_print(("Error in parsing\n"));
    }

    if (*cursor == '(') {
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
        while (*cursor != ' ' && *cursor != ')') {
            variable_name[idx] = *cursor;
            cursor++;
            idx++;
        }
        if (*cursor != ')') {
            cursor++;
        }
        variable_name[idx] = '\0';
        //printf("Variable name %s\n", variable_name);
    }
    skip_whitespace();

    debug_print(("Symbol is %s\n", sym_name[sym]));
    if (sym == variable) {
        debug_print(("Variable name %s\n", variable_name));
    }
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
    debug_print(("Error\n"));
    return 0;
    
}

void connective()
{
    if (accept(and))
       ;
    else if (accept(or))
       ;
    else {
        debug_print(("Error\n"));
    }
}


void literal()
{
    if (accept(not)) {
        debug_print(("Negation\n"));
        expect(variable);
    }
    else {
        expect(variable);
    }
}

void term()
{
    literal();
    if (accept(and)) {
        debug_print(("AND\n"));
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
    expect(lparen);
    term();
    expect(rparen);
}

int main()
{
    nextsym(); // initialize the stream of symbols
    start();
    
    debug_print(("Parsed!\n"));
    return 0;
}
