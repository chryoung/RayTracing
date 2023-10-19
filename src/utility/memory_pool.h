#ifndef A6A29969_407D_4F35_8232_D57683122DCC
#define A6A29969_407D_4F35_8232_D57683122DCC

#include <new>

namespace RayTracer{

template<class T>
class MemoryPool;

template<class T>
class MemoryChunk {
public:
  MemoryChunk(): _mem(nullptr) {}
  MemoryChunk(T* mem): _mem(mem) {}
  ~MemoryChunk() {
    _mem = nullptr;
    _next = nullptr;
  }

  friend class MemoryPool<T>;

  T* get() { return _mem; }
private:
  T* _mem;
  MemoryChunk<T>* _next = nullptr;
};

template<class T>
class MemoryPool {
public:
  MemoryPool(int pool_size, int chunk_size): _pool_size(pool_size), _chunk_size(chunk_size) {
    _total = new MemoryChunk(new T[_pool_size * chunk_size]);
    _available = new MemoryChunk<T>();
    for (int i = 0; i < _pool_size; ++i) {
      MemoryChunk<T>* next = _available->_next;
      _available->_next = new MemoryChunk(_total->_mem + i * sizeof(T) * chunk_size);
      _available->_next->_next = next;
    }
  }

  MemoryChunk<T>* alloc() {
    if (_available->_next == nullptr) {
    // No available memory.
      throw std::bad_alloc();
    }

    MemoryChunk<T>* mem = _available->_next;
    _available->_next = _available->_next->_next;
    mem->_next = nullptr;

    return mem;
  }

  void free(MemoryChunk<T>* p) {
    MemoryChunk<T>* next = _available->_next;
    _available->_next = p;
    p->_next = next;
  }

  virtual ~MemoryPool() {
    MemoryChunk<T>* iter = _available;
    while (iter) {
      MemoryChunk<T>* next = iter->_next;
      delete iter;
      iter = next;
    }

    delete[] _total->_mem;
    delete _total;
  }

private:
  MemoryChunk<T>* _total;
  MemoryChunk<T>* _available;
  int _pool_size;
  int _chunk_size;
};

}

#endif
