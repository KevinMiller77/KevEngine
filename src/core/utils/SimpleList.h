#ifndef __SIMPLE_LIST__
#define __SIMPLE_LIST__
#include <stdio.h>
#include <string.h>
#include "../CommonTypes.h"

//This is a simple list type which will replace our use of vectors

//NOT FINISHED, DON'T USE

using namespace std;

template <typename T>
class SimpleList
{
private:
    T Data;
    u8_t Count;
    
public:
    SimpleList();
    SimpleList(u32_t count);
    SimpleList(T data, u32_t count);
    ~SimpleList();

    void append(T item);
    void push(T& item);
    
    T front();
    T end();

    u32_t size();
    u64_t numBytes();

    //Operators (We really only need indexing)
    inline T operator[](int i) const { return &Data[i]; }
};

#endif