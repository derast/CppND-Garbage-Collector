#include <iostream>
#include <list>
#include <cstdlib>
#include <typeinfo>
#include "Pointer.h"
#include "PtrDetails.h"
#include "Iterator.h"

template<class T>
class Node {};

namespace sp {

  // STATIC INITIALIZATION
  // Creates storage for the static variables
  template<class T, int size>
  std::list<PtrDetails<T>> Pointer<T, size>::refContainer;
  template<class T, int size>
  bool Pointer<T, size>::first = true;

  template<class T, int size>
  Pointer<T, size>::Pointer(){
    Pointer(nullptr);
  }

  // Constructor for both initialized and uninitialized objects. -> see class interface
  template<class T,int size>
  Pointer<T,size>::Pointer(T *t)
  : addr(t), isArray((size > 0) ? true : false), arraySize(size) {
    // Register shutdown() as an exit function.
    if (first)
      atexit(shutdown);
    first = false;

    // TODO: Implement Pointer constructor
    // Lab: Smart Pointer Project Lab
    typename std::list<PtrDetails<T> >::iterator ptrDetailsIt = findPtrInfo(t);
    if(ptrDetailsIt != refContainer.end()) {
      refContainer.push_back(*ptrDetailsIt); 
      ++ptrDetailsIt->refCount;
    } else {
      refContainer.push_back(PtrDetails<T>(addr, size));
    }
  }

  // Copy constructor.
  template<class T, int size>
  Pointer<T, size>::Pointer(const Pointer<T, size> &pointer) : 
  addr(pointer.addr), isArray(pointer.isArray), arraySize(pointer.arraySize) {
    typename std::list<PtrDetails<T>>::iterator ptrDetailsIt = findPtrInfo(pointer.addr);
    // TODO: Implement Pointer constructor
    // Lab: Smart Pointer Project Lab
    ptrDetailsIt->refCount++;
  }

  // Destructor for Pointer.
  template<class T, int size>
  Pointer<T, size>::~Pointer() {
    // TODO: Implement Pointer destructor
    // Lab: New and Delete Project Lab
    typename std::list<PtrDetails<T>>::iterator ptrDetailsIt = findPtrInfo(addr);
    if(ptrDetailsIt != refContainer.end()) {
      ptrDetailsIt->refCount--;
    }
    collect();
  }

  // Collect garbage. Returns true if at least one object was freed.
  template<class T, int size>
  bool Pointer<T, size>::collect() {
    bool memFree = false;
    typename std::list<PtrDetails<T>>::iterator ptrDetailsIt;
    do {
      for(ptrDetailsIt = refContainer.begin(); ptrDetailsIt != refContainer.end(); ptrDetailsIt++) {
        // TODO: Implement collect function
        // LAB: New and Delete Project Lab
        // Note: collect() will be called in the destructor
        if(ptrDetailsIt->refCount > 0) {
          continue;
        }
        if(!ptrDetailsIt->isArray) {
          delete ptrDetailsIt->memPtr;
        } else {
          delete [] ptrDetailsIt->memPtr;
        }
        refContainer.erase(ptrDetailsIt);
        memFree = true;
        break;
      }
    } while(ptrDetailsIt != refContainer.end());

    return memFree;
  }

  template<class T, int size>
  bool Pointer<T, size>::operator==(Pointer<T, size> &rv) {
    if(addr == rv.addr && isArray == rv.isArray && arraySize == rv.arraySize) {
      return true;
    }

    return false;
  }

  // Overload assignment of pointer to Pointer.
  template <class T, int size>
  T *Pointer<T, size>::operator=(T *t){
    Pointer<T, size> temp(t);
    swap(*this, temp);

    return t;
  }

  // Overload assignment of Pointer to Pointer.
  template <class T, int size>
  Pointer<T, size> &Pointer<T, size>::operator=(Pointer &rv){
    swap(*this, rv);

    return *this;
  }

  template<class T, int size>
  T &Pointer<T, size>::operator*() {
    return *addr;
  }

  template<class T, int size>
  T *Pointer<T, size>::operator->() { 
    return addr; 
  }

  template<class T, int size>
  T &Pointer<T, size>::operator[](int i) { 
    return addr[i];
  }

  template<class T, int size>
  Pointer<T, size>::operator T *() { 
    return addr; 
  }

  template<class T, int size>
  Iterator<T> Pointer<T, size>::begin() {
    int _size;
    if (isArray)
        _size = arraySize;
    else
        _size = 1;
    return Iterator<T>(addr, addr, addr + _size);
  }

  template<class T, int size>
  Iterator<T> Pointer<T, size>::end() {
    int _size;
    if (isArray)
        _size = arraySize;
    else
        _size = 1;
    return Iterator<T>(addr + _size, addr, addr + _size);
  }

  template<class T, int size>
  int Pointer<T, size>::refContainerSize() { 
    return refContainer.size(); 
  }

  // A utility function that displays refContainer.
  template<class T, int size>
  void Pointer<T, size>::showlist() {
    typename std::list<PtrDetails<T> >::iterator p;
    std::cout << "refContainer<" << typeid(T).name() << ", " << size << ">:\n";
    std::cout << "memPtr refcount value\n ";
    if (refContainer.begin() == refContainer.end()) {
      std::cout << " Container is empty!\n\n ";
    }
    for (p = refContainer.begin(); p != refContainer.end(); p++) {
      std::cout << "[" << (void *)p->memPtr << "]"
            << " " << p->refCount << " ";
      if (p->memPtr)
          std::cout << " " << *p->memPtr;
      else
          std::cout << "---";
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  // Find a pointer in refContainer.
  template <class T, int size>
  typename std::list<PtrDetails<T> >::iterator
  Pointer<T, size>::findPtrInfo(T *ptr){
    typename std::list<PtrDetails<T> >::iterator p;
    // Find ptr in refContainer.
    for (p = refContainer.begin(); p != refContainer.end(); p++)
      if (p->memPtr == ptr)
        return p;
    
    return p;
  }

  // Clear refContainer when program exits.
  template<class T, int size>
  void Pointer<T, size>::shutdown() {
    if (refContainerSize() == 0)
      return; // list is empty
    typename std::list<PtrDetails<T> >::iterator p;
    for (p = refContainer.begin(); p != refContainer.end(); p++) {
      // Set all reference counts to zero
      p->refCount = 0;
    }
    collect();
  }

  template<class T, int size>
  void Pointer<T, size>::swap(Pointer &p1, Pointer &p2) {
    using std::swap;

    std::swap(p1.addr, p2.addr);
    std::swap(p1.isArray, p2.isArray);
    std::swap(p1.arraySize, p2.arraySize);
  }
}

// Template explicit instantiation defination 
template class sp::Pointer<int, 0>;
