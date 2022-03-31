#include "headers/simple_count.h"
#include "headers/thread_count.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void main() {
  FILE *test_file = fopen("../test10char", "r");
  size_t *count = NULL;

  if (test_file)
    count = processing_threads(test_file);

  if (count) {
    for (size_t k = 0; k < 11; k++) {
      printf("%zu\n", count[k]);
    }
  }

  free(count);
  fclose(test_file);
}
