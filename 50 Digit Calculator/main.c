/*Included Header Files*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "operations.h"


/* Static Function Prototypes */
static void choose_option(void);
static void copy_to_num_arr (char num[], char buff[], int num_size);
static void display_result(char *result, int size);

/*Global Variables*/
char inpt_buff[MAX_INPUT_SIZE];
char num1[MAX_INPUT_SIZE], num2[MAX_INPUT_SIZE];
char add_result[ADDITION_OUTPUT_SIZE], sub_result[SUBTRACTION_OUTPUT_SIZE];
char multi_result[MULTIPLICATION_OUTPUT_SIZE], div_result[DIVISION_OUTPUT_SIZE];
char div_remainder[DIVISION_OUTPUT_SIZE];
int negative_flag;


/**
 * @brief  program entry point
 * @retval int
 */
int main(int argc, char *argv[])
{   
    int cont = 1;

    while (cont){
        choose_option();
        printf("\nWant to Continue ? press '1' for yes , '0' for no:");
        scanf("%d", &cont);
    }
    return 0;
}



/**
 * @brief  getting user's operation choice & inputs , calling chosen operation func & display  func
 * @retval none
 */
static void choose_option(void)
{   
    int opt = 0;

    /*print options & get choice of operations from user*/
    printf("\nChoose operation:\n");
    printf("1.Addition \n2.Subtraction  \n3.Multiplication  \n4.Division\n");
    printf("Enter your choice:");
    scanf("%d", &opt);

    /*reset input_buff & get 1st number & copy it to num1 array [right shifted]*/
    memset(inpt_buff,0,MAX_INPUT_SIZE);
    printf("\ninput first number :");
    scanf("%s", inpt_buff);
    copy_to_num_arr(num1,inpt_buff,MAX_INPUT_SIZE);

    /*reset input_buff & get 2nd number & copy it to num2 array [right shifted]*/
    memset(inpt_buff,0,MAX_INPUT_SIZE);
    printf("input second number:");
    scanf("%s", inpt_buff);
    copy_to_num_arr(num2,inpt_buff,MAX_INPUT_SIZE);


    switch (opt){
    
    case 1:
        /*reset result array, add numbers & display result*/
        memset(add_result,0,ADDITION_OUTPUT_SIZE);
        operation_addition(num1,num2,add_result);
        display_result(add_result, ADDITION_OUTPUT_SIZE);
        break;
    
    case 2:
        /*reset result array, subtract numbers & display result*/
        memset(sub_result,0,SUBTRACTION_OUTPUT_SIZE);
        operation_subtraction(num1,num2,sub_result, &negative_flag);
        display_result(sub_result, SUBTRACTION_OUTPUT_SIZE);
        break;

    case 3:
        /*reset result array, multiply numbers & display result*/
        memset(multi_result,'0',MULTIPLICATION_OUTPUT_SIZE);
        operation_multiplication(num1, num2, multi_result);
        display_result(multi_result, MULTIPLICATION_OUTPUT_SIZE);
        break;

    case 4:
        /*reset result array, divide num1 by num2 & display result & remainder*/
        memset(div_result,'0', DIVISION_OUTPUT_SIZE);
        memset(div_remainder, '0', DIVISION_OUTPUT_SIZE);
        operation_division(num1, num2, div_result, div_remainder);
        printf("Quotient ");
        display_result(div_result, DIVISION_OUTPUT_SIZE);
        printf("Remainder ");
        display_result(div_remainder, DIVISION_OUTPUT_SIZE);
       
        break;
    }
}


/**
 * @brief  copy and arrange input number to respective number array
 * @retval none
 */
static void copy_to_num_arr (char num[], char buff[], int num_size)
{   
    /*Getting the difference between max size and input size to get right shifted new start index */

    int input_size = strlen(buff);
    int new_start_index = num_size - input_size - 1;  // 1 for null character

    memset(num,0,MAX_INPUT_SIZE);

    /* Right shifting the array in 2 steps:
     * step 1. filling empty left positions with '0' upto new_start_index - 1
     * step 2. copying the array from buffer [from index 0] to num [from new start index]
    */

    for (int i = 0; i < new_start_index; i++){
        num[i] = '0';
    }
    for (int i = 0; i < input_size; i++){
        num[new_start_index] = buff[i];
        new_start_index++;
    }
}


/**
 * @brief  Display result after calculation
 * @retval none
 */
static void display_result(char *result, int size)
{   
    int first_num_encountered_flag = 0;
    printf("Result: ");

    /*print negative sign in case subtraction: [negative-flag = 1]*/
    if (negative_flag){printf("-");}

    /*print only after the first non zero element is found*/
    for (int i = 0; i < size; i++){
        
        if (result[i] != '0')
            first_num_encountered_flag = 1;

        if (first_num_encountered_flag == 1)
            printf("%c", result[i]);
    }
    printf("\n");
}