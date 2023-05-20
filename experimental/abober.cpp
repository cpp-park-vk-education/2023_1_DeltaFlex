#include <dlfcn.h>
#include <iostream>

class LazyLibraryLoader
{
public:
    LazyLibraryLoader(const std::string &path)
    {
        m_handler = dlopen(path.c_str(), RTLD_LAZY);
        if (m_handler == NULL)
        {
            throw std::runtime_error(dlerror());
        }
    };

    ~LazyLibraryLoader()
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
int main(int argc, char **argv)
{
    LazyLibraryLoader loader(argv[1]);
    std::cout << loader.FindSymbol("DFTransform_loader");
}