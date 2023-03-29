/*
  Count the number of lines from a text file [GRAD EXEC]
*/

#include <stdio.h>
#include <string.h>

int main(int argc,char** argv) {

  /* variables */
  FILE *file;
  int found = 0;
  char c;
  char* filename;
  char* filename_default = ".files/lorenipsum.txt";

  if (argc == 2) { // <- condition: inputs filename
    filename = argv[1];
  } else if (argc == 1) { // <- condition: defaults to lorenipsum.txt
    filename = filename_default;
  } else { // <- condition: stop if incoherent arguments
    fprintf(stderr, "Expected at least one argument.\n");
    return 0;
  }

  /* read file as byte */
  file = fopen(filename,"rb");

  if (!file) { // <- condition: stop if file doesnt exist
    fprintf(stderr,"No file was found.\n");
    return 0;
  }

  /* get characters until end of file */
  c = fgetc(file);
  if (c != EOF) found = 1; // <- edge case: empty file
  
  while (c != EOF) {
    if(c == '\n')
      found++;
    c = fgetc(file);
  }

  fclose(file);

  printf("file: %s features %d lines.\n", filename, found);
  
  return 0;
  
}