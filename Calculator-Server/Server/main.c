/*Included Header Files*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "operations.h"
#include "server.h"


/* Static Function Prototypes */
static void initiate_operation(char *, char *, int *);
static void display_result(char *result, int size);

/*Global Variables*/
char inpt_buff[MAX_INPUT_SIZE];
char num1[MAX_INPUT_SIZE], num2[MAX_INPUT_SIZE];
char add_result[ADDITION_OUTPUT_SIZE], sub_result[SUBTRACTION_OUTPUT_SIZE];
char multi_result[MULTIPLICATION_OUTPUT_SIZE], div_result[DIVISION_OUTPUT_SIZE];
char div_remainder[DIVISION_OUTPUT_SIZE];
int negative_flag = 0, choice, cont = 1;


/**
 * @brief  program entry point
 * @retval int
 */
int main(int argc, char *argv[])
{   
    if (argc < 2){
        printf("Port not provided\n");
        return 1;
    }   

    setup_server(argv[1]);

    while(1){

        printf("hello\n");
        waitFor_client();

        while (cont){

            get_input(num1, num2, &choice);
            initiate_operation(num1, num2, &choice);
        }
        close_connection();
    }
    return 0;
}


/**
 * @brief  getting user's operation choice & inputs , calling chosen operation func & display  func
 * @retval none
 */
static void initiate_operation(char *num1, char *num2, int *choice)
{   
    int opt = *choice;
    switch (opt){
    
    case 1:
        /*reset result array, add numbers & display result*/
        memset(add_result,0,ADDITION_OUTPUT_SIZE);
        operation_addition(num1,num2,add_result);
        display_result(add_result, ADDITION_OUTPUT_SIZE);
        send_output(add_result);
        break;
    
    case 2:
        /*reset result array, subtract numbers & display result*/
        memset(sub_result,0,SUBTRACTION_OUTPUT_SIZE);
        operation_subtraction(num1,num2,sub_result, &negative_flag);
        display_result(sub_result, SUBTRACTION_OUTPUT_SIZE);
        if (negative_flag == 1)
            send_output("-");
        else
            send_output("+");
        send_output(sub_result);
        break;

    case 3:
        /*reset result array, multiply numbers & display result*/
        memset(multi_result,'0',MULTIPLICATION_OUTPUT_SIZE);
        operation_multiplication(num1, num2, multi_result);
        display_result(multi_result, MULTIPLICATION_OUTPUT_SIZE);
        send_output(multi_result);
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
        send_output(div_result);
        send_output(div_remainder);
        break;
    }
    negative_flag = 0;
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
    if (choice == 2 && negative_flag){printf("-");}
    

    /*print only after the first non zero element is found*/
    for (int i = 0; i < size; i++){
        
        if (result[i] != '0')
            first_num_encountered_flag = 1;

        if (first_num_encountered_flag == 1)
            printf("%c", result[i]);
    }
    printf("\n");
}