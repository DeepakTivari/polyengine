#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE *f = fopen("virus", "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);


	FILE* out_file = fopen("virus_mod", "wb");
	// write the modified executable data
	fwrite(string, fsize, 1, out_file);
    fclose(out_file);
}