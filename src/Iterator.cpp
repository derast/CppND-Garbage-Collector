#include "Iterator.h"

class Node;

namespace sp {
  template<class T>
  Iterator<T>::Iterator() {
    ptr = end = begin = nullptr;
    length = 0;
  }

  template<class T>
  Iterator<T>::Iterator(T *p, T *first, T *last) {
    ptr = p;
    end = last;
    begin = first;
    length = last - first;
  }

  // Return length of sequence to which this
  // Iterator points.
  template<class T>
  unsigned Iterator<T>::size() { 
    return length; 
  }

  // Return value pointed to by ptr.
  // Do not allow out-of-bounds access.
  template<class T>
  T& Iterator<T>::operator*() {
    if ((ptr >= end) || (ptr < begin))
      throw OutOfRangeExc();

    return *ptr;
  }

  // Return address contained in ptr.
  // Do not allow out-of-bounds access.
  template<class T>
  T* Iterator<T>::operator->() {
    if ((ptr >= end) || (ptr < begin))
      throw OutOfRangeExc();

    return ptr;
  }

  // Prefix ++.
  template<class T>
  Iterator<T> Iterator<T>::operator++() {
    ptr++;

    return *this;
  }

  // Prefix --.
  template<class T>
  Iterator<T> Iterator<T>::operator--() {
    ptr--;

    return *this;
  }

  // Postfix ++.
  template<class T>
  Iterator<T> Iterator<T>::operator++(int notused) {
    T *tmp = ptr;
    ptr++;

    return Iterator<T>(tmp, begin, end);
  }

  // Postfix --.
  template<class T>
  Iterator<T> Iterator<T>::operator--(int notused) {
    T *tmp = ptr;
    ptr--;

    return Iterator<T>(tmp, begin, end);
  }

  // Return a reference to the object at the
  // specified index. Do not allow out-of-bounds
  // access.
  template<class T>
  T & Iterator<T>::operator[](int i) {
    if ((i < 0) || (i >= (end - begin)))
      throw OutOfRangeExc();

    return ptr[i];
  }

  // Define the relational operators.
  template<class T>
  bool Iterator<T>::operator==(Iterator op2) {
    return ptr == op2.ptr;
  }

  template<class T>
  bool Iterator<T>::operator!=(Iterator op2) {
    return ptr != op2.ptr;
  }

  template<class T>
  bool Iterator<T>::operator<(Iterator op2) {
    return ptr < op2.ptr;
  }

  template<class T>
  bool Iterator<T>::operator<=(Iterator op2) {
    return ptr <= op2.ptr;
  }

  template<class T>
  bool Iterator<T>::operator>(Iterator op2) {
    return ptr > op2.ptr;
  }

  template<class T>
  bool Iterator<T>::operator>=(Iterator op2) {
    return ptr >= op2.ptr;
  }

  // Subtract an integer from an Iterator.
  template<class T>
  Iterator<T> Iterator<T>::operator-(int n) {
    ptr -= n;

    return *this;
  }

  // Add an integer to an Iterator.
  template<class T>
  Iterator<T> Iterator<T>::operator+(int n) {
    ptr += n;

    return *this;
  }

  // Return number of elements between two Iterators.
  template<class T>
  int Iterator<T>::operator-(Iterator<T> &itr2) {
    return ptr - itr2.ptr;
  }
}


// Template explicit instantiation defination
template class sp::Iterator<int>;