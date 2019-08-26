#include "PtrDetails.h"

class Node;

namespace sp {
  template<class T>
  PtrDetails<T>::PtrDetails() 
  : refCount(0), memPtr(nullptr), isArray(false), arraySize(0) {

  } 

  template<class T>
  PtrDetails<T>::PtrDetails(T *ptr, int size) 
  : memPtr(ptr), isArray((size > 0 ? true : false)), arraySize(size) {
    refCount = 1;
  }

  template<class T>
  bool PtrDetails<T>::operator==(const PtrDetails<T> &ptrDetails) const{
    if(refCount == ptrDetails.refCount && ptrDetails.refCount > 1) {
      if(isArray && ptrDetails.isArray && arraySize == ptrDetails.arraySize) {
        for(int i=0; i<arraySize; i++) {
          if(memPtr[i] != ptrDetails.memPtr[i]) {
            return false;
          }

          return true;
        }
      } else if(*memPtr == *ptrDetails.memPtr && !isArray && !ptrDetails.isArray) {
        return true;
      }
    }

    return false;  
  }

  // This has to be outside the class because we need to compare two different object, 
  // that are not the current PtrDetails instance
  template<class T>
  bool operator==(const PtrDetails<T> &ptrDetails1, const PtrDetails<T> &ptrDetails2) {
    return ptrDetails1.memPtr == ptrDetails2.memPtr;
  }
}

// Template explicit instantiation defination 
template class sp::PtrDetails<int>;