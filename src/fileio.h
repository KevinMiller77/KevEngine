#ifndef __FILE_IO_H__
#define __FILE_IO_H__

// Palatform FileIO interface header

struct FileContents {
    unsigned int length;
    byte *data;
};

FileContents ReadFileContents(const char *filePath);
void DestroyFileContents(FileContents fileContents);
void DestroyFileContentsPtr(FileContents *fileContents);

#endif