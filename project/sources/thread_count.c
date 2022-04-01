#include "../headers/thread_count.h"

void threadFunc(void *thread_data) {

  pthrData *data = (pthrData *)thread_data;

  size_t *counter = (size_t *)malloc(NUM_COUNTS * sizeof(size_t));

  count_pair(data->work_file, counter);

  for (size_t i = 0; i < NUM_COUNTS; i++) {
    data->num_all[i] += counter[i];
  }

  free(counter);

  return NULL;
}

void part_file(const size_t step, FILE *block, FILE *input) {
  char *buffer = (char *)malloc(step * sizeof(char));
  if(!buffer) return;
  size_t nread = 0;

  nread = fread(buffer, 1, step, input);
  fwrite(buffer, 1, nread, block);
  fseek(block, 0, SEEK_SET);
  free(buffer);
}

size_t *processing_threads(FILE *const input_file) {
  fseek(input_file, 0, SEEK_END);
  size_t size_file = ftell(input_file);
  fseek(input_file, 0, SEEK_SET);

  size_t num_CPU = sysconf(_SC_NPROCESSORS_ONLN);

  size_t num_threads = 2 * num_CPU;

  const size_t step_bytes = size_file / num_threads;

  const size_t last_step = size_file - (step_bytes * (num_threads - 1));

  size_t *result_count = (size_t *)malloc(NUM_COUNTS * sizeof(size_t));

  pthread_t *threads = (pthread_t *)malloc(num_threads * sizeof(pthread_t));

  pthrData *threadData = (pthrData *)malloc(num_threads * sizeof(pthrData));

  for (size_t j = 0; j < NUM_COUNTS; j++) {
    result_count[j] = 0;
  }

  FILE **block = (FILE **)malloc(num_threads * sizeof(FILE *));
  if(!block) return NULL;

  // first steps

  for (size_t i = 0; i < num_threads - 1; i++) {
    block[i] = tmpfile();
    if (i != 0)
      part_file(step_bytes + 1, block[i], input_file);
    else
      part_file(step_bytes, block[i], input_file);

    threadData[i].num_all = result_count;
    threadData[i].work_file = block[i];

    pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
    fseek(input_file, -1, SEEK_CUR);
  }

  // last step
  block[num_threads - 1] = tmpfile();
  part_file(last_step + 1, block[num_threads - 1], input_file);

  threadData[num_threads - 1].num_all = result_count;
  threadData[num_threads - 1].work_file = block[num_threads - 1];
  pthread_create(&(threads[num_threads - 1]), NULL, threadFunc, &threadData[num_threads - 1]);

  for (size_t i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  for (size_t i = 0; i < num_threads; i++)
    free(block[i]);

  free(threads);
  free(threadData);
  free(block);

  return result_count;
}
