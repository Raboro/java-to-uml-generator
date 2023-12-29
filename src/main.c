#include <stdio.h>

#include "file_scanning.h"

int main()
{
    int file_counter = count_files(".");
    printf("%d", file_counter);
    return 0;
}