#ifndef PTRDETAILS__H
#define PTRDETAILS__H

namespace sp {

  template<class T>
  class PtrDetails {
    public:
      unsigned refCount;
      T *memPtr;
      bool isArray;
      int arraySize;

      PtrDetails();
      PtrDetails(T *ptr, int size=0);
      bool operator==(const PtrDetails<T> &ptrDetails) const;
  };

  // This has to be outside the class because we need to compare two different object, 
  // that are not the current PtrDetails instance
  template<class T>
  bool operator==(const PtrDetails<T> &ptrDetails1, const PtrDetails<T> &ptrDetails2);

}

#endif