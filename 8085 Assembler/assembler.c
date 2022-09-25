#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SOURCE_REG  6
#define DESTINATION_REG 4
#define MAX_LENGTH 20
#define UPPER_NIBBLE 6
#define LOWER_NIBBLE 7

FILE *input_asm_ptr, *output_hex_Ptr;
int line_count = 0;
int addr;

struct loop {                                         // for storing loop names

	char loop_name[MAX_LENGTH];
	int Addr;
	int count_flag;
	struct loop *next;

} *head;

void get_addr (void);
void write_addr (void);
void reset (char str[]);
void detect_level (char str[]);
void left_shift (char str[], int);
void record_level_details (char str[]);
void check_assembly_file_existance (void);
void scan_asm_and_write_hex_file (void);
void open_asm_and_create_hex_file (void);
void close_asm_and_hex_file (void);
void check_data_transfer_grp (char str[]);
void check_arithmatic_grp (char str[]);
void check_logical_grp (char str[]);
void check_brunch_grp (char str[]);
void check_input_output_grp (char str[]);
void check_machine_ctrl_grp (char str[]);
void check_line_count_of_asm_file (void);
void replace_level_with_address (void);
void split_and_put_addr (struct loop *ptr);
void open_hex_file (void);
void close_hex_file (void);
void write_level_after_jump_or_call (char str[], int);

int main()
{
	check_assembly_file_existance();
	check_line_count_of_asm_file();
	open_asm_and_create_hex_file();
	scan_asm_and_write_hex_file();
	close_asm_and_hex_file();
	replace_level_with_address();
	return 0;
}


void open_asm_and_create_hex_file (void)
{
	input_asm_ptr  = fopen("input.asm", "r");
	output_hex_Ptr = fopen("output.hex", "a");               // append mode
}

void close_asm_and_hex_file (void){

	fclose(input_asm_ptr);
	fclose(output_hex_Ptr);
	printf("\n::File is successfully assembled.\n");
}

void check_assembly_file_existance (void)
{
	input_asm_ptr = fopen("input.asm", "r");

	if (input_asm_ptr == NULL){

		printf("Could't Find Assembly File\n");
		return;

	} else {

		fclose(input_asm_ptr);
		printf("\n::Found Assembly File\n");
		printf("\n::Starting Assembling Process . . .\n");
	}
}

void check_line_count_of_asm_file (void)
{	
	char ch;
	input_asm_ptr = fopen("input.asm", "r");

	while ((ch = fgetc(input_asm_ptr)) != EOF){

		if (ch == '\n'){
			line_count++;
		}
	}
	fclose(input_asm_ptr);
}

void scan_asm_and_write_hex_file (void)
{	
	char instruction[MAX_LENGTH], ch, index = 0;
	get_addr();

	while (line_count--){

		write_addr();                                        // write adress for opcode 
		while ((ch = fgetc(input_asm_ptr))!= '\n'){          // read one line instruction

			instruction[index] = ch;
			index++;
		}
	
		index = 0;
		detect_level(instruction);
		check_data_transfer_grp(instruction);
		check_arithmatic_grp(instruction);
		check_logical_grp(instruction);
		check_brunch_grp(instruction);
		check_input_output_grp(instruction);
		check_machine_ctrl_grp(instruction);
		reset(instruction);
	}
}

void reset (char instruction[])
{
	int i;
	for (i = 0; i < MAX_LENGTH; i++){
		instruction[i] = '\0';
	}
}

void get_addr (void)
{
	printf("\n::Enter starting address:");
	scanf("%x", &addr);
}

void write_addr (void)
{
	fprintf(output_hex_Ptr,"%x: ", addr);
	addr++;
}

void check_data_transfer_grp (char instruction[])                                                // index 3  is space and 5 is comma
{
	 
	if (instruction[0] == 'M' && instruction[1] == 'O' && instruction[2] == 'V'){                 // for mov instruction

		if (instruction[DESTINATION_REG] == 'A' || instruction[DESTINATION_REG] == 'C'|| 
		    instruction[DESTINATION_REG] == 'E' || instruction[DESTINATION_REG] == 'L' ){

			if (instruction[DESTINATION_REG] == 'A'){

				fputc('7', output_hex_Ptr);

			} else if (instruction[DESTINATION_REG] == 'C'){

				fputc('4', output_hex_Ptr);

			} else if (instruction[DESTINATION_REG] == 'E'){

				fputc('5', output_hex_Ptr);

			} else if (instruction[DESTINATION_REG] == 'L'){

				fputc('6', output_hex_Ptr);

			} else {
				// nothing
			}

			/*----------------------------------------------*/

			if (instruction[SOURCE_REG] == 'A'){

				fputc('F', output_hex_Ptr);

			} else if (instruction[SOURCE_REG] == 'B'){

				fputc('8', output_hex_Ptr);

			} else if (instruction[SOURCE_REG] == 'C'){

				fputc('9', output_hex_Ptr);

			} else if (instruction[SOURCE_REG] == 'D'){

				fputc('A', output_hex_Ptr);

			}  else if (instruction[SOURCE_REG] == 'E'){

				fputc('B', output_hex_Ptr);

			}  else if (instruction[SOURCE_REG] == 'H'){

				fputc('C', output_hex_Ptr);

			}  else if (instruction[SOURCE_REG] == 'L'){

				fputc('D', output_hex_Ptr);

			}  else if (instruction[SOURCE_REG] == 'M'){

				fputc('E', output_hex_Ptr);

			} else {

				// nothing
			}


		} else if (instruction[DESTINATION_REG] == 'B' || instruction[DESTINATION_REG] == 'D'|| 
		instruction[DESTINATION_REG] == 'H' || instruction[DESTINATION_REG] == 'M' ){

			if (instruction[DESTINATION_REG] == 'B'){

				fputc('4', output_hex_Ptr);

			} else if (instruction[DESTINATION_REG] == 'D'){

				fputc('5', output_hex_Ptr);

			} else if (instruction[DESTINATION_REG] == 'H'){

				fputc('6', output_hex_Ptr);

			} else if (instruction[DESTINATION_REG] == 'M'){

				fputc('7', output_hex_Ptr);

			} else {
				// nothing
			}

			/*----------------------------------------------*/

			if (instruction[SOURCE_REG] == 'A'){

				fputc('7', output_hex_Ptr);

			} else if (instruction[SOURCE_REG] == 'B'){

				fputc('0', output_hex_Ptr);

			} else if (instruction[SOURCE_REG] == 'C'){

				fputc('1', output_hex_Ptr);

			} else if (instruction[SOURCE_REG] == 'D'){

				fputc('2', output_hex_Ptr);

			}  else if (instruction[SOURCE_REG] == 'E'){

				fputc('3', output_hex_Ptr);

			}  else if (instruction[SOURCE_REG] == 'H'){

				fputc('4', output_hex_Ptr);

			}  else if (instruction[SOURCE_REG] == 'L'){

				fputc('5', output_hex_Ptr);

			}  else if (instruction[SOURCE_REG] == 'M'){

				fputc('6', output_hex_Ptr);

			} else {

				// nothing
			}
		}

		fputc('\n', output_hex_Ptr);                                                           // newline

	} else if (instruction[0] == 'M' && instruction[1] == 'V' && instruction[2] == 'I'){       // for mvi instruction

		if (instruction[DESTINATION_REG] == 'A'){

			fputs("3E", output_hex_Ptr);

		} else if (instruction[DESTINATION_REG] == 'B'){

			fputs("06", output_hex_Ptr);

		} else if (instruction[DESTINATION_REG] == 'C'){

			fputs("0E", output_hex_Ptr);

		} else if (instruction[DESTINATION_REG] == 'D'){

			fputs("16", output_hex_Ptr);

		}  else if (instruction[DESTINATION_REG] == 'E'){

			fputs("1E", output_hex_Ptr);

		}  else if (instruction[DESTINATION_REG] == 'H'){

			fputs("26", output_hex_Ptr);

		}  else if (instruction[DESTINATION_REG] == 'L'){

			fputs("2E", output_hex_Ptr);

		}  else if (instruction[DESTINATION_REG] == 'M'){

			fputs("36", output_hex_Ptr);

		} else {

			// nothing
		}

		fputc('\n', output_hex_Ptr);
		write_addr();
		fputc(instruction[UPPER_NIBBLE], output_hex_Ptr);               // immidiate data
		fputc(instruction[LOWER_NIBBLE], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);                                    // new line


	} else if (instruction[0] == 'L' && instruction[1] == 'X' && instruction[2] == 'I'){    // for LXI instruction

		if (instruction[DESTINATION_REG] == 'B'){

			fputs("01", output_hex_Ptr);

		} else if (instruction[DESTINATION_REG] == 'D'){

			fputs("11", output_hex_Ptr);

		} else if (instruction[DESTINATION_REG] == 'H'){

			fputs("21", output_hex_Ptr);

		} else if (instruction[DESTINATION_REG] == 'S'){                // S for SP [ stack pointer]

			fputs("31", output_hex_Ptr);

			fputc('\n', output_hex_Ptr);
			write_addr();
			fputc(instruction[UPPER_NIBBLE + 3], output_hex_Ptr);                                  // immidiate 2 byte data's lower byte
			fputc(instruction[LOWER_NIBBLE + 3], output_hex_Ptr);
			fputc('\n', output_hex_Ptr);  

			write_addr();
			fputc(instruction[UPPER_NIBBLE + 1], output_hex_Ptr);                                     // immidiate 2 byte data's upper byte
			fputc(instruction[LOWER_NIBBLE + 1], output_hex_Ptr);
			fputc('\n', output_hex_Ptr); 
			
			return;

		} else {
			// nothing
		}

		fputc('\n', output_hex_Ptr);
		write_addr();
		fputc(instruction[UPPER_NIBBLE + 2], output_hex_Ptr);                                  // immidiate 2 byte data's lower byte
		fputc(instruction[LOWER_NIBBLE + 2], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);  

		write_addr();
		fputc(instruction[UPPER_NIBBLE], output_hex_Ptr);                                     // immidiate 2 byte data's upper byte
		fputc(instruction[LOWER_NIBBLE], output_hex_Ptr);
		fputc('\n', output_hex_Ptr); 


	} else if (instruction[0] == 'L' && instruction[1] == 'D' 
	&& instruction[2] == 'A' && instruction[3] != 'X'){                                         // for LDA instruction

		fputs("3A", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[UPPER_NIBBLE], output_hex_Ptr);                                        // 2 byte addr's lower byte
		fputc(instruction[LOWER_NIBBLE], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);  

		write_addr();
		fputc(instruction[UPPER_NIBBLE - 2], output_hex_Ptr);                                    // 2 byte addr's upper byte
		fputc(instruction[LOWER_NIBBLE - 2], output_hex_Ptr);
		fputc('\n', output_hex_Ptr); 


	} else if (instruction[0] == 'S' && instruction[1] == 'T' 
	&& instruction[2] == 'A' && instruction[3] != 'X'){                                        // for STA instuctuction

		fputs("32", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[UPPER_NIBBLE], output_hex_Ptr);                                      // 2 byte addr's lower byte
		fputc(instruction[LOWER_NIBBLE], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);  

		write_addr();
		fputc(instruction[UPPER_NIBBLE - 2], output_hex_Ptr);                                  // 2 byte addr's upper byte
		fputc(instruction[LOWER_NIBBLE - 2], output_hex_Ptr);
		fputc('\n', output_hex_Ptr); 


	} else if (instruction[0] == 'L' && instruction[1] == 'D' &&                               // for LDAX instruction
    instruction[2] == 'A' && instruction[3] == 'X'){

		if (instruction[5] == 'B'){

			fputs("0A", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[5] == 'D'){

			fputs("1A", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);
		}

	} else if (instruction[0] == 'S' && instruction[1] == 'T' &&                               // for STAX instruction
    instruction[2] == 'A' && instruction[3] == 'X'){

		if (instruction[5] == 'B'){

			fputs("02", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[5] == 'D'){

			fputs("12", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);
		}

	} else if (instruction[0] == 'L' && instruction[1] == 'H' &&                               // for LHLD instruction
    instruction[2] == 'L' && instruction[3] == 'D'){

		fputs("2A", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[UPPER_NIBBLE + 1], output_hex_Ptr);                                  // 2 byte addr's lower byte
		fputc(instruction[LOWER_NIBBLE + 1], output_hex_Ptr);
		fputc('\n', output_hex_Ptr); 

		write_addr();
		fputc(instruction[UPPER_NIBBLE - 1], output_hex_Ptr);                                  // 2 byte addr's upper byte
		fputc(instruction[LOWER_NIBBLE - 1], output_hex_Ptr);
		fputc('\n', output_hex_Ptr); 

	}  else if (instruction[0] == 'S' && instruction[1] == 'H' &&                               // for SHLD instruction
    instruction[2] == 'L' && instruction[3] == 'D'){

		fputs("22", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[UPPER_NIBBLE + 1], output_hex_Ptr);                                  // 2 byte addr's lower byte
		fputc(instruction[LOWER_NIBBLE + 1], output_hex_Ptr);
		fputc('\n', output_hex_Ptr); 

		write_addr();
		fputc(instruction[UPPER_NIBBLE - 1], output_hex_Ptr);                                  // 2 byte addr's upper byte
		fputc(instruction[LOWER_NIBBLE - 1], output_hex_Ptr);
		fputc('\n', output_hex_Ptr); 

	}  else if (instruction[0] == 'X' && instruction[1] == 'C' &&                               // for XCHG instruction
    instruction[2] == 'H' && instruction[3] == 'G'){

		fputs("EB", output_hex_Ptr);
		fputc('\n', output_hex_Ptr); 

	} else {
		// nothing
	}
		
}// end of data transfer function 




void check_arithmatic_grp (char instruction[])
{
	if (instruction[0] == 'A' && instruction[1] == 'D' && instruction[2] == 'D'){           // for ADD instruction

		if (instruction[4] == 'A'){

			fputs("87", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'B'){

			fputs("80", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'C'){

			fputs("81", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'D'){

			fputs("82", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'E'){

			fputs("83", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'H'){

			fputs("84", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'L'){

			fputs("85", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'M'){

			fputs("86", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else {
			// nothing
		}

	} else if (instruction[0] == 'A' && instruction[1] == 'D' && instruction[2] == 'C'){     // for ADC instruction

		if (instruction[4] == 'A'){

			fputs("8F", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'B'){

			fputs("88", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'C'){

			fputs("89", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'D'){

			fputs("8A", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'E'){

			fputs("8B", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'H'){

			fputs("8C", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'L'){

			fputs("8D", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'M'){

			fputs("8E", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else {
			// nothing
		}

	}  else if (instruction[0] == 'S' && instruction[1] == 'U' && instruction[2] == 'B'){     // for SUB instruction

		if (instruction[4] == 'A'){

			fputs("97", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'B'){

			fputs("90", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'C'){

			fputs("91", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'D'){

			fputs("92", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'E'){

			fputs("93", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'H'){

			fputs("94", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'L'){

			fputs("95", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'M'){

			fputs("96", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else {
			// nothing
		}

	}  else if (instruction[0] == 'S' && instruction[1] == 'B' && instruction[2] == 'B'){     // for SBB instruction

		if (instruction[4] == 'A'){

			fputs("9F", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'B'){

			fputs("98", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'C'){

			fputs("99", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'D'){

			fputs("9A", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'E'){

			fputs("9B", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'H'){

			fputs("9C", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'L'){

			fputs("9D", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'M'){

			fputs("9E", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else {
			// nothing
		}

	}  else if (instruction[0] == 'I' && instruction[1] == 'N' && instruction[2] == 'R'){     // for INR instruction

		if (instruction[4] == 'A'){

			fputs("3C", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'B'){

			fputs("04", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'C'){

			fputs("0C", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'D'){

			fputs("14", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'E'){

			fputs("1C", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'H'){

			fputs("24", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'L'){

			fputs("2C", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'M'){

			fputs("34", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else {
			// nothing
		}

	} else if (instruction[0] == 'D' && instruction[1] == 'C' && instruction[2] == 'R'){     // for DCR instruction

		if (instruction[4] == 'A'){

			fputs("3D", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'B'){

			fputs("05", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'C'){

			fputs("0D", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'D'){

			fputs("15", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'E'){

			fputs("1D", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'H'){

			fputs("25", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'L'){

			fputs("2D", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'M'){

			fputs("35", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else {
			// nothing
		}

	} else if (instruction[0] == 'D' && instruction[1] == 'A' && instruction[2] == 'D'){    // for DAD instruction

		if (instruction[4] == 'B'){
			
			fputs("09", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'D'){

			fputs("19", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'H'){

			fputs("29", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);
			
		} else if (instruction[4] == 'S'){

			fputs("39", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);
		} else {
			// do nothing
		}

	} else if (instruction[0] == 'I' && instruction[1] == 'N' && instruction[2] == 'X'){    // for INX instruction

		if (instruction[4] == 'B'){
			
			fputs("03", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'D'){

			fputs("13", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'H'){

			fputs("23", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);
			
		} else if (instruction[4] == 'S'){

			fputs("33", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);
		} else {
			// do nothing
		}

	} else if (instruction[0] == 'D' && instruction[1] == 'C' && instruction[2] == 'X'){    // for DCX instruction

		if (instruction[4] == 'B'){
			
			fputs("0B", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'D'){

			fputs("1B", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'H'){

			fputs("2B", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);
			
		} else if (instruction[4] == 'S'){

			fputs("3B", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);
		} else {
			// do nothing
		}

	} else if (instruction[0] == 'D' && instruction[1] == 'A' && instruction[2] == 'A'){       // for DAA instruction

		fputs("27", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'C' && instruction[1] == 'M' && instruction[2] == 'A'){       // for CMA instruction

		fputs("2F", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'C' && instruction[1] == 'M' && instruction[2] == 'C'){       // for CMC instruction

		fputs("3F", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'S' && instruction[1] == 'T' && instruction[2] == 'C'){       // for STC instruction

		fputs("37", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'A' && instruction[1] == 'D' && instruction[2] == 'I'){       // for ADI instruction

		fputs("C6", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[4], output_hex_Ptr);
		fputc(instruction[5], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'A' && instruction[1] == 'C' && instruction[2] == 'I'){       // for ACI instruction

		fputs("CE", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[4], output_hex_Ptr);
		fputc(instruction[5], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'S' && instruction[1] == 'U' && instruction[2] == 'I'){       // for SUI instruction

		fputs("D6", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[4], output_hex_Ptr);
		fputc(instruction[5], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'S' && instruction[1] == 'B' && instruction[2] == 'I'){       // for SBI instruction

		fputs("DE", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[4], output_hex_Ptr);
		fputc(instruction[5], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else {
		// nothing
	}
} // end of arithmatic group



void check_logical_grp (char instruction[])
{
	if (instruction[0] == 'A' && instruction[1] == 'N' && instruction[2] == 'A'){     // for ANA instruction

		if (instruction[4] == 'A'){

			fputs("A7", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'B'){

			fputs("A0", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'C'){

			fputs("A1", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'D'){

			fputs("A2", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'E'){

			fputs("A3", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'H'){

			fputs("A4", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'L'){

			fputs("A5", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'M'){

			fputs("A6", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else {
			// do nothing
		}

	} else if (instruction[0] == 'O' && instruction[1] == 'R' && instruction[2] == 'A'){        // for ORA instruction

		if (instruction[4] == 'A'){

			fputs("B7", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'B'){

			fputs("B0", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'C'){

			fputs("B1", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'D'){

			fputs("B2", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'E'){

			fputs("B3", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'H'){

			fputs("B4", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'L'){

			fputs("B5", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'M'){

			fputs("B6", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else {
			// do nothing
		}

	}  else if (instruction[0] == 'X' && instruction[1] == 'R' && instruction[2] == 'A'){        // for XRA instruction

		if (instruction[4] == 'A'){

			fputs("AF", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'B'){

			fputs("A8", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'C'){

			fputs("A9", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'D'){

			fputs("AA", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'E'){

			fputs("AB", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'H'){

			fputs("AC", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'L'){

			fputs("AD", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'M'){

			fputs("AE", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else {
			// do nothing
		}

	}  else if (instruction[0] == 'C' && instruction[1] == 'M' && instruction[2] == 'P'){        // for CMP instruction

		if (instruction[4] == 'A'){

			fputs("BF", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'B'){

			fputs("B8", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'C'){

			fputs("B9", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'D'){

			fputs("BA", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'E'){

			fputs("BB", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'H'){

			fputs("BC", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'L'){

			fputs("BD", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == 'M'){

			fputs("BE", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else {
			// do nothing
		}

	} else if (instruction[0] == 'R' && instruction[1] == 'L' && instruction[2] == 'C'){            // for RLC instruction

		fputs("07", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'R' && instruction[1] == 'R' && instruction[2] == 'C'){             // for RRC instruction

		fputs("0F", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'R' && instruction[1] == 'A' && instruction[2] == 'L'){             // for RAL instruction

		fputs("17", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'R' && instruction[1] == 'A' && instruction[2] == 'R'){             // for RAR instruction

		fputs("1F", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'A' && instruction[1] == 'N' && instruction[2] == 'I'){             // for ANI instruction

		fputs("E6", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[4], output_hex_Ptr);
		fputc(instruction[5], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'X' && instruction[1] == 'R' && instruction[2] == 'I'){             // for XRI instruction

		fputs("EE", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[4], output_hex_Ptr);
		fputc(instruction[5], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'O' && instruction[1] == 'R' && instruction[2] == 'I'){             // for ORI instruction

		fputs("F6", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[4], output_hex_Ptr);
		fputc(instruction[5], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'C' && instruction[1] == 'P' && instruction[2] == 'I'){             // for CPI instruction

		fputs("FE", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[4], output_hex_Ptr);
		fputc(instruction[5], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else {
		// do nothing
	}
} // end of logical group


void detect_level (char instruction[])
{
	int i, shift_amount;
	for (i = 0; instruction[i] != '\0'; i++){
		if (instruction[i] == ':'){

			record_level_details(instruction);
			shift_amount = i+2;
			left_shift(instruction, shift_amount);
		}
	}
}


void left_shift (char instruction[], int shift_amount)
{
	int i;

	while (shift_amount -- ){

		for (i = 0; i < MAX_LENGTH; i++){

			instruction[i] = instruction[i+ 1];
		}
	}
}

void record_level_details (char instruction[])
{
	char Loop_Name[MAX_LENGTH] = {0};
	int i;

	for (i = 0; instruction[i] != ':'; i++){                      // extract level name
		Loop_Name[i] = instruction[i];
	}


	struct loop *temp = (struct loop *)malloc(sizeof(struct loop));
	struct loop *ptr;

	if (head ==  NULL){

		temp->Addr = addr - 1;
		strcpy(temp->loop_name, Loop_Name);
		temp->count_flag = 0;
		temp->next = NULL;
		head = temp;

	} else {

		ptr = head;
		while (ptr->next != NULL){

			ptr = ptr->next;
		}
		ptr->next = temp;

		temp->Addr = addr - 1;
		strcpy(temp->loop_name, Loop_Name);
		temp->count_flag = 0;
		temp->next = NULL;
	}
}


void check_brunch_grp (char instruction[])
{
	if (instruction[0] == 'J' && instruction[1] == 'M' && instruction[2] == 'P'){      // JMP

		fputs("C3", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 4);


	} else if (instruction[0] == 'J' && instruction[1] == 'N' && instruction[2] == 'Z'){     // JNZ

		fputs("C2", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 4);

	} else if (instruction[0] == 'J' && instruction[1] == 'Z'){ // JZ

		fputs("CA", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 3);

	}else if (instruction[0] == 'J' && instruction[1] == 'N' && instruction[2] == 'C'){   // JNC

		fputs("D2", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 4);

	}else if (instruction[0] == 'J' && instruction[1] == 'C'){ // JC

		fputs("DA", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 3);

	}else if (instruction[0] == 'J' && instruction[1] == 'P' && instruction[2] == 'O'){    // JPO

		fputs("E2", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 4);

	}else if (instruction[0] == 'J' && instruction[1] == 'P' && instruction[2] == 'E'){  // JPE

		fputs("EA", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 4);

	}else if (instruction[0] == 'J' && instruction[1] == 'P'){  // JP

		fputs("F2", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 3);

	}else if (instruction[0] == 'J' && instruction[1] == 'M'){     // JM

		fputs("FA", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 3);

	}else if (instruction[0] == 'C' && instruction[1] == 'A' && instruction[2] == 'L' && instruction[3] == 'L'){  //CALL
 
		fputs("CD", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 5);

	}else if (instruction[0] == 'C' && instruction[1] == 'N' && instruction[2] == 'Z'){      // CNZ

		fputs("C4", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 4);

	}else if (instruction[0] == 'C' && instruction[1] == 'Z'){     // CZ

		fputs("CC", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 3);

	}else if (instruction[0] == 'C' && instruction[1] == 'N' && instruction[2] == 'C'){  // CNC

		fputs("D4", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 4);

	}else if (instruction[0] == 'C' && instruction[1] == 'C'){    // CC

		fputs("DC", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 3);

	}else if (instruction[0] == 'C' && instruction[1] == 'P' && instruction[2] == 'O'){      // CPO

		fputs("E4", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 4);

	} else if (instruction[0] == 'C' && instruction[1] == 'P' && instruction[2] == 'E'){   // CPE

		fputs("EC", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 4);

	} else if (instruction[0] == 'C' && instruction[1] == 'P'){    // CP

		fputs("F4	", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 3);

	} else if (instruction[0] == 'C' && instruction[1] == 'M'){  // CM

		fputs("FC", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_level_after_jump_or_call (instruction, 3);

	} else if (instruction[0] == 'R' && instruction[1] == 'E' && instruction[2] == 'T'){  // RET

		fputs("C9", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'R' && instruction[1] == 'N' && instruction[2] == 'Z'){  // RNZ

		fputs("C0", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'R' && instruction[1] == 'Z'){  // RZ

		fputs("C8", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'R' && instruction[1] == 'N' && instruction[2] == 'C'){  // RNC

		fputs("D0", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'R' && instruction[1] == 'C'){  // RC

		fputs("D8", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'R' && instruction[1] == 'P' && instruction[2] == 'O'){  // RPO

		fputs("E0", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'R' && instruction[1] == 'P' && instruction[2] == 'E'){  // RPE

		fputs("E8", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'R' && instruction[1] == 'P'){                      // RP

		fputs("F0", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'R' && instruction[2] == 'M'){                        // RM

		fputs("F8", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'P' && instruction[1] == 'C' &&                        // PCHL
	instruction[2] == 'H' && instruction[3] == 'L'){  

		fputs("E9", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	}
}


void write_level_after_jump_or_call (char instruction[], int index){

	write_addr();
	
	for (int i = index; (instruction[i] <= 90 && instruction[i] >= 65); i++){
		fputc(instruction[i], output_hex_Ptr);
	}
	fputc('\n', output_hex_Ptr);

	write_addr();

	for (int i = index; (instruction[i] <= 90 && instruction[i] >= 65); i++){
		fputc(instruction[i], output_hex_Ptr);
	}
	fputc('\n', output_hex_Ptr);
}


void check_input_output_grp (char instruction[])
{
	if (instruction[0] == 'I' && instruction[1] == 'N' && instruction[2] == ' '){

		fputs("DB", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[3], output_hex_Ptr);
		fputc(instruction[4], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if ( instruction[0] == 'O' && instruction[1] == 'U' && instruction[2] == 'T'){

		fputs("D3", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

		write_addr();
		fputc(instruction[4], output_hex_Ptr);
		fputc(instruction[5], output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
	}
}

void check_machine_ctrl_grp (char instruction[])
{
	if (instruction[0] == 'P' && instruction[1] == 'U' && 
	instruction[2] == 'S' && instruction[3] == 'H'){

		if (instruction[5] == 'B'){

			fputs("C5", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[5] == 'D'){

			fputs("D5", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[5] == 'H'){

			fputs("E5", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[5] == 'P' && instruction[6] == 'S' && instruction[7] == 'W'){

			fputs("F5",output_hex_Ptr);
			fputc('\n', output_hex_Ptr);
		}

	} else if (instruction[0] == 'P' && instruction[1] == 'O' && instruction[2] == 'P'){

		if (instruction[5] == 'B'){

			fputs("C1", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[5] == 'D'){

			fputs("D1", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[5] == 'H'){

			fputs("E1", output_hex_Ptr);
			fputc('\n', output_hex_Ptr);

		} else if (instruction[5] == 'P' && instruction[6] == 'S' && instruction[7] == 'W'){

			fputs("F1",output_hex_Ptr);
			fputc('\n', output_hex_Ptr);
		}

	} else if (instruction[0] == 'E' && instruction[1] == 'I'){

		fputs("FB",output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'D' && instruction[1] == 'I'){

		fputs("F3",output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'R' && instruction[1] == 'I' && instruction[2] == 'M'){

		fputs("20",output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'S' && instruction[1] == 'I' && instruction[2] == 'M'){

		fputs("30",output_hex_Ptr);
		fputc('\n', output_hex_Ptr);
		
	} else if (instruction[0] == 'R' && instruction[1] == 'S' && instruction[2] == 'T'){

		if (instruction[4] == '0'){

			fputs("C7",output_hex_Ptr);
		    fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == '1'){

			fputs("CF",output_hex_Ptr);
		    fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == '2'){

			fputs("D7",output_hex_Ptr);
		    fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == '3'){

			fputs("DF",output_hex_Ptr);
		    fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == '4'){

			fputs("E7",output_hex_Ptr);
		    fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == '5'){

			fputs("EF",output_hex_Ptr);
		    fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == '6'){

			fputs("F7",output_hex_Ptr);
		    fputc('\n', output_hex_Ptr);

		} else if (instruction[4] == '7'){

			fputs("FF",output_hex_Ptr);
		    fputc('\n', output_hex_Ptr);
		}

	} else if (instruction[0] == 'X' && instruction[1] == 'T' 
	&& instruction[2] == 'H' && instruction[3] == 'L'){

		fputs("E3", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'S' && instruction[1] == 'P' 
	&& instruction[2] == 'H' && instruction[3] == 'L'){

		fputs("F9", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'N' && instruction[1] == 'O' && instruction[2] == 'P'){

		fputs("00", output_hex_Ptr);
		fputc('\n', output_hex_Ptr);

	} else if (instruction[0] == 'H' && instruction[1] == 'L' && instruction[2 == 'T']){

		fputs("76\n", output_hex_Ptr);
	}
}

void replace_level_with_address (void)
{
	char temp[MAX_LENGTH] = {0};
	char zero[MAX_LENGTH] = {0};
	char ch = 0;
	struct loop *ptr;
	int i = 0;	

	open_hex_file();

	while (1){


		while ((ch = fgetc(output_hex_Ptr)) != '\n' && ch != EOF){       // read one line
			temp[i] = ch;
			i++;
		}

		if (ch == EOF){
			break;
		}

		for (i = 0; temp[i] != '\0'; i++){                              // omit address and take level name

			if (temp[i] == ':'){
				left_shift(temp, (i+2));
			}
		}

		ptr = head;
		while (ptr != NULL){
			
			if (strcmp(ptr->loop_name, temp) == 0){

				fseek(output_hex_Ptr,-(strlen(temp)+1), SEEK_CUR);
				split_and_put_addr(ptr);

				for (int i = 0; i < (strlen(temp) - 2); i++){               // remove extra parts of level name
					fputc(' ', output_hex_Ptr);
				}
				break;
			}
			ptr = ptr->next;
		}
		reset(temp);
		i = 0;
	}
	close_hex_file();
}

void open_hex_file (void)
{
	output_hex_Ptr = fopen("output.hex", "r+");
}

void close_hex_file (void)
{
	fclose(output_hex_Ptr);
}

void split_and_put_addr (struct loop *ptr)
{
	short upper = (ptr->Addr & 0xFF00) >> 8;
	short lower = (ptr->Addr & 0x00FF);

	if(ptr->count_flag == 0){
		
		if (lower <= 15){
			fputc('0',output_hex_Ptr);
		}
		fprintf(output_hex_Ptr,"%X", lower);
		ptr->count_flag = 1;

	} else {
		
		if (upper <= 15){
			fputc('0',output_hex_Ptr);
		}
		fprintf(output_hex_Ptr,"%X", upper);
	}
}
