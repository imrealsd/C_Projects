#ifndef OPERATION_H
#define OPERATION_H

#define MAX_INPUT_SIZE 51                                           // MAX 50 digit  number + 1 null caracter
#define ADDITION_OUTPUT_SIZE           (MAX_INPUT_SIZE + 1)         // MAX 51 digit  number + 1 null caracter
#define SUBTRACTION_OUTPUT_SIZE        (MAX_INPUT_SIZE)             // MAX 50 digit  number + 1 null caracter
#define MULTIPLICATION_OUTPUT_SIZE     ((2*MAX_INPUT_SIZE)-1)       // MAX 100 digit  number + 1 null caracter
#define DIVISION_OUTPUT_SIZE           (MAX_INPUT_SIZE)             // MAX 50 digit  number + 1 null caracter

void operation_addition (char num1_arr[], char num2_arr[], char result_arr[]);
void operation_subtraction (char num1_arr[], char num2_arr[], char result_arr[], int *negative_flag);
void operation_multiplication (char num1_arr[], char num2_arr[], char result_arr[]);
void operation_division (char num1_arr[], char num2_arr[], char result_arr[], char remainder_arr[]);

#endif