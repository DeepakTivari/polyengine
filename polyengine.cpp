#include <iostream> 
#include <fstream> 
using namespace std; 

extern "C" int poly_engine(char* exe_data, size_t enc_beg_offset, size_t enc_size, size_t dec_offset);

int  main(int argc, char** argv){
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
    
    size_t enc_beg_offset =  std::stoul(argv[2], nullptr, 16);
    size_t enc_size =  std::stoul(argv[3], nullptr, 16);
    size_t dec_offset =  std::stoul(argv[4], nullptr, 16);
    cout << " "<< enc_beg_offset << " " << enc_size << " " << dec_offset << endl;
    // poly_engine(virus_data, enc_beg_offset, enc_size, dec_offset);


    // std::ofstream outfile ("virus_poly",std::ofstream::binary);
    // // write to outfile
    // outfile.write (virus_data,size);

    std::ifstream infile ("virus",std::ifstream::binary);
    std::ofstream outfile ("virus_poly",std::ofstream::binary);

    // get size of file
    infile.seekg (0,infile.end);
    int size = infile.tellg();
    infile.seekg (0);

    // allocate memory for file content
    char* buffer = new char[size];
    // char* buffer = (char *)malloc(size);

    // read content of infile
    infile.read (buffer,size);

    poly_engine(buffer, enc_beg_offset, enc_size, dec_offset);
    cout << "deepak"<< endl;
    // write to outfile
    outfile.write (buffer,size);
    cout << "kumar"<< endl;
    // release dynamically-allocated memory
    delete[] buffer;
    cout << "tivari"<< endl;
    outfile.close();
    infile.close();
    cout << "wuut"<< endl;
    return 0;
}


// https://stackoverflow.com/questions/43765881/c-reading-binary-files
// http://www.cplusplus.com/forum/beginner/176692/