#include <iostream> 
#include <fstream> 
using namespace std; 

extern "C" int poly_engine(char* exe_data, size_t enc_beg_offset, size_t enc_size, size_t dec_offset);

int  main(int argc, char** argv){
    // for (int i = 0; i < argc; ++i) 
    //     cout << argv[i] << "\n"; 
    
    // poly_engine();

    ifstream ifd("virus", ios::binary | ios::ate);
    size_t size = ifd.tellg();
    ifd.seekg(0, ios::beg);
    char* virus_data = (char *)malloc(size);
    ifd.read(virus_data, size);
    cout.write(virus_data, size);
    cout << size;
    
    size_t enc_beg_offset =  std::stoul(argv[1], nullptr, 16);
    size_t enc_size =  std::stoul(argv[2], nullptr, 16);
    size_t dec_offset =  std::stoul(argv[3], nullptr, 16);
    cout << enc_beg_offset << " " << enc_size << " " << dec_offset << endl;
    poly_engine(virus_data, enc_beg_offset, enc_size, dec_offset);

    return 0; 
}


// https://stackoverflow.com/questions/43765881/c-reading-binary-files
// http://www.cplusplus.com/forum/beginner/176692/