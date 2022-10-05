#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define BINARY_ARR_SIZE 17
#define HEX_ARR_SIZE 5


void choose_options(void);
int64_t two_power(int8_t);
int64_t sixteen_power(int8_t);
void bin_to_dec(void);
void dec_to_bin(void);
void bin_to_hex(void);
void reset_array(char[],uint8_t);
void hex_to_bin (void);
void hex_to_dec(void);
void dec_to_hex(void);


int64_t input_num = 0, output_num = 0;

int main(int argc, char* argv[])
{
    choose_options();
    return 0;
}

void choose_options(void)
{   
    int continue_flag = 1;
    char ch;

    while (continue_flag) {

        uint8_t choice; 
        printf("1. Binary  To Decimal\n");
        printf("2. Decimal To Binary\n");
        printf("3. Binary  To Hexadecimal\n");
        printf("4. Hexadecimal To Binary\n");
        printf("5. Hexadecimal To Decimal\n");
        printf("6. Decimal to Hexadecimal\n");

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
        case 4:
            hex_to_bin();
            break;
        case 5:
            hex_to_dec();
            break;
        case 6:
            dec_to_hex();
            break;
        default:
            break;
        }

        printf("\nPress 'c' to continue or 'e' to exit:");
        getchar();              // to get rid of the 'pressed enter' after typing 'c' or 'e'
        scanf("%c", &ch);
        (ch == 'c') ? (continue_flag = 1) : (continue_flag = 0);
    }
}

void dec_to_hex(void)
{   
    char hex_arr[HEX_ARR_SIZE];
    int8_t bin_buff[32];
    int8_t bin_index = 31;
    int8_t hex_index = 3;
    int8_t temp = 0;

    reset_array(hex_arr, HEX_ARR_SIZE);
    printf("\nEnter Decimal Number:[Max 65535]: ");
    scanf("%ld", &input_num);

    for (int8_t i = 0; i < 32; i++){bin_buff[i] = 0;}

    for (int8_t i = 0; i < 32; i++){
        if (input_num & (1 << i)){
            bin_buff[bin_index] = 1;
        } else {
            bin_buff[bin_index] = 0;
        }
        bin_index--;
    }

    bin_index = 31;

    for (int8_t i = 0; i < 32; i++){
        for (int8_t j = 0; j < 4; j++) {
            temp = temp + (bin_buff[bin_index] * two_power(j));
            bin_index--;
        }
        if (temp <= 9)
            hex_arr[hex_index] = temp + 48;
        else if (temp >= 10)
            hex_arr[hex_index] = temp + 55;

        temp = 0;
        hex_index--;
    }

    printf("Hexadecimal: 0x%s\n", hex_arr);
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
    uint8_t temp1 = 0, temp2 = 0, index = 3;

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
    printf("Hexadecimal: 0x%s\n",arr);
}

void hex_to_bin (void)
{   
    char bin_arr[BINARY_ARR_SIZE];
    char hex_arr[HEX_ARR_SIZE];
    printf("\nEnter Hex Number:[Max 4 digits, use capital]: 0x");
    scanf("%s", hex_arr);
    reset_array(bin_arr,BINARY_ARR_SIZE);
    uint8_t temp1 = 0, temp2 = 0, index = BINARY_ARR_SIZE-2;

    for (int8_t i = strlen(hex_arr)-1; i >= 0; i--){
        if (hex_arr[i] >= 65)
            temp1 = hex_arr[i] - 55;
        else
            temp1 = hex_arr[i] - 48;
            
        for (int j = 0; j <= 3; j++){
            
            if (temp1 & (1 << j))
                bin_arr[index] = '1';
            else
                bin_arr[index] = '0';
            index--;
        }
    }
    printf("BIN: %s\n",bin_arr);
}

void hex_to_dec(void)
{
    char hex_arr[HEX_ARR_SIZE];
    int8_t index = 0;
    printf("\nEnter Hex Number:[Max 4 digits, use capital]: 0x");
    scanf("%s", hex_arr);
    int8_t len = strlen(hex_arr);

    for (int8_t i = len-1; i >=  0; i--){
        if (hex_arr[i] <= '9'){
            output_num = output_num + (hex_arr[i]-48) * sixteen_power(index);
        } else if (hex_arr[i] >= 'A') {
            output_num = output_num + (hex_arr[i]-55) * sixteen_power(index);
        }
        index++;
    }
    printf("Decimal NUmber: %ld\n", output_num);
}

int64_t sixteen_power(int8_t val)
{
    int64_t result = 1;
    while (val--) {
        result = result * 16;
    }
    return result;
}

void reset_array(char arr[], uint8_t size)
{   
    arr[size-1] = 0;
    for (uint8_t i = 0; i < size-1; i++){
        arr[i] = '0';
    }
}