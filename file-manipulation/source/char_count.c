/*
  Count the number of characters from a text file and show it's letters [GRAD EXEC]
*/

#include <stdio.h>

int main(int argc, char **argv) {

  /* variables */
  FILE *file;
  int found[256] = {0};
  unsigned char c;       // enough room for extended ASCII values
  int count = 0;         // helper var to store found array access
  int empty = 1;         // helps not to check found array when file is empty
  int s = 0, ns = 0;     // counts how many letters were showed/not showed
  char *filename;
  char *filename_default = ".files/lorenipsum.txt";

  if (argc == 2) { // <- condition: inputs filename
    filename = argv[1];
  } else if (argc == 1) { // <- condition: defaults to lorenipsum.txt
    filename = filename_default;
  } else { // <- condition: stop if incoherent arguments
    fprintf(stderr, "usage: ./count [filename]\n");
    return 0;
  }

  /* read file as byte */
  file = fopen(filename, "rb");

  if (!file) { // <- condition: stop if file doesnt exist
    fprintf(stderr, "No file %s was found.\n",filename);
    return 0;
  }

  /* get characters until end of file */
  c = fgetc(file);
  if ((char)c != EOF) empty = 0; // <- case: empty file

  while ((char)c != EOF) {
    found[(int)c]++;
    c = fgetc(file);
  }

  fclose(file);

  /* calculate and output stuff if file is not empty */
  if (!empty) {
    
    printf("file: %s features :\n\n", filename);
    for (int i = 0; i < 256; i++) {
  
      count = found[i];

      /* iterate while no characters found */
      if (count == 0) {
        continue;
      }

      /* iterate while counts non-letter characters found */
      if (i < 65 || (i > 90 && i < 97) || i > 122) {
        ns += count;
        continue;
      }

      /* prints and counts letters found */
      printf("\t-> (%04dx) '%c'\n", count, i);
      s += count;
    
    }
  
    printf("\n");
    printf("[!] %d non-letter character(s) ignored.\n", ns);
    
  }

  printf("In total, %d character(s) can be found in this file.\n", (s + ns));

  return 0;
}