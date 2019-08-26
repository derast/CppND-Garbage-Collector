#ifndef POINTER__H
#define POINTER__H

#include <list>
#include "PtrDetails.h"
#include "Iterator.h"

namespace sp {
  template<class T, int size = 0>
  class Pointer {
    private:
      // refContainer maintains the garbage collection list.
      static std::list<PtrDetails<T> > refContainer;
      // addr points to the allocated memory to which
      // this Pointer pointer currently points.
      T *addr;
      /*  isArray is true if this Pointer points
          to an allocated array. It is false
          otherwise. 
      */
      bool isArray; 
      // true if pointing to array
      // If this Pointer is pointing to an allocated
      // array, then arraySize contains its size.
      unsigned arraySize; // size of the array
      static bool first; // true when first Pointer is created
      // Return an iterator to pointer details in refContainer.
      typename std::list<PtrDetails<T> >::iterator findPtrInfo(T *ptr);
      void swap(Pointer &first, Pointer &second);
    
    public:
      // Define an iterator type for Pointer<T>.
      typedef Iterator<T> GCiterator;
      // Empty constructor
      // NOTE: templates aren't able to have prototypes with default arguments
      // this is why constructor is designed like this:
      Pointer();
      Pointer(T*);
      // Copy constructor.
      Pointer(const Pointer &pointer);
      // Destructor for Pointer.
      ~Pointer();
      // Collect garbage. Returns true if at least
      // one object was freed.
      static bool collect();
      // Overload assignment of pointer to Pointer.
      T *operator=(T *t);
      // Overload assignment of Pointer to Pointer.
      Pointer &operator=(Pointer &rv);
      // Overload assignment of Pointer to Pointer.
      bool operator==(Pointer &rv);
      // Return a reference to the object pointed
      // to by this Pointer.
      T &operator*();
      // Return the address being pointed to.
      T *operator->();
      // Return a reference to the object at the
      // index specified by i.
      T &operator[](int i);
      // Conversion function to T *.
      operator T *();
      // Return an Iterator to the start of the allocated memory.
      Iterator<T> begin();
      // Return an Iterator to one past the end of an allocated array.
      Iterator<T> end();
      // Return the size of refContainer for this type of Pointer.
      static int refContainerSize();
      // A utility function that displays refContainer.
      static void showlist();
      // Clear refContainer when program exits.
      static void shutdown();
  };
}

#endif