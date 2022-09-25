#include <stdio.h>
#include <stdint.h>

void choose_options(void);
int64_t two_power(int8_t);
void bin_to_dec(void);

int64_t input_num = 0, output_num = 0;

int main(int argc, char* argv[])
{
    choose_options();
    return 0;
}

void choose_options(void)
{
    uint8_t choice, choice_count = 1;
    char units[5][20] = {"Binary","Decimal","Hexa-Decimal","Octal"};

    printf("Available Converters:\n");
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            if (i != j)
                printf("%d. %s To %s\n",choice_count++,units[i],units[j]);
        }
    }
    printf("\nEnter Choice: ");
    scanf("%hhd", &choice);

    switch (choice)
    {
    case 1:
        bin_to_dec();       
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
    output_num = 0;

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