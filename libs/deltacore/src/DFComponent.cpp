#include <DFComponent.hpp>

#include <DFEngine.hpp>

#ifdef EXPERIMENTAL_ALLOCATOR
void *DFComponent::operator new(std::size_t count)
{
    void *tmp = DFEngine::dfalloc(count);
    // std::cout << "allocated " << count << "bytes at " << tmp << "\n";
    std::cout << "(" << count << ", " << tmp << "),\n";
    return tmp;
}

void DFComponent::operator delete(void *ptr)
{
    
}
#endif