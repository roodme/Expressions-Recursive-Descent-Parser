#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


void get();
int expr();
void term_tail(int* );
int term();
void factor_tail(int* );
int factor();

void term_rel_tail(int* );
int term_rel();
void factor_rel_tail(int* );

void term_log_tail(int* );
int term_log();
void factor_log_tail(int* );


char* tokens[] = {"(", "5", "<=", "5", "*", "(", "3", "+", "8", "*", "2", ">", "(", "1", "+", "6", ")", 
"&&", "1", "!=", "5", "*", "2", "-", "3", "*", "(", "3", "+", "2", ")", ")", "+", "4", ")", "+", "9", "*", "(", 
"29", "-", "-", "-1", "*", "90", "/", "5", ")"};

size_t size = 48;


size_t count;
static char* ahead;
bool all_good = false;


bool audit_int(char* number)   // Is it a non negative integer
{
    size_t length = -1;

    while(number[++length]);

    if (!(number[0] == '-' || isdigit(number[0]))) // Check if number is negative
        return false;

    for (size_t i = 1; i < length; i++)
    {
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}


void get()
{    
    if (++count == size)
        all_good = true;
    
    if (count < size)
        ahead = tokens[count];    
}


int log_expr()
{
    int value = term_log();

    term_log_tail(&value);

    return value;
}

int rel_expr()
{
    int value = term_rel();

    term_rel_tail(&value);

    return value;
}

int expr()
{
    int value = term();

    term_tail(&value);

    return value;
}



void term_log_tail(int* value)
{

    if (strcmp(ahead, "||") == 0)
    {
        get();

        int temp_val = rel_expr();

        *value = temp_val || *value;

        term_log_tail(value);
    }
}

int term_log()
{
    int value = rel_expr();

    factor_log_tail(&value);
    
    return value;
}

void factor_log_tail(int* value)
{
    
    if (strcmp(ahead, "&&") == 0)
    {
        get();

        int temp_val = rel_expr();

        *value = temp_val && *value;

        factor_log_tail(value);
    }   
}



void term_rel_tail(int* value)
{

    if (strcmp(ahead, "==") == 0)
    {
        get();

        int temp_val = term_rel();

        *value = (temp_val == *value);

        term_rel_tail(value);
    }
    else if (strcmp(ahead, "!=") == 0)
    {
        get();

        int temp_val = term_rel();
        
        *value = (temp_val != *value);

        term_rel_tail(value);
    }      
}

int term_rel()
{
    int value = expr();

    factor_rel_tail(&value);
    
    return value;
}

void factor_rel_tail(int* value)
{
    if (strcmp(ahead, ">=") == 0)
    {
        get();

        int temp_val = expr();
        
        *value = (*value >= temp_val);
        factor_rel_tail(value);
    }
    else if (strcmp(ahead, "<=") == 0)
    {
        get();

        int temp_val = expr();
        
        *value = (*value <= temp_val);
        factor_rel_tail(value);
    }
    else if (strcmp(ahead, ">") == 0)
    {
        get();

        int temp_val = expr();
        
        *value = (*value > temp_val);
        factor_rel_tail(value);
    }
    else if (strcmp(ahead, "<") == 0)
    {
        get();

        int temp_val = expr();
        
        *value = (*value < temp_val);
        factor_rel_tail(value);
    }
}



void term_tail(int* value)
{

    if (strcmp(ahead, "+") == 0)
    {
        get();

        int temp_val = term();

        *value += temp_val;

        term_tail(value);
    }
    else if (strcmp(ahead, "-") == 0)
    {
        get();

        int temp_val = term();

        *value -= temp_val;

        term_tail(value);
    }
}

int term()
{
    int value = factor();

    factor_tail(&value);
    
    return value;
}

void factor_tail(int* value)
{
    if (strcmp(ahead, "*") == 0 )
    {
        get();

        int temp_val = factor();

        *value *= temp_val;

        factor_tail(value);

    }
    else if (strcmp(ahead, "/") == 0)
    {
        get();

        int temp_val = factor();

        if (temp_val == 0)
        {
            printf("Division by 0!\n");
            exit(1);
        }

        *value /= temp_val;

        factor_tail(value);

    }
    else if (strcmp(ahead, "%") == 0)   // Ok with negatives, not ok with doubles
    {
        get();

        int temp_val = factor();

        if (temp_val == 0)
        {
            printf("Division by 0!\n");
            exit(1);
        }

        *value = *value % temp_val; 

        factor_tail(value);
    }    
}


int factor_no_neg_un_op()
{
    int value = 0;
    if (strcmp(ahead, "(") == 0)
    {
        get();
        value = log_expr();
        if (strcmp(ahead, ")") == 0)
            get();
        else
        {
            printf("Expected )\n");   
            exit(1);
        }
    }
    else if (strcmp(ahead, "-") == 0)
    { 
        printf("\nWrong format!\n");
        exit(0);
    }
    else if (strcmp(ahead, "!") == 0)
    { 
        get();
        value = !factor();
    }
    else if (audit_int(ahead))
    { 
        value = atoi(ahead);
        
        get();
    }
    else
    { 
        printf("factor expected\n");
        exit(1);
    }
    
    return value;
}


int factor()
{
    int value = 0;
    
    if (strcmp(ahead, "(") == 0)
    {
        get();
        value = log_expr();
        if (strcmp(ahead, ")") == 0)
            get();
        else
        {
            printf("Expected )\n");   
            exit(1);
        }
    }
    else if (strcmp(ahead, "-") == 0)
    { 
        get();
        value = -factor();
    }
    else if (strcmp(ahead, "+") == 0)
    { 
        get();
        value = factor();
    }
    else if (strcmp(ahead, "!") == 0)
    { 
        get();
        value = !factor();
    }
    else if (audit_int(ahead))
    { 
        value = atoi(ahead);
        get();
    }
    else
    { 
        printf("Factor expected\n");
        exit(1);
    }
    
    return value;
}


// Example use
void print_expr(char** tokens, int size, int res)
{
    for (size_t i = 0; i < size; i++)
        printf("%s ", tokens[i]);
    
    printf("= %d\n", res);
}

int main(void) 
{
    count = 0;
    ahead = tokens[0];
    
    int v = log_expr();
    
    if (all_good)
        print_expr(tokens, size, v);
    else
        printf("Error in parsing\n");

    return 0;
}