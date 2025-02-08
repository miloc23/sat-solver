/*
 * Recursive descent parser to recognize input language for the SAT solver
 */

#include<stdio.h>

enum Symbol {lparen, rparen, variable, and, or, not};
char * sym_name[] = {"lparen", "rparen", "variable", "and", "or", "not"};
char variable_name[256] = {'\0'};


enum Symbol sym;
char  input[] = "(X AND Y)";
char * cursor = input;
char next_token[256] = {'\0'};

int count = 0;
enum Symbol tokens[] = {lparen, not, variable, and, lparen, variable, or, variable, rparen, rparen};

void nextsym()
{
    printf("Input is %s\n", cursor);
    // Make sure the cursor is not NULL/at the end of the string
    if (*cursor == '\0') {
        printf("Error in parsing\n");
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

    printf("Symbol is %s\n", sym_name[sym]);
    if (sym == variable) {
        printf("Variable name %s\n", variable_name);
    }
    

    //sym = tokens[count];
    //printf("Sym is %s\n", sym_name[sym]);
    //count++;
    /* Get the next token and put into next_token */
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
    printf("Error\n");
    return 0;
    
}

void connective()
{
    if (accept(and))
       ;
    else if (accept(or))
       ;
    else {
        printf("Error\n");
    }
}


void literal()
{
    if (accept(not)) {
        printf("Negation\n");
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
        printf("AND\n");
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
    
    printf("Parsed!\n");
    return 0;
}
