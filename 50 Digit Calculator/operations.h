#ifndef OPERATION_H
#define OPERATION_H

#define MAX_INPUT_SIZE 51                                          // MAX 50 digit  number
#define ADDITION_OUTPUT_SIZE           (MAX_INPUT_SIZE + 1)
#define SUBTRACTION_OUTPUT_SIZE        (MAX_INPUT_SIZE)
#define MULTIPLICATION_OUTPUT_SIZE     ((2*MAX_INPUT_SIZE)-1)
#define DIVISION_OUTPUT_SIZE           (MAX_INPUT_SIZE)

void operation_addition (char num1_arr[], char num2_arr[], char result_arr[]);
void operation_subtraction (char num1_arr[], char num2_arr[], char result_arr[]);
void operation_multiplication (char num1_arr[], char num2_arr[], char result_arr[]);
void operation_division (char num1_arr[], char num2_arr[], char result_arr[]);

#endif