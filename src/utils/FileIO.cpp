#include "FileIO.h"


FileContents ReadFileContents(const char *filePath)
{
    FileContents result;

    FILE* file = fopen(filePath, "rt");
    fseek(file, 0, SEEK_END);
    result.length = ftell(file);
    result.data = (char*)malloc(result.length + 1);
    memset(result.data, 0, result.length + 1);
    fseek(file, 0, SEEK_SET);
    fread(result.data, 1, result.length, file);
    fclose(file);

    return result;
}
void DestroyFileContents(FileContents fileContents)
{
    free(fileContents.data);
}
void DestroyFileContentsPtr(FileContents *fileContents)
{
    free(fileContents->data);
}