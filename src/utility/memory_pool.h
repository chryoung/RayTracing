#ifndef A6A29969_407D_4F35_8232_D57683122DCC
#define A6A29969_407D_4F35_8232_D57683122DCC

#include <cstdlib>
#include <new>
#include <iostream>

namespace RayTracer{
  
class MemoryPool
{
public:
  MemoryPool(int init_size, int chunk_size): _pool_size(init_size), _chunk_size(chunk_size) {
    _memory = reinterpret_cast<unsigned char*>(::malloc(sizeof(unsigned char) * init_size));
    _used = reinterpret_cast<bool*>(::malloc(sizeof(bool) * (init_size / chunk_size)));
  }

  template<class T>
  T* alloc() {
    for (int i = 0; i < _pool_size / _chunk_size; ++i) {
      if (_used[i] == false) {
        _used[i] = true;
        unsigned long long addr = (unsigned long long)(_memory + i * _chunk_size);
        std::cout << "alloc(): alloc addr = " << addr << ", start = " << (unsigned long long)(_memory) << std::endl;
        return reinterpret_cast<T*>(_memory + i * _chunk_size);
      }
    }

    throw std::bad_alloc();
  }

  void free(void* p) {
    int i = (reinterpret_cast<unsigned char*>(p) - _memory) / _chunk_size;
    std::cout << "free(p): i == " << i << "\n";
    _used[i] = false;
  }

  virtual ~MemoryPool() {
    ::free(_memory);
    ::free(_used);
  }

private:
  unsigned char* _memory;
  int _pool_size;
  int _chunk_size;
  bool* _used;
};

}

#endif
