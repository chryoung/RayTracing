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
    delete[] _mem;
  }

  MemoryChunk(const MemoryChunk&) = delete;
  MemoryChunk& operator=(const MemoryChunk&) = delete;

  MemoryChunk(MemoryChunk&& other) noexcept 
    : _mem(other._mem), _next(other._next) {
    other._mem = nullptr;
    other._next = nullptr;
  }

  MemoryChunk& operator=(MemoryChunk&& other) noexcept {
    if (this != &other) {
      delete[] _mem;
      _mem = other._mem;
      _next = other._next;
      other._mem = nullptr;
      other._next = nullptr;
    }
    return *this;
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
  MemoryPool(int pool_size, int chunk_size, int resize_step = 100)
    : _pool_size(pool_size), _chunk_size(chunk_size), _resize_step(resize_step), _available(nullptr) {
    alloc_chunk(_pool_size);
  }

  ~MemoryPool() {
    while (_available) {
      MemoryChunk<T>* next = _available->_next;
      delete _available;
      _available = next;
    }
  }

  MemoryPool(const MemoryPool&) = delete;
  MemoryPool& operator=(const MemoryPool&) = delete;

  MemoryPool(MemoryPool&& other) noexcept 
    : _pool_size(other._pool_size), _chunk_size(other._chunk_size), _resize_step(other._resize_step), _available(other._available) {
    other._available = nullptr;
  }

  MemoryPool& operator=(MemoryPool&& other) noexcept {
    if (this != &other) {
      this->~MemoryPool();
      _pool_size = other._pool_size;
      _chunk_size = other._chunk_size;
      _resize_step = other._resize_step;
      _available = other._available;
      other._available = nullptr;
    }

    return *this;
  }

  MemoryChunk<T>* alloc() {
    if (_available == nullptr) {
      alloc_chunk(_resize_step);
      _pool_size += _resize_step;
    }

    MemoryChunk<T>* mem = _available;
    _available = _available->_next;
    mem->_next = nullptr;

    return mem;
  }

  void free(MemoryChunk<T>* p) {
    p->_next = _available;
    _available = p;
  }

private:
  void alloc_chunk(int n) {
    for (int i = 0; i < n; ++i) {
      MemoryChunk<T>* new_chunk = new MemoryChunk<T>(_chunk_size);
      new_chunk->_next = _available;
      _available = new_chunk;
    }
  }

  MemoryChunk<T>* _available;
  int _pool_size;
  int _chunk_size;
  int _resize_step;
};

}

