#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "operations.h"

void choose_option(void);
void copy_to_num_arr (char num[], char buff[], int8_t num_size);

int main(int argc, char *argv[])
{   
    int8_t cont = 1;

    while (cont){
        choose_option();
        printf("Want to Continue ? press 'y' for yes , 'n' for no:");
        scanf("%hhd", &cont);
    }
    return 0;
}


void choose_option(void)
{   
    char inpt_buff[MAX_INPUT_SIZE];
    char num1[MAX_INPUT_SIZE], num2[MAX_INPUT_SIZE];
    int8_t opt;

    printf("Choose operation:\n");
    printf("1.Addition, 2.Subtraction, 3.Multiplication, 4.Division\n");
    printf("Enter your choice:");
    scanf("%hhd", &opt);

    memset(inpt_buff,0,MAX_INPUT_SIZE);
    printf("input first number:");
    scanf("%s", inpt_buff);
    copy_to_num_arr(num1,inpt_buff,MAX_INPUT_SIZE);

    memset(inpt_buff,0,MAX_INPUT_SIZE);
    printf("input second number:");
    scanf("%s", inpt_buff);
    copy_to_num_arr(num2,inpt_buff,MAX_INPUT_SIZE);

    switch (opt){
    
    case 1:
        
    }
}

void copy_to_num_arr (char num[], char buff[], int8_t num_size)
{   
    /*Getting the difference between max size and input size to get right shifted new start index */

    int8_t input_size = strlen(buff);
    int8_t new_start_index = num_size - input_size - 1;  // 1 for null character

    memset(num,0,MAX_INPUT_SIZE);

    /* Right shifting the array in 2 steps:
     * step 1. filling empty left positions with '0' upto new_start_index - 1
     * step 2. copying the array from buffer [from index 0] to num [from new start index]
    */

    for (int8_t i = 0; i < new_start_index; i++){
        num[i] = '0';
    }
    for (int8_t i = 0; i < input_size; i++){
        num[new_start_index] = buff[i];
        new_start_index++;
    }

    printf("%s\n", num);
}