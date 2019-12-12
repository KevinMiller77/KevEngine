#include "SimpleList.h"
using namespace std;

template <typename T> SimpleList<T>::SimpleList()
{
    Data = (T*)malloc(sizeof(T));
    Count = 0;
}

template <typename T> SimpleList<T>::SimpleList(u32_t count)
{
    Data = (T*)malloc(count * sizeof(T));
    Count = count;
}

template <typename T> SimpleList<T>::SimpleList(T data, u32_t count)
{
    Data = ptr(data);
    Count = count;
}

template <typename T> SimpleList<T>::~SimpleList()
{
    free(Data);
}

template <typename T> void SimpleList<T>::append(T item)
{
    Count++;
    Data = (T*)realloc(Data, Count * sizeof(T));
    Data[Count - 1] = ptr(item);
}

template <typename T> T SimpleList<T>::front()
{
    return Data[0];
}

template <typename T> T SimpleList<T>::end()
{
    return ptr(Data[Count - 1]);
}

template <typename T> u32_t SimpleList<T>::size()
{
    return Count;
}

template <typename T> u64_t SimpleList<T>::numBytes()
{
    return Count * sizeof(T);
}