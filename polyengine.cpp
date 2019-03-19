
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include<iostream>
#include <fstream>

extern "C" int poly_engine(char* exe_data, size_t enc_beg_offset, size_t enc_size, size_t dec_offset);
using namespace std;
int main(int argc, char* argv[])
{


    if(argc != 5) {

        cout << "Invalid number of arguments!" << endl;
        return 1;
    }

	// seed the random number generator
	srand(time(NULL));

	// get the arguments
	const char* virus_name = argv[1];
	const size_t enc_offset  = strtol(argv[2], nullptr, 16);
	const size_t enc_size    = strtol(argv[3], nullptr, 16);
	const size_t dec_offset  = strtol(argv[4], nullptr, 16);




    ifstream ifd(virus_name, ios::binary | ios::ate);
    size_t exe_size = ifd.tellg();
    ifd.seekg(0, ios::beg);
    char* exe_data = new char[exe_size];
    ifd.read(exe_data, exe_size);
    
// This is the bug 
    cout << exe_size;
	printf("The size is %zd\n", exe_size);

	if(dec_offset >= exe_size)
	{
		printf("The offset in which to place the decrypt function is invalid\n");
	    free(exe_data); 	return 0;
	}
// End of bug 


	// call the polymorphic engine
	poly_engine(exe_data, enc_offset, enc_size, dec_offset);

    std::ofstream outfile ("virus_poly",std::ofstream::binary);
    // write to outfile
    outfile.write (exe_data,exe_size);
















    // for (int i = 0; i < argc; ++i) 
    //     cout << argv[i] << "\n"; 
    
    // poly_engine();

    // ifstream ifd("virus", ios::binary | ios::ate);
    // size_t size = ifd.tellg();
    // ifd.seekg(0, ios::beg);
    // char* virus_data = (char *)malloc(size);
    // ifd.read(virus_data, size);
    // // cout.write(virus_data, size);
    // cout << size;
    
    // size_t enc_beg_offset =  std::stoul(argv[2], nullptr, 16);
    // size_t enc_size =  std::stoul(argv[3], nullptr, 16);
    // size_t dec_offset =  std::stoul(argv[4], nullptr, 16);
    // cout << " "<< enc_beg_offset << " " << enc_size << " " << dec_offset << endl;
    // poly_engine(virus_data, enc_beg_offset, enc_size, dec_offset);

    // cout << "hello";

    // std::ofstream ofile("virus_poly", ios::binary);
    // ofile.write((char*) &virus_data, size);

    // std::ofstream outfile ("virus_poly",std::ofstream::binary);
    // // write to outfile
    // outfile.write (virus_data,size);

    // std::ifstream infile ("virus",std::ifstream::binary);
    // std::ofstream outfile ("virus_poly",std::ofstream::binary);

    // // get size of file
    // infile.seekg (0,infile.end);
    // int size = infile.tellg();
    // infile.seekg (0);

    // // allocate memory for file content
    // char* buffer = new char[size];
    // // char* buffer = (char *)malloc(size);

    // // read content of infile
    // infile.read (buffer,size);

    // poly_engine(buffer, enc_beg_offset, enc_size, dec_offset);
    // cout << "deepak"<< endl;
    // // write to outfile
    // outfile.write (buffer,size);
    // cout << "kumar"<< endl;
    // // release dynamically-allocated memory
    // delete[] buffer;
    // cout << "tivari"<< endl;
    // outfile.close();
    // infile.close();
    // cout << "wuut"<< endl;


	// // seed the random number generator
	// srand(time(NULL));

	// // get the arguments
	// const char* exe_filename = argv[1];
	// const size_t enc_offset  = strtol(argv[2], NULL, 16);
	// const size_t enc_size    = strtol(argv[3], NULL, 16);
	// const size_t dec_offset  = strtol(argv[4], NULL, 16);

	// // // open the executable file
	// // FILE* exe_file = fopen("virus", "rb");
	// // if(!exe_file)
	// // {
	// // 	printf("Failed to open %s\n", exe_filename);
	// // 	return -1;
	// // }



    // ifstream ifd("virus", ios::binary | ios::ate);
    // size_t exe_size = ifd.tellg();
    // ifd.seekg(0, ios::beg);
    // char* exe_data = (char *)malloc(exe_size);
    // ifd.read(exe_data, exe_size);
    // // cout.write(virus_data, size);
    // cout << exe_size;

	// // // get the size of the executable file
	// // size_t exe_size;
	// // fseek(exe_file, 0, SEEK_END);
	// // exe_size = ftell(exe_file);
	// // rewind(exe_file);

	// printf("The size is %zd\n", exe_size);
	
	// // // allocate the data
	// // char* exe_data =  (char *) malloc(exe_size);
	// // if(!exe_data)
	// // {
	// // 	fclose(exe_file);
	// // 	printf("Executable data allocation failed\n");
	// // 	return 1;
	// // }

	// // // read the entire executable file
	// // if(!fread(exe_data, exe_size, 1, exe_file))
	// // {
	// // 	fclose(exe_file);
	// // 	printf("Executable file read failed\n");
	// // free(exe_data); 	return 0;
	// // }

	// // // close the file
	// // fclose(exe_file);

	// // check the input parameters
	// // if(enc_offset >= exe_size)
	// // {
	// // 	printf("The offset of the section to encrypt is invalid\n");
	// // free(exe_data); 	return 0;
	// // }

	// if(dec_offset >= exe_size)
	// {
	// 	printf("The offset in which to place the decrypt function is invalid\n");
	//     free(exe_data); 	return 0;
	// }

	// // if(enc_size == 0 || (enc_size & 0x0F) != 0)
	// // {
	// // 	printf("The section to encrypt size must be a multiple of 16\n");
	// // free(exe_data); 	return 0;
	// // }

	// // call the polymorphic engine
	// if(poly_engine(exe_data, enc_offset, enc_size, dec_offset) != 0)
	// {
	// 	printf("An error occured in the polymorphic engine\n");
	// free(exe_data); 	return 0;
	// }



    // std::ofstream outfile ("virus_poly",std::ofstream::binary);
    // // write to outfile
    // outfile.write (exe_data,exe_size);




    return 0;
}

// https://stackoverflow.com/questions/22129349/reading-binary-file-to-unsigned-char-array-and-write-it-to-another
// https://stackoverflow.com/questions/43765881/c-reading-binary-files
// http://www.cplusplus.com/forum/beginner/176692/