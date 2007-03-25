#ifndef _HSTARRAY_H
#define _HSTARRAY_H

#include <stdlib.h>
#include "hsStream.h"

template <class T>
class hsTArray {
private:
    unsigned short max, count;
    T* data;

public:
    hsTArray() : max(0), count(0) {
        data = NULL;
    }
    ~hsTArray<T>() {
        if (data != NULL)
            delete[] data;
    }

    void clear() {
        Reset();
    }
    
    inline void Reset() {
        if (data != NULL)
            delete[] data;
        data = NULL;
        count = 0;
        max = 0;
	}

    inline int getSize() { return count; }
    int getCap() { return max; }

    void setSize(int cap) {
        if (max == cap) return;
        T* newData = new T[cap];
        for (int i=0; i<count; i++)
            newData[i] = data[i];
        if (data != NULL)
            delete[] data;
        max = count = cap;
        data = newData;
    }

    void setSizeNull(int cap) {
        delete[] data;
        data = new T[cap];
        for (int i=0; i<cap; i++)
            data[i] = 0;
        max = count = cap;
    }

    void append(T& item) {
        setSize(count+1);
        data[count++] = item;
    }

    T& remove(int idx) {
        T dItm = data[idx];
        for (int i=idx; i<count; i++)
            data[i] = data[i+1];
        data[--count] = NULL;
        return dItm;
    }

    T& operator[](int idx) {
        return data[idx];
    }
};

#endif

