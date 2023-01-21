#ifndef PS2_PTR_H
#define PS2_PTR_H

#include "klonoa_memory.h"

template <typename T>
class PS2Pointer {
public:
    uint ptr;

    T* Get(KlonoaMemory* mem, uint offset = 0) {
        return mem->ReadObj<T>(ptr + offset);
    }

    template <typename U>
    U* Get(KlonoaMemory* mem, uint offset = 0) {
        return mem->ReadObj<U>(ptr + offset);
    }

    bool IsValid() {
        return KlonoaMemory::IsValidPointer(ptr);
    }
};

#endif