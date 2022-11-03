#include <stdio.h>
#include <stdlib.h>
#include "operations.h"


void operation_addition (char num1_arr[], char num2_arr[], char result_arr[])
{   
    int sum = 0, remainder = 0, carry = 0, temp = 0;

    for (int i = MAX_INPUT_SIZE-2; i >= 0; i--){

        temp  = carry + num1_arr[i] + num2_arr[i] - (2*48);
        sum   = temp % 10;
        carry = temp / 10;
        result_arr[i+1] = sum + 48;
    }
    result_arr[0] = carry + 48;
}

void operation_subtraction (char num1_arr[], char num2_arr[], char result_arr[])
{
    
}

void operation_multiplication (char num1_arr[], char num2_arr[], char result_arr[])
{
    
}

void operation_division (char num1_arr[], char num2_arr[], char result_arr[])
{
    
}