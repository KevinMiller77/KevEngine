#ifndef __FILE_IO_H__
#define __FILE_IO_H__

#include <stdio.h>
#include <cstring>
#include <cstdlib>

// Palatform FileIO interface header

struct FileContents {
    unsigned int length;
    char *data;
};

FileContents ReadFileContents(const char *filePath);
void DestroyFileContents(FileContents fileContents);
void DestroyFileContentsPtr(FileContents *fileContents);

#endif