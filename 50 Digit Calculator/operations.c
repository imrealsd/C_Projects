/* Included Header Files*/
#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include <string.h>

/*Static Function Prototypes*/
static int check_bigger_number(char *num1, char *num2);


/**
 * @brief  adds two number arrays
 * @retval none
 */
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

/**
 * @brief  subtract two number arrays
 * @retval none
 */
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

/**
 * @brief  multliplies two number arrays
 * @retval none
 */
void operation_multiplication (char num1_arr[], char num2_arr[], char result_arr[])
{   

    char temp_buff[MAX_INPUT_SIZE];
    int shift_val = 0, sum = 0, carry = 0, temp, result_index;
    memset(temp_buff, 0, MAX_INPUT_SIZE);

    /**
     * multiply all elements of num1 with one element of num2 ,  put resuls in temp_buff
     * multiply all elements of num1 with next element of num2 , add results with prev temp_buff elements [1 left shift]
     * continue for all num2 elements..
     */
    for (int i = MAX_INPUT_SIZE-2; i >= 0; i--){
        for (int j = MAX_INPUT_SIZE-2; j >= 0; j--){
            temp_buff[j-shift_val] += (num1_arr[j]-48) * (num2_arr[i]-48);
        }
        shift_val++;
    }

    /*Adjust carry of temp_buff and put final result in result_arr*/

    result_index = MULTIPLICATION_OUTPUT_SIZE - 2;
    
    for (int i = MAX_INPUT_SIZE-2; i >= 0; i--){

        temp = temp_buff[i] + carry;
        carry = temp / 10;
        sum = temp % 10;
        result_arr[result_index] = sum + 48;
        result_index--;
    }
    result_arr[result_index] = carry + 48;

    /*multi-out-size-1 elememt is null character*/
    result_arr[MULTIPLICATION_OUTPUT_SIZE-1] = 0;
}


/**
 * @brief  devides one number array  by another
 * @retval none
 */
void operation_division (char num1_arr[], char num2_arr[], char result_arr[], char remainder_arr[])
{
    if (!check_bigger_number(num1_arr, num2_arr)){
        printf("Decimal point not supported\n");
        return;
    }

    char uint_arr[MAX_INPUT_SIZE];
    char add_buff[MAX_INPUT_SIZE];
    char add_result_buff[ADDITION_OUTPUT_SIZE];
    char sub_buffer[MAX_INPUT_SIZE];
    char sub_result_buff[SUBTRACTION_OUTPUT_SIZE];
    int negative_flag = 0;
    
    memset(add_buff, '0', MAX_INPUT_SIZE);
    memset(sub_buffer, '0', MAX_INPUT_SIZE);
    memset(add_result_buff, '0', ADDITION_OUTPUT_SIZE);
    memset(sub_result_buff, '0', SUBTRACTION_OUTPUT_SIZE);
    memset(uint_arr, '0', MAX_INPUT_SIZE);

    uint_arr[MAX_INPUT_SIZE-2] = '1';

    while (check_bigger_number(num1_arr, num2_arr)){
        /**
         * do num1 - num2 , store result in sub_result_arr
         * clear num1 & copy sub_result into num1 
         * add add_buff with unit_arr store into add_result buff
         * copy add_result_buff to add_buff
         * repeat
         */
        operation_subtraction(num1_arr, num2_arr,sub_result_buff, &negative_flag);
        memset(num1_arr, '0', MAX_INPUT_SIZE);
        strcpy(num1_arr, sub_result_buff);
        operation_addition(add_buff, uint_arr, add_result_buff);
        memset(add_buff, '0', MAX_INPUT_SIZE);
        strcpy(add_buff, add_result_buff+1);
    }
    strcpy(result_arr, add_buff);
    strcpy(remainder_arr, num1_arr);

    result_arr[MAX_INPUT_SIZE-1] = 0;
    remainder_arr[MAX_INPUT_SIZE-1] = 0;
}   


/**
 * @brief  checks which number array holds larger value
 * @retval int
 */
static int check_bigger_number(char *num1, char *num2)
{   
    /*check for bigger element at same index */
    for (int i = 0; i < MAX_INPUT_SIZE-1; i++){

        /*if num1 is bigger return 1 else return 0*/
        if (num1[i] > num2[i])
            return 1;

        else if (num1[i] < num2[i])
            return 0;
    }
    /*if 2 numbers are same return 1*/
    return 1;
}

