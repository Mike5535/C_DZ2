#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
    #include "../headers/simple_count.h"
    #include "../headers/thread_count.h"
}

TEST(linear_processing, one) {
    
    FILE* stdinn = tmpfile();
    
    fprintf(stdinn,"1");
    fprintf(stdinn,"2");
    fprintf(stdinn,"3");
    fprintf(stdinn,"4");
    fprintf(stdinn,"3");
    fprintf(stdinn,"2");
    fprintf(stdinn,"1");
    fprintf(stdinn,"3");
    fprintf(stdinn,"5");
    fprintf(stdinn,"8");
    fprintf(stdinn,"4");
    fprintf(stdinn,"9");
    fprintf(stdinn,"3"); 
  
    fseek(stdinn,0,SEEK_SET);

    size_t* counter = (size_t*)malloc(NUM_COUNTS * sizeof(size_t));
    count_pair(stdinn,counter);
   
    EXPECT_EQ( 6, counter[1]);
    EXPECT_EQ( 2, counter[2]);
    EXPECT_EQ( 1, counter[3]);
    EXPECT_EQ( 1, counter[4]);
    EXPECT_EQ( 1, counter[5]);
    EXPECT_EQ( 1, counter[6]);

    free(counter);
    fclose(stdinn);
}

TEST(thread_processing, two) {
    
    FILE* stdinn = tmpfile();
    
    fprintf(stdinn,"1");
    fprintf(stdinn,"2");
    fprintf(stdinn,"3");
    fprintf(stdinn,"4");
    fprintf(stdinn,"3");
    fprintf(stdinn,"2");
    fprintf(stdinn,"1");
    fprintf(stdinn,"3");
    fprintf(stdinn,"5");
    fprintf(stdinn,"8");
    fprintf(stdinn,"4");
    fprintf(stdinn,"9");
    fprintf(stdinn,"3"); 
    
    fseek(stdinn,0,SEEK_SET);

    size_t* numbers_pair = processing_threads(stdinn);

    EXPECT_EQ( 6, numbers_pair[1]);
    EXPECT_EQ( 2, numbers_pair[2]);
    EXPECT_EQ( 1, numbers_pair[3]);
    EXPECT_EQ( 1, numbers_pair[4]);
    EXPECT_EQ( 1, numbers_pair[5]);
    EXPECT_EQ( 1, numbers_pair[6]);

    free(numbers_pair);
    fclose(stdinn);
}

TEST(threadFunc, one) {
    
    FILE* stdinn = tmpfile();
    
    fprintf(stdinn,"1");
    fprintf(stdinn,"2");
    fprintf(stdinn,"3");
    fprintf(stdinn,"4");
    fprintf(stdinn,"3");
    fprintf(stdinn,"2");
    fprintf(stdinn,"1");
  
    fseek(stdinn,0,SEEK_SET);

    size_t* numbers_pair = (size_t*)malloc(NUM_COUNTS * sizeof(size_t));

    pthrData test_data;
    test_data.work_file = stdinn;
    test_data.num_all = numbers_pair;

    pthrData* ptest_data = &test_data;

    threadFunc(ptest_data);
   
    EXPECT_EQ( 6, numbers_pair[1]);

    free(numbers_pair);
    fclose(stdinn);
}
