#include "headers/simple_count.h"
#include "headers/thread_count.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void main() {
  FILE *test_file = tmpfile();
  for(size_t i = 0; i < 101; i++) 
    {
        fprintf(test_file,"1");
    }
  fseek(test_file,100,SEEK_SET); 
  size_t *count = NULL;

  if (test_file)
    count = processing_threads(test_file);

  free(count);
  fclose(test_file);
}
