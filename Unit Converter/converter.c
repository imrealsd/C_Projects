#include <stdio.h>
#include <stdint.h>
#define BINARY_ARR_SIZE 17
#define HEX_ARR_SIZE 5

void choose_options(void);
int64_t two_power(int8_t);
void bin_to_dec(void);
void dec_to_bin(void);
void bin_to_hex(void);
void reset_array(char[],int);

int64_t input_num = 0, output_num = 0;

int main(int argc, char* argv[])
{
    choose_options();
    return 0;
}

void choose_options(void)
{
    uint8_t choice;
    printf("1. Binary  To Decimal\n");
    printf("2. Decimal To Binary\n");
    printf("3. Binary  To Hexadecimal\n");
    printf("\nEnter Choice: ");
    scanf("%hhd", &choice);
    output_num = 0;
 
    switch (choice)
    {
    case 1:
        bin_to_dec();       
        break;
    case 2:
        dec_to_bin();
        break;
    case 3:
        bin_to_hex();
        break;
    default:
        break;
    }
}

void bin_to_dec (void)
{   
    printf("\nEnter Binary Number:[Max 16 bits]: ");
    scanf("%ld", &input_num);
    int temp, index = 0;

    while (input_num){
        temp = input_num % 10;
        output_num = output_num + (temp * two_power(index));
        index++;
        input_num = input_num / 10;
    }
    printf("Decimal: %ld\n", output_num);
}

int64_t two_power(int8_t pow)
{   
    int64_t result = 1;
    for (int8_t i = 0; i < pow; i++){
        result = result * 2;
    }
    return result;
}

void dec_to_bin (void)
{   
    printf("\nEnter Decimal Number:[Max 65535]: ");
    scanf("%ld", &input_num);
    int temp, index = 0;

    /* binary array size = 16 + null char = 17 */
    char result[BINARY_ARR_SIZE];
    reset_array(result,BINARY_ARR_SIZE);

    /* output bits = 16 = array_size -1 = 0 to 15 */
    for (uint8_t i = 0; i < BINARY_ARR_SIZE-1; i++){
        if (input_num & (1 << i)){
            result[16-i-1] = '1';
        } else{
            result[16-i-1] = '0';
        }
    }
    printf("Binary: %s\n", result);
}

void bin_to_hex(void)
{
    printf("\nEnter Binary Number:[Max 16 bits]: ");
    scanf("%ld", &input_num);
    char arr[HEX_ARR_SIZE] = {'0','0','0','0',0};
    int temp1 = 0, temp2 = 0, index = 3;

    while (input_num){
        for (int8_t i = 0; i < 4; i++){
            temp1 = input_num % 10;
            temp2 += temp1 *  two_power(i);
            input_num = input_num / 10;
        }
        if (temp2 <= 9)
            arr[index] = temp2 + 48;
        else 
            arr[index] = temp2 + 55; /* 10 + 55 = 65 = 'A */
        index--;
        temp1 = 0;
        temp2 = 0;
    }
    printf("Hex: %s\n",arr);
}

void reset_array(char arr[], int size)
{
    for (uint8_t i = 0; i < size; i++){
        arr[i] = 0;
    }
}