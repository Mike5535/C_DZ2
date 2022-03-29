#include "../headers/thread_count.h"

size_t getFileSize(const char* file_name){
	size_t _file_size = 0;
	struct stat _fileStatbuff;
	int fd = open(file_name, O_RDONLY);
	if(fd == -1){
		_file_size = -1;
	}
	else{
		if ((fstat(fd, &_fileStatbuff) != 0) || (!S_ISREG(_fileStatbuff.st_mode))) {
			_file_size = -1;
		}
		else{
			_file_size = _fileStatbuff.st_size;
		}
		close(fd);
	}
	return _file_size;
}

void threadFunc(void* thread_data){
	/*pthrData* data = (pthrData*) thread_data;
    size_t i = data->value_bytes;
    FILE* input_file = data->work_file; 
    
 */
    
	 pthread_exit(NULL);
}

size_t* processing_threads(FILE* source_file,const char* path_file)
{
    size_t* result_count = (size_t*) malloc(NUM_THREADS * sizeof(size_t));
/*
    pthread_t* threads = (pthread_t*) malloc(NUM_THREADS * sizeof(pthread_t));

    pthrData* threadData = (pthrData*) malloc(NUM_THREADS * sizeof(pthrData));
*/
    size_t size_file = getFileSize(path_file);
    printf("File size: %zu \n", size_file);
    
/*
    for (size_t j = 0; j < NUM_THREADS; j++)
    {
        result_count[j] = 0;
    }

    for(size_t i = 0; i < NUM_THREADS; i++)
    {
        threadData[i].work_file = source_file;
        threadData[i].value_bytes = i;
        threadData[i].num_all = result_count;
        pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
    }

    for(size_t i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    free(threads);
	free(threadData);
*/
    return result_count;
}
