#pragma once

#include <cstdlib>
#include <iostream>
class DFLinearAllocator
{

public:
    DFLinearAllocator(size_t memsize)
    {
        m_memory = (char *)malloc(memsize);
        m_cur = m_memory;
        m_end = m_memory + memsize;
    }

    ~DFLinearAllocator()
    {
        free(m_memory);
    }

    void *allocate(size_t size)
    {
        if (m_cur + size < m_end)
        {
            std::cout << "allocated " << size << ". mem: " << (m_cur + size - m_memory) * 100 / (m_end - m_memory) << "%\n";
            m_cur += size;
            return m_cur - size;
        }
        throw std::bad_alloc();
    }

    void deallocate()
    {
        m_cur = m_memory;
    }

private:
    void print_hex(char num)
    {
        int first = (num >> 4) & 0xF;
        int second = (num) & 0xF;
        std::cout << std::hex << first << second;
    }
    char *m_memory, *m_cur, *m_end;
};