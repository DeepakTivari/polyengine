#include <stdio.h>
int polymorphicengine(int argc, char* argv[])
{
      int i;
      for (i=0; i<argc; ++i) {
      printf("argv[%d]=%s\n", i, argv[i]);
      }
      return 0;
}

// int main(int argc, char* argv[]){
//       const char* virus_name = argv[0];
//       printf("ASCII value = %s,", virus_name );
//       return 0;
// }