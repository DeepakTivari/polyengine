#include <stdio.h>
#include <stdlib.h>

int main(){

	// virus name
	char filename[] = "test";

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
    printf("%ul", exe_size);
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

}