#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_handling.h"

// file pointer
FILE *pTextFile;


void file_createTextFile(char *fileName)
{
    pTextFile = fopen("newFile.txt", "w");
    fclose(pTextFile);
    rename("newFile", fileName);    
}