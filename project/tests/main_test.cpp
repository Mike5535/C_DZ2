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
    count_pair(stdinn,counter,NUM_COUNTS);
   
    EXPECT_EQ( 6, counter[1]);
    EXPECT_EQ( 2, counter[2]);
    EXPECT_EQ( 1, counter[3]);
    EXPECT_EQ( 1, counter[4]);
    EXPECT_EQ( 1, counter[5]);
    EXPECT_EQ( 1, counter[6]);

    free(counter);
    fclose(stdinn);
}

TEST(linear_processing, empty_file) {
    
    FILE* stdinn = tmpfile();

    size_t* counter = (size_t*)malloc(NUM_COUNTS * sizeof(size_t));
    count_pair(stdinn,counter,NUM_COUNTS);
   
    EXPECT_EQ( 0, counter[1]);
    EXPECT_EQ( 0, counter[2]);
    EXPECT_EQ( 0, counter[3]);
    EXPECT_EQ( 0, counter[4]);
    EXPECT_EQ( 0, counter[5]);
    EXPECT_EQ( 0, counter[6]);

    free(counter);
    fclose(stdinn);
}

TEST(linear_processing, size_1) {
    
    FILE* stdinn = tmpfile();
    
    fprintf(stdinn,"1");
  
    fseek(stdinn,0,SEEK_SET);

    size_t* counter = (size_t*)malloc(NUM_COUNTS * sizeof(size_t));
    count_pair(stdinn,counter,NUM_COUNTS);
   
    EXPECT_EQ( 0, counter[1]);
    EXPECT_EQ( 0, counter[2]);
    EXPECT_EQ( 0, counter[3]);
    EXPECT_EQ( 0, counter[4]);
    EXPECT_EQ( 0, counter[5]);
    EXPECT_EQ( 0, counter[6]);

    free(counter);
    fclose(stdinn);
}

TEST(thread_processing, one) {
    
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

TEST(thread_processing, empty_file) {
    
    FILE* stdinn = tmpfile();
    
    size_t* numbers_pair = processing_threads(stdinn);

    EXPECT_EQ( 0, numbers_pair[1]);
    EXPECT_EQ( 0, numbers_pair[2]);
    EXPECT_EQ( 0, numbers_pair[3]);
    EXPECT_EQ( 0, numbers_pair[4]);
    EXPECT_EQ( 0, numbers_pair[5]);
    EXPECT_EQ( 0, numbers_pair[6]);

    free(numbers_pair);
    fclose(stdinn);
}

TEST(thread_processing, size_1) {
    
    FILE* stdinn = tmpfile();

    fseek(stdinn,0,SEEK_SET);

    fprintf(stdinn,"3");
    
    size_t* numbers_pair = processing_threads(stdinn);

    EXPECT_EQ( 0, numbers_pair[1]);
    EXPECT_EQ( 0, numbers_pair[2]);
    EXPECT_EQ( 0, numbers_pair[3]);
    EXPECT_EQ( 0, numbers_pair[4]);
    EXPECT_EQ( 0, numbers_pair[5]);
    EXPECT_EQ( 0, numbers_pair[6]);

    free(numbers_pair);
    fclose(stdinn);
}
