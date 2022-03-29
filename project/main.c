#include "headers/simple_count.h"
#include "headers/thread_count.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


void main()
{
   

    FILE* test_file = fopen("../test10char", "r");
    size_t* count_linear = NULL;
    size_t* count_thread = NULL;

    if (test_file)
    {
        count_linear = count_pair(test_file);
        count_thread = processing_threads(test_file,"../test10char");
    }

    for(size_t i =0;i<11;i++)
    {
    printf("%zu\n",count_linear[i]);
    }

    free(count_linear);
    free(count_thread);
    fclose(test_file);
}
