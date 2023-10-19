#ifndef A6A29969_407D_4F35_8232_D57683122DCC
#define A6A29969_407D_4F35_8232_D57683122DCC

#include <cstdlib>
#include <new>
#include <utility>

#include "linked_list.h"

namespace RayTracer{


class MemoryChunk {
public:
  MemoryChunk(): _mem(nullptr) {}
  MemoryChunk(unsigned char* mem): _mem(mem) {}

  template<class T>
  T* get() { return reinterpret_cast<T*>(_mem); }
private:
  unsigned char * _mem;
};

class MemoryPool {
public:
  using Memory = LinkedListNode<MemoryChunk>*;

  MemoryPool(int pool_size, int chunk_size): _pool_size(pool_size), _chunk_size(chunk_size) {
    _memory = reinterpret_cast<unsigned char*>(::malloc(sizeof(unsigned char) * chunk_size * pool_size));
    for (int i = 0; i < _pool_size; ++i) {
      _available.add_back(new LinkedListNode<MemoryChunk>(std::make_unique<MemoryChunk>(_memory + i * chunk_size)));
    }
  }

  Memory alloc() {
    if (_available.is_empty()) {
    // No available memory.
      throw std::bad_alloc();
    }

    return _available.pop_front();
  }

  void free(Memory p) {
    _available.add_back(p);
  }

  virtual ~MemoryPool() {
    if (_memory != nullptr) {
      ::free(_memory);
      _memory = nullptr;
    }
  }

private:
  unsigned char* _memory;
  LinkedList<MemoryChunk> _available;
  int _pool_size;
  int _chunk_size;
};

}

#endif
