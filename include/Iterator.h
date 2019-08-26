#ifndef ITERATOR__H
#define ITERATOR__H

namespace sp {
  // Exception thrown when an attempt is made to
  // use an Iterator that exceeds the range of the
  // underlying object.
  class OutOfRangeExc
  {
    // Add functionality if needed by your application.
  };

  template<class T>
  class Iterator {
    private:
      T *ptr;
      T *end;
      T *begin;        
      unsigned length; 
    public:
      Iterator();
      Iterator(T *p, T *first, T *last);
      // Return length of sequence to which this
      // Iterator points.
      unsigned size();
      // Return value pointed to by ptr.
      // Do not allow out-of-bounds access.
      T &operator*();
      // Return address contained in ptr.
      // Do not allow out-of-bounds access.
      T *operator->();
      // Prefix ++.
      Iterator operator++();
      // Prefix --.
      Iterator operator--();
      // Postfix ++.
      Iterator operator++(int notused);
      // Postfix --.
      Iterator operator--(int notused);
      // Return a reference to the object at the
      // specified index. Do not allow out-of-bounds
      // access.
      T &operator[](int i);
      // Define the relational operators.
      bool operator==(Iterator op2);
      bool operator!=(Iterator op2);
      bool operator<(Iterator op2);
      bool operator<=(Iterator op2);
      bool operator>(Iterator op2);
      bool operator>=(Iterator op2);
      // Subtract an integer from an Iterator.
      Iterator operator-(int n);
      // Add an integer to an Iterator.
      Iterator operator+(int n);
      // Return number of elements between two Iterators.
      int operator-(Iterator<T> &itr2);
  };
}

#endif