#pragma once

#include <dlfcn.h>
#include <string>
#include <stdexcept>

class DFLazyLibraryLoader
{
public:
    DFLazyLibraryLoader(const std::string &path)
    {
        m_handler = dlopen(path.c_str(), RTLD_LAZY);
        if (m_handler == NULL)
        {
            throw std::runtime_error(dlerror());
        }
    };

    DFLazyLibraryLoader()
    {
        m_handler = dlopen(NULL, RTLD_LAZY);
        if (m_handler == NULL)
        {
            throw std::runtime_error(dlerror());
        }
    }
    
    ~DFLazyLibraryLoader()
    {
        dlclose(m_handler);
    }

    void *FindSymbol(const std::string &title)
    {
        return dlsym(m_handler, title.c_str());
    }

private:
    void *m_handler;
};