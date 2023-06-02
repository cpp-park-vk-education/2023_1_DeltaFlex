#pragma once

#include <iostream>
#include <string>
#ifdef EXPERIMENTAL_ALLOCATOR
#include <DFEngine.hpp>
#endif

class BaseModel
{

public:
    virtual void save(int stage, int current) = 0;
    virtual void load(std::string file) = 0;

#ifdef EXPERIMENTAL_ALLOCATOR
    void *operator new(std::size_t size)
    {
        return DFEngine::dfalloc(size);
    }
#endif
};