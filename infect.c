#include <stdio.h>      	// for basic IO

void main(int argc, char *argv[]) {

    int i;
    for (i=0; i<argc; ++i) {
    	printf("infect.c argv[%d]=%s\n", i, argv[i]);
	}
}

