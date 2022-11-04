#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
static int check_bigger_number(char *num1, char *num2);


void operation_addition (char num1_arr[], char num2_arr[], char result_arr[])
{   
    int sum = 0, remainder = 0, carry = 0, temp = 0;

    /*add ith index elements of the two array, put sum in result & propagate carry*/
    for (int i = MAX_INPUT_SIZE-2; i >= 0; i--){

        temp  = carry + num1_arr[i] + num2_arr[i] - (2*48);
        sum   = temp % 10;
        carry = temp / 10;
        result_arr[i+1] = sum + 48;
    }
    /*put final carry in the 0th position of result*/
    result_arr[0] = carry + 48;
}


void operation_subtraction (char num1_arr[], char num2_arr[], char result_arr[], int* negative_flag)
{
    int borrow = 0, diff = 0, temp = 0;
    char *big_num, *small_num;

    /* check bigger number array & asssign them to big_num , smmall_num arrays
     * update negative_flag accordingly [1st num > 2nd num => flag = 0] [1st num < 2nd num => flag = 1]
    */ 
    if (check_bigger_number(num1_arr, num2_arr)){
        big_num = num1_arr;
        small_num = num2_arr;
        *negative_flag = 0;
    } else {
        big_num = num2_arr;
        small_num = num1_arr;
        *negative_flag = 1;
    }

    /* subtract ith index elements if subtraction is greater than zero , borrow = 0, diff = temp 
     * else borrow = 1 & diff = 10 + temp
     * put diff in result_arr then propagate borrow
     */
    for (int i = MAX_INPUT_SIZE-2; i >= 0; i--){

        temp = big_num[i] - small_num[i] - borrow;

        if (temp >= 0){
            diff = temp;
            borrow = 0;

        } else {
            diff = 10 + temp;
            borrow = 1;
        }
        result_arr[i] = diff + 48;
    }
}


void operation_multiplication (char num1_arr[], char num2_arr[], char result_arr[])
{
    
}

void operation_division (char num1_arr[], char num2_arr[], char result_arr[])
{
    
}

static int check_bigger_number(char *num1, char *num2)
{   
    /*check for bigger element at same index */
    for (int i = 0; i < MAX_INPUT_SIZE-1; i++){

        if (num1[i] > num2[i])
            return 1;

        else if (num1[i] < num2[i])
            return 0;
    }
    /*if 2 numbers are same return 1*/
    return 1;
}