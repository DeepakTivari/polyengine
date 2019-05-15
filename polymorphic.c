
int polymorphic(int argc, char* argv[])
{
      int i;
      for (i=0; i<argc; ++i) {
      printf("polymorphic argv[%d]=%s\n", i, argv[i]);
      }
}