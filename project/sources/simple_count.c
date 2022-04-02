#include "../headers/simple_count.h"

size_t count_pair(FILE *const input_file, size_t *count,size_t num_counts) {

  if(!input_file) return-1;
  if(!count) return -1;

  for (size_t j = 0; j < num_counts; j++) {
    count[j] = 0;
  }

  size_t z_o = 0;
  char c[2];
  c[z_o] = fgetc(input_file);
  z_o++;
  while ((c[z_o] = fgetc(input_file)) != EOF) {
    if (z_o)
      z_o--;
    else
      z_o++;
    for (size_t i = 0; i < num_counts; i++)
    {
      if (c[0] - c[1] == i || c[1] - c[0] == i)
        count[i]++;
    }
    }

  return count;
}
