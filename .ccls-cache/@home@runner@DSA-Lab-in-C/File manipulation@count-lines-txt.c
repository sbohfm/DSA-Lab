/*
  Count the number of lines from a text file [GRAD EXEC]
*/

#include <stdio.h>

int main(int argc,char** argv) {

  /* variables */
  FILE *file;
  int size = 1;
  char c;
  char* filename = argv[1];

  if(argc != 2) { // <- condition: stop if incoherent arguments
    fprintf(stderr,"Expected a single argument.\n");
    return 0;
  }

  /* read file as byte */
  file = fopen(filename,"rb");

  if(!file) { // <- condition: stop if file doesnt exist
    fprintf(stderr,"No file was found.\n");
    return 0;
  }

  /* get characters until end of file */
  c = fgetc(file);
  if(c == EOF) size = 0; // <- edge case: empty file
  else {
    while(c != EOF) {
      if(c == '\n')
        size++;
      c = fgetc(file);
    }
  }

  fclose(file);

  printf("This file have %d lines.\n", size);
  
  return 0;
  
}