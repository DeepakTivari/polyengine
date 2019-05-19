#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

int filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

void    print_section(Elf64_Shdr *shdr, char *strTab, int shNum, uint8_t *data)
{
  int   i;  

  for(i = 0; i < shNum; i++) {
    size_t k;
     printf("%02d: %s Offset %lx\n", i, &strTab[shdr[i].sh_name], 
        shdr[i].sh_offset);
    //  for (k = shdr[i].sh_offset; k < shdr[i].sh_offset + shdr[i].sh_size; k++) {
    //    printf("%x", data[k]);
    //  }   
    //  printf("\n");
    //  for (k = shdr[i].sh_offset; k < shdr[i].sh_offset + shdr[i].sh_size; k++) {
    //    printf("%c", data[k]);
    //  }   
    //  printf("\n");
  }
}


int main(int ac, char **av)
{
  void  *data;
  Elf64_Ehdr    *elf;
  Elf64_Shdr    *shdr;
  int       fd;
  char      *strtab;

  fd = open(av[1], O_RDONLY);
  data = mmap(NULL, filesize(fd), PROT_READ, MAP_SHARED, fd, 0);
  elf = (Elf64_Ehdr *) data;
  shdr = (Elf64_Shdr *) (data + elf->e_shoff);
  strtab = (char *)(data + shdr[elf->e_shstrndx].sh_offset);
  print_section(shdr, strtab, elf->e_shnum, (uint8_t*)data);
  close(fd);
  return 0;
}