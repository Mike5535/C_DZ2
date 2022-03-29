#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
    #include "../headers/simple_count.h"
    #include "../headers/thread_count.h"
}

/*TEST(linear_processing, one) {
    
    FILE* stdinn = tmpfile();
    
    for(size_t i = 0; i < 104857601; i++) //100MB = 104857601 byte
    {
        fprintf(stdinn,"1");
    }  
  
    fseek(stdinn,0,SEEK_SET);

    size_t* numbers_pair = count_pair(stdinn);
    

   
    EXPECT_EQ( 104857600, numbers_pair[0]);
    free(numbers_pair);
     
    
}*/

TEST(thread_processing, two) {
    
    FILE* stdinn = fopen("../tests/test1","w+b");
    
    for(size_t i = 0; i < 104857601; i++) //100MB = 104857601 byte
    {
        fprintf(stdinn,"1");
    }  
  
    fseek(stdinn,0,SEEK_SET);

    size_t* numbers_pair = processing_threads(stdinn,"../tests/test1");

   
    EXPECT_EQ( 104857600, numbers_pair[0]);

    free(numbers_pair);
    
}
