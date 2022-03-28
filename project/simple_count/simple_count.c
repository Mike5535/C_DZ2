#include "simple_count.h"

size_t* count_pair( FILE* const input_file)
{
    size_t* count = (size_t*)malloc(11*sizeof(size_t)); // mag num

     for (size_t j = 0; j < 11; j++)
    {
        count[j] = 0;
    }

    for (size_t i = 0; i < 11; i++)
    {
        size_t z_o = 0;
        char c[2];
        c[z_o] = fgetc(input_file);
        z_o++;
        while ((c[z_o] = fgetc(input_file)) != EOF)
        {
            if (z_o)
                z_o--;
            else 
                z_o++; 
            if (c[0] - c[1] == i || c[1] - c[0] == i)
                count[i]++;
        }
        fseek(input_file, 0, SEEK_SET);
    }
    
    return count;
}
