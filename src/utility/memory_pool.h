#pragma once
#include <new>

namespace RayTracer{

template<class T>
class MemoryPool;

template<class T>
class MemoryChunk {
public:
  MemoryChunk(): _mem(nullptr) {}
  MemoryChunk(int chunk_size): _mem(new T[chunk_size]) {}
  ~MemoryChunk() {
    if (_mem != nullptr) {
      delete[] _mem;
      _mem = nullptr;
      _next = nullptr;
    }
  }

  friend class MemoryPool<T>;

  T* get() { return _mem; }
private:
  MemoryChunk(T* mem): _mem(mem) {}

  T* _mem;
  MemoryChunk<T>* _next = nullptr;
};

template<class T>
class MemoryPool {
public:
  MemoryPool(int pool_size, int chunk_size, int resize_step = 100): _pool_size(pool_size), _chunk_size(chunk_size), _resize_step(resize_step) {
    _available = new MemoryChunk<T>();
    alloc_chunk(_pool_size);
  }

  MemoryChunk<T>* alloc() {
    if (_available->_next == nullptr) {
      alloc_chunk(_resize_step);
      _pool_size += _resize_step;
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
  }

private:
  void alloc_chunk(int n) {
    for (int i = 0; i < n; ++i) {
      MemoryChunk<T>* next = _available->_next;
      _available->_next = new MemoryChunk<T>(_chunk_size);
      _available->_next->_next = next;
    }
  }

  MemoryChunk<T>* _available;
  int _pool_size;
  int _chunk_size;
  int _resize_step;
};

}

